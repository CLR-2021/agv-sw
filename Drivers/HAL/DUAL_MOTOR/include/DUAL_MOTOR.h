/**
 *****************************************************************************
 * @file    MOTOR.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   DC Motors Interfaces
 * @version 0.1
 * @date    2021-08-26
 *****************************************************************************
 */
#ifndef DUAL_MOTOR_H
#define DUAL_MOTOR_H

/**
 ******************************************************************************
 *                                  Typedefs & Macros
 ******************************************************************************
 */
typedef enum{
    DUAL_MOTOR0,
    DUAL_MOTOR1,
    DUAL_MOTOR2,
    DUAL_MOTOR3,
}DUAL_MOTOR_t;

typedef enum{
    DUAL_MOTOR_STOP  ,
    DUAL_MOTOR_FWD   ,
    DUAL_MOTOR_BACK  ,
    DUAL_MOTOR_RIGHT ,
    DUAL_MOTOR_LEFT  ,
}DUAL_MOTOR_DIR_t;

/*
 *******************************************************************************
 *                                   APIs
 *******************************************************************************
 */

/**
 * @brief Initialize Motor Driver Configurations
 */
void DUAL_MOTOR_init(void);

/**
 * @brief Rotate a specific motor forward, backward, or stop it.
 * @param motor The motor to rotate; options specified in MOTOR_t enum.
 * @param direction Direction to rotate motor with; options specified in MOTOR_DIR_t enum.
 * @param motorSpeed Speed of motor as a percentage.
 * @details Rotating motor forward or backward, motors rotates at a speed of motorSpeed
 *          parameter.
 *          With stop motor, speed does not matter, motor stops whatever speed is passed.
 */
void DUAL_MOTOR_rotate(DUAL_MOTOR_t dualMotorNum, DUAL_MOTOR_DIR_t direction, u8 speed);

/**
 * @brief Rotate a specific motor forward, backward, or stop it.
 * @param motor The motor to rotate; options specified in MOTOR_t enum.
 * @param direction Direction to rotate motor with; options specified in MOTOR_DIR_t enum.
 * @param motorSpeed Speed of motor as a percentage.
 * @details When rotating motor forward or backward, motors rotates at a speed defined 
 *          with MOTOR_DEFAULT_SPEED macro in configurations header file.
 */
void DUAL_MOTOR_rotate(DUAL_MOTOR_t dualMotorNum, DUAL_MOTOR_DIR_t direction);

#endif