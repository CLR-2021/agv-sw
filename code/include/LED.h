/******************************************************************************
 * @file    LED.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Interfaces header file for \ref LED.c
 * @version 1.0.0
 * @date    2022-03-20
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#ifndef LED_H       
#define LED_H      

/********************************************************************************
 ********************************************************************************
 *                                  TYPEDEFS
 ********************************************************************************
 ********************************************************************************/
typedef enum {
    LED_0,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
}LED_t;

typedef enum{
    LED_OFF,
    LED_ON
}LED_STATE_t;

/********************************************************************************
 ********************************************************************************
 *                               API's
 ********************************************************************************
 ********************************************************************************/

/********************************************************************************
 * @brief Initializes LEDs connected to DIO
 ********************************************************************************/
void LED_Init(void);

/********************************************************************************
 * @brief Turns on/off a specific LED
 * @param[in] led: the LED to be turned on/off, LED_0 to LED_7
 * @param[in] state: the state of the LED, LED_ON or LED_OFF
 * @par For example:
 *      * LED_TurnOnOff(LED_0, LED_ON) turns on LED_0
 *      * LED_TurnOnOff(LED_0, LED_OFF) turns off LED_0
 ********************************************************************************/
void LED_TurnOnOff(LED_t led, LED_STATE_t state);

/**********************************************************************************
 * @brief Toggle state of a specific LED
 * @param[in] led: the LED to be turned on/off
 * @example LED_Toggle(LED_0);
 **********************************************************************************/
void LED_Toggle(LED_t led);

#endif     /* LED_H */              
