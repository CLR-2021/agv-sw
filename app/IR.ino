/**
 **************************************************************************************
 * @file    IR.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   IR sensor library.
 * @version 0.1
 * @date    21 Aug 2021
 **************************************************************************************
 */

#include "include/STD_TYPES.h"
#include "include/IR.h"
#include "include/IR_cfg.h"


/**
 * @brief Initialize IR Array Configurations
 */
void IR_init(void)
{
  u8 idx = 0;

  /*
   *************************************************************************************
   *                            IR Sensors pins configuration as inputs         
   *************************************************************************************
  */
  for (idx = 0; idx < countIRConfigs; idx++){
    pinMode(IR_configs[idx].pin, INPUT);
  }
}

#if 0
/**
 * @brief   Scan IR sensors
 * @details Scan IR sensor array and write them on their corresponding variables, which are
 *          defined under comment "IR sensors variables to store states of sensors"
 * @param   extLeftSensor   pointer to u8 store the value of Extra Left   IR sensor.
 * @param   leftSensor      pointer to u8 store the value of Left         IR sensor.
 * @param   righttSensor    pointer to u8 store the value of Extra Right  IR sensor.
 * @param   extRightSensor  pointer to u8 store the value of Extra Right  IR sensor.
 */
void IR_getValues(u8 * extLeftSensor, u8 * leftSensor, u8 * righttSensor, u8 * extRightSensor)
{
  /* Read sensor 1 ==> extra left   */
  * extLeftSensor  = digitalRead(EXTRA_LEFT_IR_SENSOR_PIN);
  
  /* Read sensor 2 ==> left         */
  * leftSensor  = digitalRead(LEFT_IR_SENSOR_PIN);
    
  /* Read sensor 3 ==> right        */
  * righttSensor  = digitalRead(RIGHT_IR_SENSOR_PIN);
  
  /* Read sensor 4 ==> extra right  */
  * extRightSensor  = digitalRead(EXTRA_RIGHT_IR_SENSOR_PIN);  
}

#elif 1
/**
 * @brief   Get digital value of IR sensor
 * @param   sensor Number of the sensor to read; options defined in IR_SENSOR_t enum.
 * @return  STATE_t state of the sensor; HIGH if White, LOW if black.
 */
STATE_t IR_getValue(IR_SENSOR_t sensor)
{
  u8 idx = 0;
  STATE_t state = LOW;

  for (idx = 0; idx < countIRConfigs; idx++){
    if (sensor == IR_configs[idx].sensor){
      state = (STATE_t)digitalRead(IR_configs[idx].pin);
      break;
    }
  }

  if(idx == countIRConfigs){
    /* No Sensor detected */
    /* Error              */
  }

  /* Check if the IR returns LOW for white color  */
  if((u8)IR_WHITE_VALUE == (u8)LOW){    /* Reverse state value  */
    if(state == HIGH){
      state = LOW;
    }else{
      state = HIGH;
    }
  }

  return state;
}
#endif