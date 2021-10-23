/**
 **************************************************************************************
 * @file    IR_Library.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Runtime configurations of IR array.
 * @version 0.1
 * @date    21 Aug 2021
 **************************************************************************************
 */

#include "include/STD_TYPES.h"
#include "include/IR.h"
#include "include/IR_cfg.h"

IR_CONFIG_t IR_configs[] = {
    {IR0, A0 },
    {IR1, A1 },
    {IR2, A2 },
    {IR3, A3 },
};

const u8 countIRConfigs = sizeof(IR_configs) / sizeof(IR_CONFIG_t);