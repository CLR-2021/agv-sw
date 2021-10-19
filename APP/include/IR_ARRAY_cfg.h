/**
 **************************************************************************************
 * @file    IR_ARRAY_cfg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Configurations of IR array (types, macros, ...).
 * @version 0.1
 * @date    21 Aug 2021
 **************************************************************************************
 */

#ifndef IR_ARRAY_CFG_H
#define IR_ARRAY_CFG_H

/**
 **************************************************************************************
 *                                Configurations
 **************************************************************************************
 */
/**
 * @brief Color of the track: Options in Track_Color enumerator
 */
#define TRACK_COLOR     BLACK_TRACK

/**
 **************************************************************************************
 *                                DO NOT CHANGE ANYTHING BELOW
 **************************************************************************************
 */
typedef enum{
    BLACK_TRACK,
    WHITE_TRACK
}Track_Color;

typedef struct{
    IR_SENSOR_INDEX_t   IRSensorIndex;
    IR_SENSOR_t         sensorNumber;
}IR_ARRAY_CONFIGS_t;

extern IR_ARRAY_CONFIGS_t IR_arrayConfigs[];

#endif