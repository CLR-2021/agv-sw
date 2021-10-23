/**
 *****************************************************************************
 * @file    MOTOR_cfg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Dual DC Motors Configurations header file
 * @version 0.1
 * @date    2021-08-26
 *****************************************************************************
 */
#ifndef DUAL_MOTOR_CFG_H
#define DUAL_MOTOR_CFG_H

#define DUAL_MOTOR_DEFAULT_SPEED     50  /* Default speed = 50%  */

typedef struct
{
    DUAL_MOTOR_t    dualMotorNum;
    u8              in1_Pin;
    u8              in2_Pin;
    u8              in3_Pin;
    u8              in4_Pin;
    u8              pwmPin1;
    u8              pwmPin2;
}DUAL_MOTOR_CONGIG_t;

extern DUAL_MOTOR_CONGIG_t DUAL_MOTOR_configs[];
extern const u8 countDualMotorConfigs;

#endif