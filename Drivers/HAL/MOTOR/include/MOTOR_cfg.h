/**
 *****************************************************************************
 * @file    MOTOR_cfg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   DC Motors Configurations header file
 * @version 0.1
 * @date    2021-08-26
 *****************************************************************************
 */
#ifndef MOTOR_CFG_H
#define MOTOR_CFG_H

#define MOTOR_DEFAULT_SPEED     50  /* Default speed = 50%  */
typedef struct
{
    MOTOR_t     motor;
    u8          in1_Pin;
    u8          in2_Pin;
    u8          pwmPin;
}MOTOR_CONGIG_t;

extern MOTOR_CONGIG_t MOTOR_configs[];
extern const u8 countMotorConfigs;

#endif