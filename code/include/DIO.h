/*/*******************************************************************************
 * @file    DIO.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Interace file for Digital Input Output (DIO) module for Atmega128 microcontroller (\ref DIO.c)
 * @version 1.0.0
 * @date    2022-01-23
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#ifndef DIO_H
#define DIO_H

/*------------------------------------------------------------------------------*/
/*                                  TYPEDEFS                                    */
/*------------------------------------------------------------------------------*/
typedef enum{
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7
}PIN_t;

typedef enum{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G
}PORT_t;

typedef enum{
    INPUT,
    OUTPUT
}DIR_t;

typedef enum{
    PULLUP_TRUE,
    PULLUP_FALSE
}PULLUP_t;

/*------------------------------------------------------------------------------*/
/*                             API FUNCTIONS PROTOTYPES                         */
/*------------------------------------------------------------------------------*/
/*******************************************************************************
 * @brief Initialize DIO configurations based on user configurations in DIO_cfg.h
 *        and DIO_cfg.c
 ******************************************************************************/
void DIO_Init();

/*******************************************************************************
 * @brief Initialize a pin as input or output.
 * @param[in] pin: The pin to be initialized: PIN0 ... PIN7
 * @param[in] port: The port of the pin: PORT_A ... PORT_G.
 * @param[in] direction: The direction of the pin: INPUT or OUTPUT.
 * @param[in] pullup: The pullup of the pin: PULLUP_TRUE or PULLUP_FALSE.
 ******************************************************************************/
void DIO_InitPin(PIN_t pin, PORT_t port, DIR_t direction, PULLUP_t pullup);

/*******************************************************************************
 * @brief write a value on the output pins, options are defined in STD_TYPES.h in the enum STATE_t
 * @param[in] pin: the pin to be initialized, PIN0, PIN1, ..., PIN7
 * @param[in] port: the port of the pin to be initialized, PORT_A, PORT_B, ..., PORT_G
 * @param[in] pinState: state of the pin, high or low, options are defined in STD_TYPES.h in the enum STATE_t
 * @par Example:
 *      @code DIO_WritePin(PIN0, PORT_A, HIGH);     // turns on pin 0 of port A         @endcode
 *      @code DIO_WritePin(PIN0, PORT_A, LOW);      // turns off pin 0 of port A        @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this function will do nothing.
 ******************************************************************************/
void DIO_WritePin(const PIN_t pin, const PORT_t port, const STATE_t pinState);

/*******************************************************************************
 * @brief write a value on a specific port (value of 8-bits ranges from 0 to 255)
 * @param[in] port: The port to be modified, PORT_A, PORT_B, ..., PORT_G
 * @param[in] value: value to set on the port (8 bits --> 0-255)
 * @par Example:
 *      @code DIO_WritePort(PORT_A, 0xFF);  // sets all pins of port A to high          @endcode
 *      @code DIO_WritePort(PORT_A, 0x00);  // sets all pins of port A to low           @endcode
 *      @code DIO_WritePort(PORT_A, 0xF0);  // sets pins 4, 5, 6, 7 of port A to high   @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this function will do nothing.
 ******************************************************************************/
void DIO_WritePort(const PORT_t port, const u8 value);

/*******************************************************************************
 * @brief Read the state of a pin
 * @param[in] pin the pin to be initialized, PIN0, PIN1, ..., PIN7
 * @param[in] port the port of the pin to be initialized, PORT_A, PORT_B, ..., PORT_G
 * @return state of the pin, HIGH or LOW
 * @par Example:
 *      @code DIO_ReadPin(PIN0, PORT_A);    // return the state of PIN0 on PORT A       @endcode
 *      @code DIO_ReadPin(PIN6, PORT_B);    // return the state of PIN6 on PORT B       @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this function will do nothing.
 ******************************************************************************/
STATE_t DIO_ReadPin(const PIN_t pin, const PORT_t port);

/*******************************************************************************
 * @brief Read the state of the port (8 bits --> 0-255)
 * @param[in] port the port to be read, PORT_A, PORT_B, ..., PORT_G
 * @return value of the port (8 bits --> 0-255)
 * @par Example:
 *      @code DIO_ReadPort(PORT_A);  // return 0xFF when all pins of PORT A are high    @endcode   
 *      @code DIO_ReadPort(PORT_A);  // return 0x00 when all pins of PORT A are low     @endcode
 *      @code DIO_ReadPort(PORT_A);  // return 0xF0 when pins (4~7) of PORT A are high  @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this function return LOW.
 ******************************************************************************/
u8 DIO_ReadPort(const PORT_t port);

#endif      /* DIO_H */