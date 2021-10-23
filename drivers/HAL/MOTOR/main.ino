/**
 ****************************************************************************
 * @file    main.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Check Functionality of DC motor driver
 * @version 0.1
 * @date    2021-08-14
 * @details This example shows how to drive a motor using the PWM and DIR pins.
 *          This example only shows how to drive a single motor for simplicity.
 *          For dual channel motor driver, both channel work the same way.
 * CONNECTIONS: Arduino D11 <--> Left Motor Driver PWM Input
 *              Arduino D10 <--> Right Motor Driver PWM Input
 *              Arduino D6  <--> Left Motor Driver DIR Input 1
 *              Arduino D7  <--> Left Motor Driver DIR Input 2
 *              Arduino D4  <--> Right Motor Driver DIR Input 1
 *              Arduino D3  <--> Right Motor Driver DIR Input 2
 *              Arduino GND <--> Motor Driver GND
 * @note    Motors connections can be found in MOTOR_cfg.ino
 * ***************************************************************************
 */
#include "include/STD_TYPES.h"
#include "include/MOTOR.h"

void setup()
{
    /* Initializations      */
    MOTOR_init();
}

void loop(){
 
    /* Rotate Robot Forward with full speed (100%)  */
    MOTOR_rotate(MOTOR0, MOTOR_FWD  , 100 );
    MOTOR_rotate(MOTOR1, MOTOR_FWD  , 100 );
    delay(1500);

    /* Rotate Robot Forward with default speed  */
    MOTOR_rotate(MOTOR0, MOTOR_FWD  );
    MOTOR_rotate(MOTOR1, MOTOR_FWD  );
    delay(1500);

    /* Rotate Robot Backward with full speed (100%)  */
    MOTOR_rotate(MOTOR0, MOTOR_BACK , 100 );
    MOTOR_rotate(MOTOR1, MOTOR_BACK , 100 );
    delay(1500);

    /* Rotate Robot Backward with default speed  */
    MOTOR_rotate(MOTOR0, MOTOR_BACK );
    MOTOR_rotate(MOTOR1, MOTOR_BACK );
    delay(1500);

    /* Rotate Robot Right with full speed (100%)  */
    MOTOR_rotate(MOTOR0, MOTOR_FWD  , 100);
    MOTOR_rotate(MOTOR1, MOTOR_BACK , 100);
    delay(1500);

    /* Rotate Robot Right with default speed  */
    MOTOR_rotate(MOTOR0, MOTOR_FWD  );
    MOTOR_rotate(MOTOR1, MOTOR_BACK );
    delay(1500);

    /* Rotate Robot Left with full speed (100%)  */
    MOTOR_rotate(MOTOR0, MOTOR_BACK , 100);
    MOTOR_rotate(MOTOR1, MOTOR_FWD  , 100);
    delay(1500);

    /* Rotate Robot Right with default speed */
    MOTOR_rotate(MOTOR0, MOTOR_BACK );
    MOTOR_rotate(MOTOR1, MOTOR_FWD  );
    delay(1500);
}
            