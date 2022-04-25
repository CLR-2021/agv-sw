/**************************************************************************************
 * @file    IR_Library.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   IR sensors array used in Line follwer applications.
 * @version 1.0.0
 * @date    21 Aug 2021
 *************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "IR.h"
#include "IR_cfg.h"

void IR_Init(void) {
    /* Do nothing */
}

STATE_t IR_GetStatus(IR_SENSOR_t sensor) {
  STATE_t state = LOW;
  u8 i = 0;   /* Don't define it in the for loop as it will be used outside the for loop */

  for(i = 0; i < countIRSensorsConfigured; ++i) {
    if(sensor == IR_configs[i].sensor) {
      state = DIO_ReadPin(IR_configs[i].pin, IR_configs[i].port);
      break;
    }
  }

  /* Check if the IR returns LOW for white color  */
  if( ACTIVE_LOW == IR_configs[i].ActiveHighOrLow ) { 
    if(state == HIGH) {
      state = LOW;
    }else {
      state = HIGH;
    }
  }

  return state;
}

u32 IR_ScanAll(void) {
  u32 result = 0;

  for(u8 i = 0; i < countIRSensorsConfigured; ++i) {
    result |= (IR_GetStatus(IR_configs[i].sensor) << i);
  }

  return result;
}

u8 IR_GetCount(void) {
  return countIRSensorsConfigured;
}