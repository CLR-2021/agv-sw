/**
 **************************************************************************************
 * @file    IR_Library.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   APIs of IR sensor library.
 * @version 0.1
 * @date    2021-08-12
 **************************************************************************************
 */

#ifndef IR_H
#define IR_H
/**
 **************************************************************************************
 *                                  Typedefs
 **************************************************************************************
 */
typedef enum{
    IR0,
    IR1,
    IR2,
    IR3,
    IR4,
    IR5,
    IR6,
    IR7
}IR_SENSOR_t;

/*
 **************************************************************************************
 *                                   APIs
 **************************************************************************************
 */
/**
 * @brief Initialize IR Array Configurations
 */
void IR_init(void);

/**
 * @brief   Get digital value of IR sensor
 * @param   sensor Number of the sensor to read; options defined in IR_SENSOR_t enum.
 * @return  STATE_t state of the sensor; HIGH if White, LOW if black.
 */
STATE_t IR_getValue(IR_SENSOR_t sensor);

#endif