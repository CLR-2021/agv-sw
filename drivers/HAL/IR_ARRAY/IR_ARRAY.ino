/**
 **************************************************************************************
 * @file    IR_Library.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   IR sensors array used in Line follwer applications.
 * @version 0.1
 * @date    21 Aug 2021
 **************************************************************************************
 */

#include "include/STD_TYPES.h"
#include "include/IR.h"
#include "include/IR_ARRAY.h"
#include "include/IR_ARRAY_cfg.h"

/**
 * @brief Allocating memory for IR sensors' to store their values in
 */
u8 * IR_Values = (u8 *) calloc(countIRSensors, sizeof(u8));

/**
 * @brief   Scan values of IR sensors
 * @details Scan values of IR sensors, and if:
 *          1. Sensor = HIGH if ON TRACK.
 *          2. Sensor = LOW if NOT ON TRACK.
 *          Then store these values in the array --> IR_Values[]
 */     
void scanIR_Sensors(void){
    u8 idx = 0;

    /**
     * @details Scan IR Sensors, each sensor gets:
     *          1. HIGH if ON WHITE surface.
     *          2. LOW if ON BLACK surface.  
     */
    for(idx = 0; idx < countIRSensors; idx++){
        IR_Values[IR_arrayConfigs[idx].IRSensorIndex] = IR_getValue(IR_arrayConfigs[idx].sensorNumber);
    }

    /**
     * @details If track color is WHITE, toggle IR sensors values to be
     *          1. HIGH if ON TRACK.
     *          2. LOW if NOT ON TRACK  
     */
    if(TRACK_COLOR == WHITE_TRACK){
        for(idx = 0; idx < countIRSensors; idx++){
            /* Toggle bit   */
            IR_Values[IR_arrayConfigs[idx].IRSensorIndex] ^= (1 << IR_arrayConfigs[idx].IRSensorIndex);   
        }
    }
}
