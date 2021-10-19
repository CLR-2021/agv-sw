/**
 ****************************************************************************
 * @file    MOTOR_cfg.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Dynamic code of Dual DC Motors Driver.
 * @version 0.1
 * @date    2021-08-14
 *****************************************************************************
 */
#include "include/STD_TYPES.h"
#include "include/DUAL_MOTOR.h"
#include "include/DUAL_MOTOR_cfg.h"

/*
*************************************************************************************
*                            Motor driver Connections with pins          
*************************************************************************************
*/
DUAL_MOTOR_CONGIG_t DUAL_MOTOR_configs[] = {
    {DUAL_MOTOR0, 7, 6, 4, 3, 11, 10},
};

const u8 countDualMotorConfigs = sizeof(DUAL_MOTOR_configs) / sizeof(DUAL_MOTOR_CONGIG_t);