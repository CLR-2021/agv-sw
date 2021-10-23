/**
 *****************************************************************************
 * @file    MOTOR.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   DC Motors Interfaces
 * @version 0.1
 * @date    2021-08-26
 *****************************************************************************
 */
#ifndef MOTOR_H
#define MOTOR_H

/**
 ******************************************************************************
 *                                  Typedefs & Macros
 ******************************************************************************
 */
typedef enum{
    MOTOR0,
    MOTOR1,
    MOTOR2,
    MOTOR3,
}MOTOR_t;

typedef enum{
    MOTOR_STOP,
    MOTOR_FWD,
    MOTOR_BACK,
}MOTOR_DIR_t;

/*
 *******************************************************************************
 *                                   APIs
 *******************************************************************************
 */

/**
 * @brief Initialize Motor Driver Configurations
 */
void MOTOR_init(void);

/**
 * @brief Rotate a specific motor forward, backward, or stop it.
 * @param motor The motor to rotate; options specified in MOTOR_t enum.
 * @param direction Direction to rotate motor with; options specified in MOTOR_DIR_t enum.
 * @param motorSpeed Speed of motor as a percentage.
 * @details Rotating motor forward or backward, motors rotates at a speed of motorSpeed
 *          parameter.
 *          With stop motor, speed does not matter, motor stops whatever speed is passed.
 */
void MOTOR_rotate(MOTOR_t motor, MOTOR_DIR_t direction, u8 motorSpeed);

/**
 * @brief Rotate a specific motor forward, backward, or stop it.
 * @param motor The motor to rotate; options specified in MOTOR_t enum.
 * @param direction Direction to rotate motor with; options specified in MOTOR_DIR_t enum.
 * @param motorSpeed Speed of motor as a percentage.
 * @details When rotating motor forward or backward, motors rotates at a speed defined 
 *          with MOTOR_DEFAULT_SPEED macro in configurations header file.
 */
void MOTOR_rotate(MOTOR_t motor, MOTOR_DIR_t direction);

#endif