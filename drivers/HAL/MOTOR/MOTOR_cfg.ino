/**
 ****************************************************************************
 * @file    MOTOR_cfg.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Dynamic code of DC Motors Driver.
 * @version 0.1
 * @date    2021-08-14
 *****************************************************************************
 */
#include "include/STD_TYPES.h"
#include "include/MOTOR.h"
#include "include/MOTOR_cfg.h"

/*
*************************************************************************************
*                            Motor driver Connections with pins          
*************************************************************************************
*/
MOTOR_CONGIG_t MOTOR_configs[] = {
    {MOTOR0, 7, 6, 11},
    {MOTOR1, 4, 3, 10},
};

const u8 countMotorConfigs = sizeof(MOTOR_configs) / sizeof(MOTOR_CONGIG_t);