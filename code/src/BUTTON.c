/******************************************************************************
 * @file    BUTTON.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Button Management Module
 * @version 1.0.0
 * @date    2022-03-20
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "DIO.h"
#include "BUTTON.h"
#include "BUTTON_cfg.h"

void BUTTON_Init(void) {
    /* Do nothing   */
}

STATE_t BUTTON_GetStatus(BUTTON_t button) {
    STATE_t status = 0; /* returns HIGH if the bustton pressed and LOW if not    */
    u16 const DEBOUNCE_COUNTER  = 200; /* Debounce counter value   */
    u16 Local_u16pressedCounter = 0;

    /* Loop on configured button in cfg.c file */
    for(u8 idxButtons = 0; idxButtons < countButtonsConfigured; ++idxButtons) {
        /* check if the button exists in database   */
        if(button == buttonsConfigs[idxButtons].button) {
            /* check if debouncing button is needed   */
            switch(buttonsConfigs[idxButtons].debounceStatus) {
                case DEBOUNCE_ON:
                    /* check if the button is pressed */
                    for(u16 idxCounter = 0; idxCounter < DEBOUNCE_COUNTER; ++idxCounter) {
                        if(HIGH == DIO_ReadPin(buttonsConfigs[idxButtons].pin, buttonsConfigs[idxButtons].port)) {
                            ++Local_u16pressedCounter;
                        }
                    }

                    if(Local_u16pressedCounter >= DEBOUNCE_COUNTER) {
                        status = HIGH;
                    }else if( (Local_u16pressedCounter < DEBOUNCE_COUNTER) && (Local_u16pressedCounter > 0) ) {
                        if(ACTIVE_LOW == buttonsConfigs[idxButtons].ActiveHighOrLow) {
                            status = HIGH;
                        }
                    }else {
                        status = LOW;
                    }
                    break;

                case DEBOUNCE_OFF:
                    status = DIO_ReadPin(buttonsConfigs[idxButtons].pin, buttonsConfigs[idxButtons].port);
                    break;
                default:
                    /* DEBUG */
                    break;
            }   /* end switch of debounceStatus */

            if(ACTIVE_LOW == buttonsConfigs[idxButtons].ActiveHighOrLow) {
                (status == LOW) ? (status = HIGH) : (status = LOW);
            }
            /* Status of Active HIGH does not need changes  */ 

            break;  /* exit for loop    */

        }   /* end if button exists in database    */

    }   /* end for loop of searching button in database    */

    return status;
}
