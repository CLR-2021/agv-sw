/**
 ****************************************************************************
 * @file    main.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Check Functionality of Dual DC motor driver
 * @version 0.1
 * @date    2021-08-14
 * @details This example shows how to drive two motors using the PWM and DIR pins.
 *          This is done using dual channel motor driver, both channel work the same way.
 * CONNECTIONS: Arduino D11 <--> Left Motor Driver PWM Input
 *              Arduino D10 <--> Right Motor Driver PWM Input
 *              Arduino D6  <--> Left Motor Driver DIR Input 1
 *              Arduino D7  <--> Left Motor Driver DIR Input 2
 *              Arduino D4  <--> Right Motor Driver DIR Input 1
 *              Arduino D3  <--> Right Motor Driver DIR Input 2
 *              Arduino GND <--> Motor Driver GND
 * @note    Motors connections can be found in DUAL_MOTOR_cfg.ino
 * ***************************************************************************
 */
#include "include/STD_TYPES.h"
#include "include/DUAL_MOTOR.h"

void setup()
{
    /* Initializations      */
    DUAL_MOTOR_init();
}

void loop(){
 
    /* Rotate Robot Forward with full speed (100%)  */
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_FWD  , 100 );
    delay(1500);

    /* Rotate Robot Forward with default speed  */
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_FWD  );
    delay(1500);

    /* Rotate Robot Backward with full speed (100%)  */
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_BACK , 100 );
    delay(1500);

    /* Rotate Robot Backward with default speed  */
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_BACK );
    delay(1500);

    /* Rotate Robot Right with full speed (100%)  */
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_RIGHT  , 100);
    delay(1500);

    /* Rotate Robot Right with default speed  */
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_RIGHT  );
    delay(1500);

    /* Rotate Robot Left with full speed (100%)  */
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_LEFT , 100);
    delay(1500);

    /* Rotate Robot Right with default speed */
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_LEFT );
    delay(1500);
}
            