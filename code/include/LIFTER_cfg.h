/******************************************************************************
 * @file    LIFTER_cfg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Configuration header file for \ref LIFTER.c
 * @version 1.0.0
 * @date    2022-03-20
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#ifndef LIFTER_CFG_H
#define LIFTER_CFG_H

/*******************************************************************************
 * @brief If you are using enable pin, Write 1, else write 0
 ******************************************************************************/
#define ENABLE_CONNECTION 0

/*******************************************************************************
 * DO NOT CHANGE ANYTHING BELOW THIS LINE
 ******************************************************************************/
typedef enum{
    LIFTER_UP,
    LIFTER_DOWN,
}LIFTER_DIR_t;

typedef struct{
    PIN_t       directionPin;
    PORT_t      directionPinPort;
    PIN_t       pulsePin;
    PORT_t      pulsePinPort;
    PIN_t       enablePin;
    PORT_t      enablePinPort;
    u8          overallStroke;
    u16         pulsesPerRevolution;
    u8          revolutionStroke;
    u8          speed;
}LIFTER_CONFIGS_t;

extern LIFTER_CONFIGS_t LifterConfigs;

#endif                  
