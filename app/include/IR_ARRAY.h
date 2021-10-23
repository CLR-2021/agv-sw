/**
 **************************************************************************************
 * @file    IR_ARRAY.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   APIs of IR sensors array.
 * @version 0.1
 * @date    12 Sep 2021
 **************************************************************************************
 */

#ifndef IR_ARRAY_H
#define IR_ARRAY_H

/**
 **************************************************************************************
 *                                Configurations
 **************************************************************************************
 */
/**
 * @brief   Indixes of IR sensors to stor in array (IR_Values). 
 * @note    This is only valid when only 4 sensors are used
 */
typedef enum{
    EXTRA_LEFT_IR_SENSOR     = 0,
    LEFT_IR_SENSOR           = 1,
    RIGHT_IR_SENSOR          = 2,
    EXTRA_RIGHT_IR_SENSOR    = 3,
}IR_SENSOR_INDEX_t;

/**
 **************************************************************************************
 *                                DO NOT CHANGE ANYTHING BELOW
 **************************************************************************************
 */
/**
 * @brief Allocating memory for IR sensors' to store their values in
 */
extern u8 * IR_Values;

/**
 * @brief   Scan values of IR sensors
 * @details Scan values of IR sensors, and if:
 *          1. Sensor = HIGH if ON TRACK.
 *          2. Sensor = LOW if NOT ON TRACK.
 *          Then store these values in the array --> IR_Values[]
 */     
void scanIR_Sensors(void);

/**
 * @brief Counting number of IR Sensors  
 */
extern u8 countIRSensors;

#endif