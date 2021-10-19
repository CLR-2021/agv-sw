/**
 **************************************************************************************
 * @file    IR_ARRAY_cfg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Configurations of IR array (types, macros, ...).
 * @version 0.1
 * @date    21 Aug 2021
 **************************************************************************************
 */

#ifndef IR_CFG_H
#define IR_CFG_H
/**
 **************************************************************************************
 *                                Configurations
 **************************************************************************************
 */
/**
 * @brief Color detected from sensors
 * @note  Color values depends on IR module. 
 *        So, check module datasheet to verify mapped return values for black and white colors.
 * 
 */
typedef enum{
  IR_BLACK_VALUE = HIGH,
  IR_WHITE_VALUE = LOW,
}IR_COLOR_t;

/**
 **************************************************************************************
 *                                Do not change anything below
 **************************************************************************************
 */
typedef struct
{
  IR_SENSOR_t sensor;
  u8          pin;
}IR_CONFIG_t;

extern IR_CONFIG_t IR_configs[];
extern const u8 countIRConfigs;

#endif