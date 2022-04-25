/**************************************************************************
 * @file    LIFTER.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Lifter module that control the movement of the lifter actuator
 * @details This module uses TB6560 motor driver to control the LIFTER. 
 *          TB6560 is configured to use a stepper motor. And connected in 
 *          common-anode mode: PUL-, DIR-, and EN- are connected to GND.
 * @version 1.0.0
 * @date    2022-02-09
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO.h"
#include "LIFTER.h"
#include "LIFTER_cfg.h"

/******************************************************************************
 ******************************************************************************
 *                        PRIVATE FUNCTIONS IMPLEMENTATION                    *   
 ******************************************************************************
 *****************************************************************************/

/*******************************************************************************
 * @brief Set the direction of the lifter: up or down.
 * @param[in] dir: The direction of the movement: LIFTER_UP or LIFTER_DOWN
 ******************************************************************************/
static void LIFTER_SetDirection(const LIFTER_DIR_t dir) {
    if(LIFTER_UP == dir) {
        DIO_WritePin(LifterConfigs.directionPin, LifterConfigs.directionPinPort, HIGH);
    }
    else {
        DIO_WritePin(LifterConfigs.directionPin, LifterConfigs.directionPinPort, LOW);
    }
}

/*******************************************************************************
 * @brief Send pulses to the motor driver to move the lifter.
 * @param[in] pulsesPerSecond: The number of pulses per second to send to the motor.
 * @param[in] overallSeconds: The number of seconds to send pulses for.
 ******************************************************************************/
static void LIFTER_SendPulses(const u32 pulsesPerSecond, const u8 overallSeconds) {
    const u32   usInSecond = 1000000UL;
    u8          usPerPulse = 0;
    double      pulseDelay = 0.0;


    usPerPulse = usInSecond / pulsesPerSecond;  
    pulseDelay = (double)usPerPulse / 2.0;

    /************************************************************************
     * @brief Send the required number of pulses to the lifter
     * @note For greater timing accuracy, increase revolutionStroke and decrease speed and pulsesPerRevolution   
     *          Best results are obtained when speed = revolutionStroke, and pulsesPerRevolution <= 800
     * @note _delay_us loses accuracu with smaller values when used inside a bigger loop
     * **********************************************************************/
    for(u32 i = 0; i < (pulsesPerSecond * overallSeconds); ++i) {
        DIO_WritePin(LifterConfigs.pulsePin, LifterConfigs.pulsePinPort, HIGH);
        _delay_us(pulseDelay);
        DIO_WritePin(LifterConfigs.pulsePin, LifterConfigs.pulsePinPort, LOW);
        _delay_us(pulseDelay);
    }
}

/*******************************************************************************
 * @brief Move the lifter to the desired position: up or down.
 * @note This function is called by the other two functions: LIFTER_MoveUp and 
 *       LIFTER_MoveDown
 * @param[in] direction: The direction of the movement
 ******************************************************************************/
static void LIFTER_Move(const LIFTER_DIR_t dir) {
    u32 pulsesPerSecond = 0;
    u8  overallSeconds  = 0;

    /* pulsesPerSecond = speed * pulsesPerRevolution / revolutionStroke */
    /* time = requiredStrokeDistance / speed */
    /* revolutionsPerSecond = speed / revolutionStroke */
    overallSeconds = (u8)LifterConfigs.overallStroke / (u8)LifterConfigs.speed;
    if(overallSeconds == 0) {
        /* DEBUG */
    }

    pulsesPerSecond = (u32)LifterConfigs.speed * (u32)LifterConfigs.pulsesPerRevolution / LifterConfigs.revolutionStroke;

    #if(ENABLE_CONNECTION == 1)
    LIFLER_Enable();
    #endif
    LIFTER_SetDirection(dir);
    LIFTER_SendPulses(pulsesPerSecond, overallSeconds);
}


/******************************************************************************
 ******************************************************************************
 *                        API FUNCTIONS IMPLEMENTATION                        *
 ******************************************************************************
 *****************************************************************************/

/*******************************************************************************
 * @brief Initialize the LIFTER module.
 ******************************************************************************/
void LIFTER_Init(void) {
    /* Do nothing */
}

/******************************************************************************
 * @brief Move the lifter up until it reaches the top
 *****************************************************************************/
void LIFTER_MoveUp(void) {
    LIFTER_Move(LIFTER_UP);
}

/*******************************************************************************
 * @brief Move the lifter down until it reaches the bottom
 ******************************************************************************/
void LIFTER_MoveDown(void) {
    LIFTER_Move(LIFTER_DOWN);
}

/*******************************************************************************
 * @brief Enable the lifter motor
 ******************************************************************************/
void LIFTER_Enable(void) {
    DIO_WritePin(LifterConfigs.enablePin, LifterConfigs.enablePinPort, HIGH);
}

/*******************************************************************************
 * @brief Disable the lifter motor
 ******************************************************************************/
void LIFTER_Disable(void) {
    DIO_WritePin(LifterConfigs.enablePin, LifterConfigs.enablePinPort, LOW);
}

/*******************************************************************************
 * @brief Set the speed of the lifter motor
 * @param[in] speed: The speed of the lifter motor
 ******************************************************************************/
void LIFTER_SetSpeed(const u8 speed) {
    LifterConfigs.speed = speed;
}

/*******************************************************************************
 * @brief Set the stroke of the lifter motor per revolution in mm
 * @param[in] overallStroke: The stroke of the lifter motor per revolution in mm
 ******************************************************************************/
void LIFTER_SetOverallStroke(const u8 overallStroke) {
    LifterConfigs.overallStroke = overallStroke;
}

/*******************************************************************************
 * @brief Set the number of pulses per revolution
 * @param[in] pulsesPerRevolution: The number of pulses per revolution
 ******************************************************************************/
void LIFTER_SetPulsesPerRevolution(const u16 pulsesPerRevolution) {
    LifterConfigs.pulsesPerRevolution = pulsesPerRevolution;
}

/*******************************************************************************
 * @brief Set the distance per revolution
 * @param[in] revolutionStroke: The distance per revolution in mm
 ******************************************************************************/
void LIFTER_SetRevolutionStroke(const u8 revolutionStroke) {
    LifterConfigs.revolutionStroke = revolutionStroke;
}