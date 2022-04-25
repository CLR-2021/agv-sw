/******************************************************************************
 * @file    DIO.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Digital Input Output (DIO) driver for Atmega128 microcontroller.
 * @version 1.0.0
 * @date    2022-03-20
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_reg.h"
#include "DIO.h"
#include "DIO_cfg.h"

/*-----------------------------------------------------------------------------*/
/*                             PRIVATE FUNCTIONS                               */                     
/*-----------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief Used inside DIO_Init() to initialize a pin
 * @param pin: pin to initialize, options are defined in DIO.h file in the enum PIN_t
 * @param port: port to initialize, options are defined in DIO.h file in the enum PORT_t
 * @param direction: pin direction, options are defined in DIO.h file in the enum DIRECTION_t
 ******************************************************************************/
#define INIT_PIN(pin, port, direction, pullup, direction_reg)          \
    if(INPUT == direction) {                            \
        CLR_BIT(direction_reg, pin);                    \
                                                        \
        if(PULLUP_TRUE == pullup) {                     \
            SET_BIT(port, pin);                         \
        }                                               \
        else {                                           \
            CLR_BIT(port, pin);                         \
        }                                               \
    }                                                   \
    else if(OUTPUT == direction) {                      \
        SET_BIT(direction_reg, pin);                    \
        CLR_BIT(port, pin);                             \
    }                                                   \
    else {     /* Invalid Direction    */                \
        ; /* Null operation       */                    \
    }                                   
    
/*******************************************************************************
 * @brief used inside the writePin() function to write a pin
 *        Calling direction: DIO_WritePin() -> writePin() -> WRITE_PIN()
 * @param pin the pin number, options are defined in the DIO.h file in the enum PIN_t
 * @param port the port number, options are defined in the DIO.h file in the enum PORT_t
 * @param pinState the state of the pin, options are defined in the DIO.h file in the enum STATE_t
 ******************************************************************************/
#define WRITE_PIN(pin, port, state)                     \
    if(LOW == state) {                                  \
        CLR_BIT(port, pin);                             \
    }else if(HIGH == state) {                           \
        SET_BIT(port, pin);                             \
    }else {     /* Invalid State    */                   \
        ; /* Null operation       */                    \
    }

/*-----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                               */
/*-----------------------------------------------------------------------------*/
/*******************************************************************************
 * @details Initialize DIO pins to a specific direction (input or output), pullup or not
 *          according to the configuration in the DIO_cfg.h file.  
 ******************************************************************************/
void DIO_Init(void) {
    for(u8 i = 0; i < countPinsConfigured; ++i) {
        switch (pinConfigs[i].port) {
            case PORT_A:
                INIT_PIN(pinConfigs[i].pin, PORTA, pinConfigs[i].direction, pinConfigs[i].pullup, DDRA);
                break;

            case PORT_B:
                INIT_PIN(pinConfigs[i].pin, PORTB, pinConfigs[i].direction, pinConfigs[i].pullup, DDRB);
                break;

            case PORT_C:
                INIT_PIN(pinConfigs[i].pin, PORTC, pinConfigs[i].direction, pinConfigs[i].pullup, DDRC);
                break;

            case PORT_D:
                INIT_PIN(pinConfigs[i].pin, PORTD, pinConfigs[i].direction, pinConfigs[i].pullup, DDRD);
                break;
            
            case PORT_E:
                INIT_PIN(pinConfigs[i].pin, PORTE, pinConfigs[i].direction, pinConfigs[i].pullup, DDRE);
                break;

            case PORT_F:
                INIT_PIN(pinConfigs[i].pin, PORTF, pinConfigs[i].direction, pinConfigs[i].pullup, DDRF);
                break;
            
            case PORT_G:
                INIT_PIN(pinConfigs[i].pin, PORTG, pinConfigs[i].direction, pinConfigs[i].pullup, DDRG);
                break;

            default: /* Error, invalid port ID  */
                ;    /* NULL operation   */
        }
    }
}

/*******************************************************************************
 * @details If:
 *          * DIO pin is not configured in the DIO_cfg.h file
 *          * Or the pin is configurations need to be modified
 *          Then, this function will be called to modify the pin configuration.
 ******************************************************************************/
void DIO_InitPin(const PIN_t pin, const PORT_t port, const DIR_t direction, const PULLUP_t pullup) {
    switch (port) {
        case PORT_A:
            INIT_PIN(pin, PORTA, direction, pullup, DDRA);
            break;

        case PORT_B:
            INIT_PIN(pin, PORTB, direction, pullup, DDRB);
            break;

        case PORT_C:
            INIT_PIN(pin, PORTC, direction, pullup, DDRC);
            break;

        case PORT_D:
            INIT_PIN(pin, PORTD, direction, pullup, DDRD);
            break;
        
        case PORT_E:
            INIT_PIN(pin, PORTE, direction, pullup, DDRE);
            break;

        case PORT_F:
            INIT_PIN(pin, PORTF, direction, pullup, DDRF);
            break;
        
        case PORT_G:
            INIT_PIN(pin, PORTG, direction, pullup, DDRG);
            break;

        default: /* Error, invalid port ID  */
            ;    /* NULL operation   */
    }
}

/*******************************************************************************
 * @details If the pin is configured in the DIO_cfg.h file, then this function 
 *          can be called to write to the pin (1 or 0).
 ******************************************************************************/
void DIO_WritePin(const PIN_t pin, const PORT_t port, const STATE_t pinState) {
    for(u8 i = 0; i < countPinsConfigured; ++i) {
        if( (pin == pinConfigs[i].pin) && (port == pinConfigs[i].port) ) {
            switch (port) {
                case PORT_A:
                    WRITE_PIN(pin, PORTA, pinState);
                    break;

                case PORT_B:
                    WRITE_PIN(pin, PORTB, pinState);
                    break;

                case PORT_C:
                    WRITE_PIN(pin, PORTC, pinState);
                    break;

                case PORT_D:
                    WRITE_PIN(pin, PORTD, pinState);
                    break;

                case PORT_E:
                    WRITE_PIN(pin, PORTE, pinState);
                    break;

                case PORT_F:
                    WRITE_PIN(pin, PORTF, pinState);
                    break;

                case PORT_G:
                    WRITE_PIN(pin, PORTG, pinState);
                    break;

                default: /* Error, invalid port ID  */
                    ;    /* NULL operation   */
            }
        }
    }
}

/*******************************************************************************
 * @details This function can be called to toggle the state of the pin. If the pins state
 *          is HIGH, then it will be set to LOW, and vice versa.
 ******************************************************************************/
void DIO_TogglePin(const PIN_t pin, const PORT_t port) {
    for(u8 i = 0; i < countPinsConfigured; ++i) {
        if( (pin == pinConfigs[i].pin) && (port == pinConfigs[i].port) ) {
            switch (port) {
                case PORT_A:
                    TOG_BIT(PORTA, pin);
                    break;

                case PORT_B:
                    TOG_BIT(PORTB, pin);
                    break;

                case PORT_C:
                    TOG_BIT(PORTC, pin);
                    break;

                case PORT_D:
                    TOG_BIT(PORTD, pin);
                    break;

                case PORT_E:
                    TOG_BIT(PORTE, pin);
                    break;

                case PORT_F:
                    TOG_BIT(PORTF, pin);
                    break;

                case PORT_G:
                    TOG_BIT(PORTG, pin);
                    break;

                default: /* Error, invalid port ID  */
                    ;    /* NULL operation   */
            }
        }
    }
}

/*******************************************************************************
 * @details Write a value to the port (all pins).
 ******************************************************************************/
void DIO_WritePort(const PORT_t port, const u8 value) {
    switch (port) {
        case PORT_A:
            PORTA = value;
            break;

        case PORT_B:
            PORTB = value;
            break;

        case PORT_C:
            PORTC = value;
            break;

        case PORT_D:
            PORTD = value;
            break;
        
        case PORT_E:
            PORTE = value;
            break;
        
        case PORT_F:
            PORTF = value;
            break;

        case PORT_G:
            PORTG = value;
            break;

        default: /* Error, invalid port ID  */
            ;    /* NULL operation   */
    }
}

/*******************************************************************************
 * @details If the pin is configured in the DIO_cfg.h file, then this function
 *         can be called to read the pin (1 or 0).
 ******************************************************************************/
STATE_t DIO_ReadPin(const PIN_t pin, const PORT_t port) {
    STATE_t pinState = LOW;

    /* Loop times = # of onfigured pins in DIO  */
    for(u8 i = 0; i < countPinsConfigured; ++i) {
        /* Check te port and pin                */
        if((pin == pinConfigs[i].pin) && (port == pinConfigs[i].port)) {
            switch (pinConfigs[i].port) {
                case PORT_A:
                    pinState = GET_BIT(PINA, pinConfigs[i].pin);
                    break;

                case PORT_B:
                    pinState = GET_BIT(PINB, pinConfigs[i].pin);
                    break;

                case PORT_C:
                    pinState = GET_BIT(PINC, pinConfigs[i].pin);
                    break;

                case PORT_D:
                    pinState = GET_BIT(PIND, pinConfigs[i].pin);
                    break;

                case PORT_E:
                    pinState = GET_BIT(PINE, pinConfigs[i].pin);
                    break;

                case PORT_F:
                    pinState = GET_BIT(PINF, pinConfigs[i].pin);
                    break;

                case PORT_G:
                    pinState = GET_BIT(PING, pinConfigs[i].pin);
                    break;

                default: /* Error, invalid port ID     */
                    ;    /* NULL Operations            */
            }
        }
    }

    return pinState;
}

/*******************************************************************************
 * @details Read the value of the port (all pins).
 ******************************************************************************/
u8 DIO_ReadPort(const PORT_t port) {
    u8 portValue = 0;

    switch (port) {
        case PORT_A:
            portValue = PORTA;
            break;

        case PORT_B:
            portValue = PORTB;
            break;

        case PORT_C:
            portValue = PORTC;
            break;

        case PORT_D:
            portValue = PORTD;
            break;

        case PORT_E:
            portValue = PORTE;
            break;

        case PORT_F:
            portValue = PORTF;
            break;

        case PORT_G:
            portValue = PORTG;
            break;

        default: /* Error, invalid port ID  */
            ;    /* NULL operation   */
    }

    return portValue;
}

