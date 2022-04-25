/**********************************************************************************
 * @file    LED.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   LED Driver 
 * @version 1.0.0
 * @date    2022-02-01
 **********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "LED.h"
#include "LED_cfg.h"

/**********************************************************************************
 * @brief   Initialize LEDs Configurations
 **********************************************************************************/
void LED_Init(void) {
    /* do nothing   */
}

/**********************************************************************************
 * @brief Turn on/off a specific LED
 * @param[in] led: The LED to be turned on/off
 * @param[in] state: The state of the LED, either LED_ON or LED_OFF
 * @par Example:
 *      @code LED_Set(LED_0, LED_ON);   // turn on LED_0    @endcode
 *      @code LED_Set(LED_0, LED_OFF);  // turn off LED_0   @endcode
 **********************************************************************************/
void LED_TurnOnOff(const LED_t led, const LED_STATE_t state) { 
    for(u8 i = 0; i < countLedsConfigured; ++i) {
        if(led == ledConfigs[i].led) {
            DIO_WritePin(ledConfigs[i].pin, ledConfigs[i].port, state);
        }
    }
}

/**********************************************************************************
 * @brief Toggle state of a specific LED
 * @param[in] led: The LED to be oggles
 * @par Example:
 *      @code 
 *      LED_Toggle(LED_0);   // toggle LED_0: LED_0 will be turned on if it was off and vice versa 
 *      @endcode
 **********************************************************************************/
void LED_Toggle(const LED_t led) {
    for(u8 i = 0; i < countLedsConfigured; ++i) {
        if(led == ledConfigs[i].led) {
            if(HIGH == DIO_ReadPin(ledConfigs[i].pin, ledConfigs[i].port)) {
                DIO_WritePin(ledConfigs[i].pin, ledConfigs[i].port, LOW);
            }else {
                DIO_WritePin(ledConfigs[i].pin, ledConfigs[i].port, HIGH);
            }
        } else {
            /* do nothing */
        }
    }
}