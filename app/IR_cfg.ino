/**
 **************************************************************************************
 * @file    IR_cfg.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Runtime configurations of IR sensor.
 * @version 0.1
 * @date    21 Aug 2021
 **************************************************************************************
 */

#include "include/STD_TYPES.h"
#include "include/IR.h"
#include "include/IR_cfg.h"
/**
 * @brief Mapping between IR sensors and microcontroller pins
 * 
 * @note  To add extra sensors, check if IR_SENSOR_t enumerator contains them. 
 *        If not, add them.
 */
IR_CONFIG_t IR_configs[] = {
    {IR0, A0 },  /* IR0 connected to pin 8   */
    {IR1, A1 },  /* IR1 connected to pin 9   */
    {IR2, A2 },  /* IR2 connected to pin 10  */
    {IR3, A3 },  /* IR3 connected to pin 11  */
};

const u8 countIRConfigs = sizeof(IR_configs) / sizeof(IR_CONFIG_t);