/**************************************************************************
 * @file    UART.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   UART driver for ATMEGA128 microcontroller.
 * @version 1.0.0
 * @date    2022-03-03
 * @copyright Copyright (c) 2022
 **************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_reg.h"
#include "GIE.h"
#include "UART.h"
#include "UART_cfg.h"

/*----------------------------------------------------------------------*/
/*                        CALLBACK FUNCTIONS                            */
/*----------------------------------------------------------------------*/
#if 0
static void (* volatile UART0_RX_Callback)(void)   = NULL;     /*!< Pointer to the RX callback function of UART0 */
static void (* volatile UART1_RX_Callback)(void)   = NULL;     /*!< Pointer to the RX callback function of UART1 */
static void (* volatile UART0_TX_Callback)(void)   = NULL;     /*!< Pointer to the TX callback function of UART0 */
static void (* volatile UART1_TX_Callback)(void)   = NULL;     /*!< Pointer to the TX callback function of UART1 */
static void (* volatile UART0_UDRE_Callback)(void) = NULL;     /*!< Pointer to the UDRE callback function of UART0 */
static void (* volatile UART1_UDRE_Callback)(void) = NULL;     /*!< Pointer to the UDRE callback function of UART1 */
#elif 1
typedef void (* volatile UART_Callback_typedef_fn)(void);
static UART_Callback_typedef_fn UART0_RX_Callback = NULL;     /*!< Pointer to the RX callback function of UART0 */
static UART_Callback_typedef_fn UART1_RX_Callback = NULL;     /*!< Pointer to the RX callback function of UART1 */
static UART_Callback_typedef_fn UART0_TX_Callback = NULL;     /*!< Pointer to the TX callback function of UART0 */
static UART_Callback_typedef_fn UART1_TX_Callback = NULL;     /*!< Pointer to the TX callback function of UART1 */
static UART_Callback_typedef_fn UART0_UDRE_Callback = NULL;   /*!< Pointer to the UDRE callback function of UART0 */
static UART_Callback_typedef_fn UART1_UDRE_Callback = NULL;   /*!< Pointer to the UDRE callback function of UART1 */
#endif

/*----------------------------------------------------------------------*/
/*                          ISR FUNCTIONS                               */
/*----------------------------------------------------------------------*/
/* UART0_RX_ISR */
void __vector_18(void) __attribute__((signal));
void __vector_18(void) {
    GIE_Disable();

    if(NULL != UART0_RX_Callback) {
        UART0_RX_Callback();
    }

    /* Clear the RXC flag */
    SET_BIT(UCSR0A, RXC);

    GIE_Enable();
}

/* UART0_TX_ISR */
void __vector_20(void) __attribute__((signal));
void __vector_20(void) {
    GIE_Disable();

    if(UART0_TX_Callback != NULL) {
        UART0_TX_Callback();
    }

    /* Clear the TXC flag */
    SET_BIT(UCSR0A, TXC);

    GIE_Enable();
}

/* UART0_UDRE_ISR */
void __vector_19(void) __attribute__((signal));
void __vector_19(void) {
    GIE_Disable();

    if(UART0_UDRE_Callback != NULL) {
        UART0_UDRE_Callback();
    }

    /* Clear the UDRE flag */
    CLR_BIT(UCSR0A, UDRE);

    GIE_Enable();
}

/* UART1_RX_ISR */
void __vector_30(void) __attribute__((signal));
void __vector_30(void) {
    GIE_Disable();

    if(NULL != UART1_RX_Callback) {
        UART1_RX_Callback();
    }

    /* Clear the RXC flag */
    SET_BIT(UCSR1A, RXC);

    GIE_Enable();
}

/* UART1_TX_ISR */
void __vector_32(void) __attribute__((signal));
void __vector_32(void) {
    GIE_Disable();

    if(UART1_TX_Callback != NULL) {
        UART1_TX_Callback();
    }

    /* Clear the TXC flag */
    SET_BIT(UCSR1A, TXC);

    GIE_Enable();
}

/* UART1_UDRE_ISR */
void __vector_31(void) __attribute__((signal));
void __vector_31(void) {
    GIE_Disable();

    if(UART1_UDRE_Callback != NULL) {
        UART1_UDRE_Callback();
    }

    /* Clear the UDRE flag */
    CLR_BIT(UCSR1A, UDRE);

    GIE_Enable();
}

/*--------------------------------------------------------------------*/
/*                 UART PRIVATE FUNCTIONS PROTOTYPES                 */
/*--------------------------------------------------------------------*/
static void UART_SetBaudRate(const u32 baudRate, const UART_MODE_t mode, volatile u8 * const UBRRnH, volatile u8 * const UBRRnL) {
    u16 ubbrValue = 0;

    /* Calculate UBRR value */
    switch (mode) {
        case UART_MODE_ASYNCHRONOUS_NORMAL:
            ubbrValue = (u16)( ( ( (u32)F_CPU ) / ((u32)16 * baudRate) ) - 1);
            break;
        case UART_MODE_ASYNCHRONOUS_DOUBLE_SPEED:
            ubbrValue = (u16)( ( ( (u32)F_CPU ) / ((u32)8 * baudRate) ) - 1);
            break;
        case UART_MODE_SYNCHRONOUS_MASTER:
            ubbrValue = (u16)( ( ( (u32)F_CPU ) / ((u32)2 * baudRate) ) - 1);
            break;
        default:
            break;
    }
            
    /* Set UBRR value. UBRRH must be written before UBRRL */
    *UBRRnH = (u8)(ubbrValue >> 8);
    *UBRRnL = (u8)ubbrValue;
}

static void UART0_SetBaudRate(const u32 baudRate) {
    UART_SetBaudRate(baudRate, UART0_Configs.mode, &UBRR0H, &UBRR0L);
}

static void UART1_SetBaudRate(const u32 baudRate) {
    UART_SetBaudRate(baudRate, UART1_Configs.mode, &UBRR1H, &UBRR1L);
}

static void UART_SetDataBits(const UART_DATA_BITS_t dataBits, volatile u8 * const UCSRnC, volatile u8 * const UCSRnB) {
    switch (dataBits) {
        case UART_DATA_5_BITS:
            CLR_BIT(*UCSRnC, UCSZ0);
            CLR_BIT(*UCSRnC, UCSZ1);
            CLR_BIT(*UCSRnB, UCSZ2);
            break;
        case UART_DATA_6_BITS:
            SET_BIT(*UCSRnC, UCSZ0);
            CLR_BIT(*UCSRnC, UCSZ1);
            CLR_BIT(*UCSRnB, UCSZ2);
            break;
        case UART_DATA_7_BITS:
            CLR_BIT(*UCSRnC, UCSZ0);
            SET_BIT(*UCSRnC, UCSZ1);
            CLR_BIT(*UCSRnB, UCSZ2);
            break;
        case UART_DATA_8_BITS:
            SET_BIT(*UCSRnC, UCSZ0);
            SET_BIT(*UCSRnC, UCSZ1);
            CLR_BIT(*UCSRnB, UCSZ2);
            break;
        case UART_DATA_9_BITS:
            SET_BIT(*UCSRnC, UCSZ0);
            SET_BIT(*UCSRnC, UCSZ1);
            SET_BIT(*UCSRnB, UCSZ2);
            break;
        default:
            break;
    }
}

static void UART0_SetDataBits(const UART_DATA_BITS_t dataBits) {
    UART_SetDataBits(dataBits, &UCSR0C, &UCSR0B);
}

static void UART1_SetDataBits(const UART_DATA_BITS_t dataBits) {
    UART_SetDataBits(dataBits, &UCSR1C, &UCSR1B);
}

static void UART_SetParity(const UART_PARITY_t parity, volatile u8 * const UCSRnC) {
    switch (parity) {
        case UART_PARITY_DISABLE:
            CLR_BIT(*UCSRnC, UPM0);
            CLR_BIT(*UCSRnC, UPM1);
            break;
        case UART_PARITY_EVEN:
            CLR_BIT(*UCSRnC, UPM0);
            SET_BIT(*UCSRnC, UPM1);
            break;
        case UART_PARITY_ODD:
            SET_BIT(*UCSRnC, UPM0);
            SET_BIT(*UCSRnC, UPM1);
            break;
        default:
            /* DEBUGGING */
            break;
    }
}

static void UART0_SetParity(const UART_PARITY_t parity) {
    UART_SetParity(parity, &UCSR0C);
}

static void UART1_SetParity(const UART_PARITY_t parity) {
    UART_SetParity(parity, &UCSR1C);
}

static void UART_SetStopBits(const UART_STOP_BITS_t stopBits, volatile u8 * const UCSRnC) {
    switch (stopBits) {
        case UART_STOP_1_BIT:
            CLR_BIT(*UCSRnC, USBS);
            break;
        case UART_STOP_2_BIT:
            SET_BIT(*UCSRnC, USBS);
            break;
        default:
            break;
    }
}

static void UART0_SetStopBits(const UART_STOP_BITS_t stopBits) {
    UART_SetStopBits(stopBits, &UCSR0C);
}

static void UART1_SetStopBits(const UART_STOP_BITS_t stopBits) {
    UART_SetStopBits(stopBits, &UCSR1C);
}

static void UART_SetMode(const UART_MODE_t mode, volatile u8 * const UCSRnB) {
    switch (mode) {
        case UART_MODE_ASYNCHRONOUS_NORMAL: case UART_MODE_ASYNCHRONOUS_DOUBLE_SPEED:
            CLR_BIT(*UCSRnB, UMSEL);
            break;
        case UART_MODE_SYNCHRONOUS_MASTER: case UART_MODE_SYNCHRONOUS_SLAVE:
            SET_BIT(*UCSRnB, UMSEL);
            break;
        default:
            break;
    }
}

static void UART0_SetMode(const UART_MODE_t mode) {
    UART_SetMode(mode, &UCSR0B);
}

static void UART1_SetMode(const UART_MODE_t mode) {
    UART_SetMode(mode, &UCSR1B);
}

static void UART_SetClockPolarity(const UART_CLOCK_POLARITY_t polarity, volatile u8 * const UCSRnC, volatile u8 * const UCSRnB) {
    switch (UART0_Configs.mode ) {
        case UART_MODE_ASYNCHRONOUS_NORMAL: case UART_MODE_ASYNCHRONOUS_DOUBLE_SPEED:
            CLR_BIT(*UCSRnC, UCPOL);
            break;
        case UART_MODE_SYNCHRONOUS_MASTER: case UART_MODE_SYNCHRONOUS_SLAVE:
            switch (polarity) {
                case UART_RISING_EDGE_CLOCK:
                    CLR_BIT(*UCSRnB, UCPOL);
                    break;
                case UART_FALLING_EDGE_CLOCK:
                    SET_BIT(*UCSRnB, UCPOL);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

static void UART0_SetClockPolarity(const UART_CLOCK_POLARITY_t polarity) {
    UART_SetClockPolarity(polarity, &UCSR0C, &UCSR0B);
}

static void UART1_SetClockPolarity(const UART_CLOCK_POLARITY_t polarity) {
    UART_SetClockPolarity(polarity, &UCSR1C, &UCSR1B);
}

static void UART_SetSpeed(const UART_MODE_t mode, volatile u8 * const UCSRnB) {
    switch (mode) {
        case UART_MODE_ASYNCHRONOUS_NORMAL:
            CLR_BIT(*UCSRnB, U2X);
            break;
        case UART_MODE_ASYNCHRONOUS_DOUBLE_SPEED:
            SET_BIT(*UCSRnB, U2X);
            break;
        default:
            break;
    }
}

static void UART0_SetSpeed(const UART_MODE_t mode) {
    UART_SetSpeed(mode, &UCSR0B);
}

static void UART1_SetSpeed(const UART_MODE_t mode) {
    UART_SetSpeed(mode, &UCSR1B);
}

/*----------------- Send Data (Synchronous) -------------------*/
static void UART_SendByte(const u8 data, volatile u8 * const UCSRnA, volatile u8 * const UDRn) {
    /* Wait for empty transmit buffer: Synchronous */
    while( BIT_IS_CLEAR(*UCSRnA, UDRE) )
        ;

    /* Put data into buffer, sends the data */
    *UDRn = data;
}

static void UART_Send9BitData(const u16 data, volatile u8 * const UCSRnA, volatile u8 * const UCSRnB, volatile u8 * const UDRn) {
    /* Wait for empty transmit buffer: Synchronous */
    while(BIT_IS_CLEAR(*UCSRnA, UDRE) );

    /* Put 9th bit into buffer: Must be written before the data register */
    if(data & 0x0100) {     /* If 9th bit is 1 */
        SET_BIT(*UCSRnB, TXB8);
    }else {
        CLR_BIT(*UCSRnB, TXB8);
    }

    /* Put data into buffer, sends the data */
    *UDRn = (u8)(data & 0x00FF);
}

/*----------------- Send Data (No Check) ------------------*/
static void UART_SendByte_NoBlock(const u8 data, volatile u8 * const UDRn) {
    /* Put data into buffer, sends the data */
    *UDRn = data;
}

static void UART_Send9BitData_NoBlock(const u16 data, volatile u8 * const UCSRnB, volatile u8 * const UDRn) {
    /* Put 9th bit into buffer: Must be written before the data register */
    if(data & 0x0100) {     /* If 9th bit is 1 */
        SET_BIT(*UCSRnB, TXB8);
    }else {
        CLR_BIT(*UCSRnB, TXB8);
    }

    /* Put data into buffer, sends the data */
    *UDRn = (u8)(data & 0x00FF);
}

/*----------------- Check if Data is Received ------------------*/
static STATE_t UART_Available(volatile u8 * const UCSRnA) {
    STATE_t state = LOW;

    /* Check if data is available in receive buffer */
    if(BIT_IS_SET(*UCSRnA, RXC)) {
        state = HIGH;
    }else {
        state = LOW;
    }

    return state;
}

/*----------------- Receive Data (Synchronous) ------------------*/
static ERROR_STATUS_t UART_ReceiveByte(u8 * const data, volatile u8 * const UCSRnA, volatile u8 * const UDRn) {
    ERROR_STATUS_t errorStatus = ERROR_NO;
                    
    /* Wait for data to be received */
    while( BIT_IS_CLEAR(*UCSRnA, RXC) ) 
        ;

    /* Check for errors. Must be checked before reading the data register */
    if( BIT_IS_SET(*UCSRnA, FE) || BIT_IS_SET(*UCSRnA, DOR) || BIT_IS_SET(*UCSRnA, UPE)) {
        errorStatus = ERROR_YES;
    }else {
        errorStatus = ERROR_NO;
    }

    /* Get data from buffer */
    *data = *UDRn;
    /* Reading data register clears the receive complete flag. So, no need to clear it again */

    return errorStatus;
}

static ERROR_STATUS_t UART_Receive9BitData(u16 * const data, volatile u8 * const UCSRnA, volatile u8 * const UDRn) {
    ERROR_STATUS_t errorStatus = ERROR_NO;

    /* Wait for data to be received */
    while(BIT_IS_CLEAR(*UCSRnA, RXC) )
        ;

    /* Check for errors. Must be checked before reading the data register */
    if( BIT_IS_SET(*UCSRnA, FE) || BIT_IS_SET(*UCSRnA, DOR) || BIT_IS_SET(*UCSRnA, UPE)) {
        errorStatus = ERROR_YES;
    }else {
        errorStatus = ERROR_NO;
    }

    /* Get 9th bit from buffer */
    if(BIT_IS_SET(UCSR0B, RXB8)) {
        *data = (u16)(*UDRn) | 0x0100;   /* Must be read before the data register */
    }else {
        *data = (u16)(*UDRn);
    }

    return errorStatus;
}

/*----------------- Receive Data (No Check) -----------------*/
static ERROR_STATUS_t UART_ReceiveByte_NoBlock(u8 * const data, volatile u8 * const UCSRnA, volatile u8 * const UDRn) {
    ERROR_STATUS_t errorStatus = ERROR_NO;
    
    /* Check for errors. Must be checked before reading the data register */
    if( BIT_IS_SET(*UCSRnA, FE) || BIT_IS_SET(*UCSRnA, DOR) || BIT_IS_SET(*UCSRnA, UPE)) {
        errorStatus = ERROR_YES;
    }else {
        errorStatus = ERROR_NO;
    }

    /* Get data from buffer */
    *data = *UDRn;
    /* Reading data register clears the receive complete flag. So, no need to clear it again */

    return errorStatus;
}

static ERROR_STATUS_t UART_Receive9BitData_NoBlock(u16 * const data, volatile u8 * const UCSRnA, volatile u8 * const UDRn) {
    ERROR_STATUS_t errorStatus = ERROR_NO;

    /* Check for errors. Must be checked before reading the data register */
    if( BIT_IS_SET(*UCSRnA, FE) || BIT_IS_SET(*UCSRnA, DOR) || BIT_IS_SET(*UCSRnA, UPE)) {
        errorStatus = ERROR_YES;
    }else {
        errorStatus = ERROR_NO;
    }

    /* Get 9th bit from buffer */
    if(BIT_IS_SET(UCSR0B, RXB8)) {
        *data = (u16)(*UDRn) | 0x0100;   /* Must be read before the data register */
    }else {
        *data = (u16)(*UDRn);
    }

    return errorStatus;
}

/*----------------- Receive Data (Interrupt) -----------------*/


/*----------------- Flush Receive Buffer ------------------*/
static void UART_Flush(volatile u8 *UCSRnA, ERROR_STATUS_t (* const UART_ReceiveByte)(u8 * const data)) {
    u8 dummy;
                    
    while(BIT_IS_SET(*UCSRnA, RXC) ) {
        UART_ReceiveByte(&dummy);
    }
}

/*--------------------------------------------------------------------*/
/*                 UART PUBLIC FUNCTIONS PROTOTYPES                 */
/*--------------------------------------------------------------------*/

/*----------------- Initialize UART Modules------------------*/
void UART0_Init(void) {
        /* Set baud rate */
         UART0_SetBaudRate(UART0_Configs.baud_rate);

        /* Set data bits: 5, 6, 7, 8 or 9 */
         UART0_SetDataBits(UART0_Configs.data_bits);

        /* Set parity: even, odd, disable */
         UART0_SetParity(UART0_Configs.parity);

        /* Set stop bits: 1 or 2 */
         UART0_SetStopBits(UART0_Configs.stop_bits);

        /* Set mode: asynchronous or synchronous */
         UART0_SetMode(UART0_Configs.mode);

        /* Set clock polarity: rising or falling */
         UART0_SetClockPolarity(UART0_Configs.clock_polarity);

        /* Set speed: normal or double speed */
         UART0_SetSpeed(UART0_Configs.mode);

        /* Enable UART */
        UART0_Enable();
}

void UART1_Init(void) {
        /* Set baud rate */
        UART1_SetBaudRate(UART1_Configs.baud_rate);

        /* Set data bits: 5, 6, 7, 8 or 9 */
        UART1_SetDataBits(UART1_Configs.data_bits);

        /* Set parity: even, odd, disable */
        UART1_SetParity(UART1_Configs.parity);

        /* Set stop bits: 1 or 2 */
        UART1_SetStopBits(UART1_Configs.stop_bits);

        /* Set mode: asynchronous or synchronous */
        UART1_SetMode(UART1_Configs.mode);

        /* Set clock polarity: rising or falling */
        UART1_SetClockPolarity(UART1_Configs.clock_polarity);

        /* Set speed: normal or double speed */
        UART1_SetSpeed(UART1_Configs.mode);

        /* Enable UART */
        UART1_Enable();
}

/*----------------- Enable UART Modules -------------------*/
void UART0_Enable(void) {
    SET_BIT(UCSR0B, RXEN);     /* Enable receiver */
    SET_BIT(UCSR0B, TXEN);     /* Enable transmitter */
}

void UART1_Enable(void) {
    SET_BIT(UCSR1B, RXEN);     /* Enable receiver */
    SET_BIT(UCSR1B, TXEN);     /* Enable transmitter */    
}

/*----------------- Disable UART Modules ------------------*/
void UART0_Disable(void) {
    CLR_BIT(UCSR0B, RXEN);     /* Enable receiver */
    CLR_BIT(UCSR0B, TXEN);     /* Enable transmitter */
}

void UART1_Disable(void) {
    CLR_BIT(UCSR1B, RXEN);     /* Enable receiver */
    CLR_BIT(UCSR1B, TXEN);     /* Enable transmitter */
}

/*----------------- Send Data (Synchronous) -------------------*/
void UART0_SendByte(const u8 data) {
    UART_SendByte(data, &UCSR0A, &UDR0);
}

void UART1_SendByte(const u8 data) {
    UART_SendByte(data, &UCSR1A, &UDR1);
}

void UART0_Send9BitData(const u16 data) {
    UART_Send9BitData(data, &UCSR0A, &UCSR0B, &UDR0);
}

void UART1_Send9BitData(const u16 data) {
    UART_Send9BitData(data, &UCSR1A, &UCSR1B, &UDR1);
}

/*----------------- Send Data (No Block) ------------------*/
void UART0_SendByte_NoBlock(const u8 data) {
    UART_SendByte_NoBlock(data, &UDR0);
}

void UART1_SendByte_NoBlock(const u8 data) {
    UART_SendByte_NoBlock(data, &UDR1);
}

void UART0_Send9BitData_NoBlock(const u16 data) {
    UART_Send9BitData_NoBlock(data, &UCSR0B, &UDR0);
}

void UART1_Send9BitData_NoBlock(const u16 data) {
    UART_Send9BitData_NoBlock(data, &UCSR1B, &UDR1);
}

/*----------------- Receive Data (Synchronous) ------------------*/
ERROR_STATUS_t UART0_ReceiveByte(u8 * const data) {
    return UART_ReceiveByte(data, &UCSR0A, &UDR0);
}

ERROR_STATUS_t UART1_ReceiveByte(u8 * const data) {
    return UART_ReceiveByte(data, &UCSR1A, &UDR1);
}

ERROR_STATUS_t UART0_Receive9BitData(u16 * const data) {
    return UART_Receive9BitData(data, &UCSR0A, &UDR0);
}

ERROR_STATUS_t UART1_Receive9BitData(u16 * const data) {
    return UART_Receive9BitData(data, &UCSR1A, &UDR1);
}

/*----------------- Receive Data (No Check) -----------------*/
ERROR_STATUS_t UART0_ReceiveByte_NoBlock(u8 * const data) {
    return UART_ReceiveByte_NoBlock(data, &UCSR0A, &UDR0);
}

ERROR_STATUS_t UART1_ReceiveByte_NoBlock(u8 * const data) {
    return UART_ReceiveByte_NoBlock(data, &UCSR1A, &UDR1);
}

ERROR_STATUS_t UART0_Receive9BitData_NoBlock(u16 * const data) {
    return UART_Receive9BitData_NoBlock(data, &UCSR0A, &UDR0);
}

ERROR_STATUS_t UART1_Receive9BitData_NoBlock(u16 * const data) {
    return UART_Receive9BitData_NoBlock(data, &UCSR1A, &UDR1);
}

/*----------------- Check if Data is Received ------------------*/
STATE_t UART0_Available(void) {
    return UART_Available(&UCSR0A);
}

STATE_t UART1_Available(void) {
    return UART_Available(&UCSR1A);
}

/********************************************************************************
 * @brief The receiver buffer FIFO will be flushed when the receiver is disabled, 
 *          i.e. the buffer will be emptied of its contents. 
 *        Unread data will be lost. If the buffer has to be flushed during normal 
 *          operation, due to for instance an error condition, 
 *          read the UDR I/O location until the RXC flag is cleared. 
 *******************************************************************************/
void UART0_Flush(void) {
    UART_Flush(&UCSR0A, UART0_ReceiveByte);
}

void UART1_Flush(void) {
    UART_Flush(&UCSR1A, UART1_ReceiveByte);
}

void UART0_RX_InterruptEnable(void(* const ptrCallback)(void)) {    
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/
    SET_BIT(UCSR0B, RXCIE);        /* Enable RX Complete Interrupt */
    UART0_RX_Callback = ptrCallback;    /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART1_RX_InterruptEnable(void(* const ptrCallback)(void)) {    
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/
    SET_BIT(UCSR1B, RXCIE);        /* Enable RX Complete Interrupt */
    UART1_RX_Callback = ptrCallback;    /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART1_TX_InterruptEnable(void(* const ptrCallback)(void)) {
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/
    SET_BIT(UCSR1B, TXCIE);        /* Enable TX Complete Interrupt */
    UART1_TX_Callback = ptrCallback;    /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART0_TX_InterruptEnable(void(* const ptrCallback)(void)) {
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/
    SET_BIT(UCSR0B, TXCIE);        /* Enable TX Complete Interrupt */
    UART0_TX_Callback = ptrCallback;    /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART0_UDRE_InterruptEnable(void(* const ptrCallback)(void)) {
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/ 
    SET_BIT(UCSR0B, UDRIE);        /* Enable UDRE Interrupt */
    UART0_UDRE_Callback = ptrCallback;  /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART1_UDRE_InterruptEnable(void(* const ptrCallback)(void)) {
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/ 
    SET_BIT(UCSR1B, UDRIE);        /* Enable UDRE Interrupt */
    UART1_UDRE_Callback = ptrCallback;  /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART0_RX_InterruptDisable(void) {
    CLR_BIT(UCSR0B, RXCIE);        /* Disable RX Complete Interrupt */
}

void UART1_RX_InterruptDisable(void) {
    CLR_BIT(UCSR1B, RXCIE);        /* Disable RX Complete Interrupt */
}

void UART0_TX_InterruptDisable(void) {
    CLR_BIT(UCSR0B, TXCIE);        /* Disable TX Complete Interrupt */
}

void UART1_TX_InterruptDisable(void) {
    CLR_BIT(UCSR1B, TXCIE);        /* Disable TX Complete Interrupt */
}

void UART0_UDRE_InterruptDisable(void) {
    CLR_BIT(UCSR0B, UDRIE);        /* Disable UDRE Interrupt */
}

void UART1_UDRE_InterruptDisable(void) {
    CLR_BIT(UCSR1B, UDRIE);        /* Disable UDRE Interrupt */
}

