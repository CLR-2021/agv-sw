/**
 **************************************************************************************
 * @file    IR_ARRAY_cfg.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Runtime configurations of IR sensors array.
 * @version 0.1
 * @date    12 Sep 2021
 **************************************************************************************
 */

#include "include/STD_TYPES.h"
#include "include/IR.h"
#include "include/IR_ARRAY.h"
#include "include/IR_ARRAY_cfg.h"


/**
 * @brief Mapping between IR sensors' numbers and their 
 *        indexes in the array (IR_Values[])
 */
IR_ARRAY_CONFIGS_t IR_arrayConfigs[] = {
    {EXTRA_LEFT_IR_SENSOR   , IR0},
    {LEFT_IR_SENSOR         , IR1},
    {RIGHT_IR_SENSOR        , IR2},
    {EXTRA_RIGHT_IR_SENSOR  , IR3},
};

/**
 * @brief Counting number of IR Sensors  
 */
u8 countIRSensors = sizeof(IR_arrayConfigs) / sizeof(IR_ARRAY_CONFIGS_t);