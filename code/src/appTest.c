/******************************************************************************
 * @file    main.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Auto Guided Vehicle (AGV) control system main file
 * @version 1.0.0
 * @date    2022-01-31
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE.h"
#include "DIO.h"
#include "EXTI.h"
#include "TIMER.h"
#include "SPI.h"
#include "UART.h"
#include "UART_service.h"
#include "BUTTON.h"
#include "LED.h"
#include "IR.h"
#include "LIFTER.h"
#include "WHEELS.h"
#include "BATTERY.h"
#include "NRF24.h"

int main(void) {
    u8 data = 0, str[10] = {0}; /* Used by UART and SPI */

    /* Initialize modules here */
    DIO_Init();
    UART0_Init();
    UART1_Init();
    SPI_Init();

    #if 0   /* Uncomment when using EXTI    */
    EXTI_Init();
    PWM_Init(PWM_0, 16000U);
    PWM_Init(PWM_1, 16000U);
    PWM_Init(PWM_2, 16000U);
    PWM_Init(PWM_3, 16000U);
    
    UART0_Init();
    BUTTON_Init();
    LED_Init();
    IR_Init();
    LIFTER_Init();
    WHEELS_Init();
    BATTERY_Init();
    NRF24_Init();
    #endif

    #if 0     /* Testing UART checksum */
        UART0_SendString_Checksum("Me");
    #endif

    while(1) {  /* Infinite loop */
        #if 0   /* Testing SPI transmission */
        SPI_SendByte('a');
        _delay_ms(1000);
        SPI_SendByte('b');
        _delay_ms(1000);
        SPI_SendByte('c');
        _delay_ms(1000);

        #elif 0     /* Testing SPI reception */
        SPI_ReceiveByte(&data);
        _delay_ms(1000);

        #elif 0     /* Testing UART transmission */
        UART0_SendString("Sending from UART0\r\n");
        UART0_SendByte('a');
        _delay_ms(1000);
        UART0_SendByte('b');
        _delay_ms(1000);
        UART0_SendByte('c');
        _delay_ms(1000);

        UART0_SendString("\n\r");
        UART0_SendString("Hello World!\n\r");
        _delay_ms(1000);

        if(UART0_Available()) {
            UART0_ReceiveByte(&data);   
            UART0_SendByte(data);
        }

        UART1_SendString("Sending from UART1\r\n");
        UART1_SendByte('a');
        _delay_ms(1000);
        UART1_SendByte('b');
        _delay_ms(1000);
        UART1_SendByte('c');
        _delay_ms(1000);

        UART1_SendString("\n\r");
        UART1_SendString("Hello World!\n\r");
        _delay_ms(1000);

        if(UART1_Available()) {
            UART1_ReceiveByte(&data);   
            UART1_SendByte(data);
        }

        #elif 0     /* Testing UART Sending Float */
        UART1_SendString("\n\r");
        UART1_SendFloat(30.1415f, 6);
        UART1_SendString("\n\r");
        UART1_SendFloat(30.1415f, 4);
        UART1_SendString("\n\r");
        UART1_SendFloat(30.1415f, 3);
        UART1_SendString("\n\r");
        
        UART1_SendString("\n\r");
        UART1_SendFloat(-30.1415f, 6);
        UART1_SendString("\n\r");
        UART1_SendFloat(-30.1415f, 4);
        UART1_SendString("\n\r");
        UART1_SendFloat(-30.1415f, 3);
        UART1_SendString("\n\r");
        _delay_ms(10000);

        #elif 0     /* Testing UART Sending Integer */
        UART0_SendString("\n\r");
        UART0_SendInteger(30);
        UART0_SendString("\n\r");
        UART0_SendInteger(30);
        UART0_SendString("\n\r");
        UART0_SendInteger(30);
        UART0_SendString("\n\r");
        
        UART1_SendString("\n\r");
        UART1_SendInteger(-30L);
        UART1_SendString("\n\r");
        UART1_SendInteger(-30L);
        UART1_SendString("\n\r");
        UART1_SendInteger(-30L);
        UART1_SendString("\n\r");
        _delay_ms(10000);


        #elif 0    /* Testing UART reception */
        UART0_ReceiveByte(&data);

        switch (data) {
            case 'A':
                UART0_SendByte('A');
                break;

            case 'B':
                UART0_SendByte('B');
                break;
            default:
                UART0_SendString("\n\r");
                UART0_SendString("Invalid input\n\r");
                UART0_SendString("\n\r");
               break;
        }
        _delay_ms(1000);

        UART0_ReceiveString(str);

        #elif 0     /* Testing UART Receive checksum */
        UART0_ReceiveString_Checksum(str);

        #elif 0 /* Testing UART Asynchronous transmission */
        UART0_SendString_Asynchronous("UART0\r");
        UART0_SendString_Asynchronous("UART1\r");
        UART0_SendString_Asynchronous("UART2\r");
        _delay_ms(1000);

        #endif

    }
    
    return 0;
}