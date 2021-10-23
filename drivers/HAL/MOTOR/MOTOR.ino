/**
 *****************************************************************************
 * @file    MOTOR.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Static code of DC Motor Driver with Direction and Speed Control.
 * @version 0.1
 * @date    2021-08-26
 *****************************************************************************
 */
#include "include/STD_TYPES.h"
#include "include/MOTOR.h"
#include "include/MOTOR_cfg.h"

void MOTOR_init(void)
{
    u8 idx = 0;

    for (idx = 0; idx < countMotorConfigs; idx++){
        /*
        *************************************************************************************
        *                            Motor driver pins configuration as outputs         
        *************************************************************************************
        */
        pinMode(MOTOR_configs[idx].in1_Pin  , OUTPUT);
        pinMode(MOTOR_configs[idx].in2_Pin  , OUTPUT);
        pinMode(MOTOR_configs[idx].pwmPin   , OUTPUT);

        /*
        *************************************************************************************
        *                            Pulling all control pins down at start-up         
        *************************************************************************************
        */
        digitalWrite(MOTOR_configs[idx].in1_Pin , LOW);
        digitalWrite(MOTOR_configs[idx].in2_Pin , LOW);
        analogWrite(MOTOR_configs[idx].pwmPin   , 255);       
    }
}

void MOTOR_rotate(MOTOR_t motor, MOTOR_DIR_t direction, u8 motorSpeed)
{
    switch(direction)
    {
        case MOTOR_FWD  :       MOTOR_forward(motor, motorSpeed);       break;        
        case MOTOR_BACK :       MOTOR_back(motor, motorSpeed);          break;
        case MOTOR_STOP :       MOTOR_stop(motor);                      break;

        default:
        /* Invalid state    */  
        break;    
    }
}

void MOTOR_rotate(MOTOR_t motor, MOTOR_DIR_t direction)
{
    switch(direction)
    {
        case MOTOR_FWD  :       MOTOR_forward(motor , MOTOR_DEFAULT_SPEED);     break;        
        case MOTOR_BACK :       MOTOR_back(motor    , MOTOR_DEFAULT_SPEED);     break;
        case MOTOR_STOP :       MOTOR_stop(motor);                              break;

        default:
        /* Invalid state    */  
        break;    
    }
}

static void MOTOR_forward(MOTOR_t motor, u8 motorSpeed){
    u8 idx = 0;
    /* Convert from percentage value (0 ~ 100) to PWM analog vlaue (0 ~ 255)    */
    motorSpeed = (motorSpeed * 255) / 100;

    for (idx = 0; idx < countMotorConfigs; idx++){
        if(motor == MOTOR_configs[idx].motor){
            /* Starting mode for        */
            analogWrite(MOTOR_configs[idx].pwmPin, motorSpeed);

            digitalWrite(MOTOR_configs[idx].in1_Pin    , HIGH );
            digitalWrite(MOTOR_configs[idx].in2_Pin    , LOW  );
        }
    }
}

static void MOTOR_back(MOTOR_t motor, u8 motorSpeed){
    u8 idx = 0;
    /* Convert from percentage value (0 ~ 100) to PWM analog vlaue (0 ~ 255)    */
    motorSpeed = (motorSpeed * 255) / 100;

    for (idx = 0; idx < countMotorConfigs; idx++){
        if(motor == MOTOR_configs[idx].motor){
            /* Starting mode for        */
            analogWrite(MOTOR_configs[idx].pwmPin   , motorSpeed);

            digitalWrite(MOTOR_configs[idx].in1_Pin    , LOW   );
            digitalWrite(MOTOR_configs[idx].in2_Pin    , HIGH  );
        }
    }
}

static void MOTOR_stop(MOTOR_t motor){
    u8 idx = 0;

    for (idx = 0; idx < countMotorConfigs; idx++){
        if(motor == MOTOR_configs[idx].motor){
            analogWrite(MOTOR_configs[idx].pwmPin   , 0);

            digitalWrite(MOTOR_configs[idx].in1_Pin    , LOW   );
            digitalWrite(MOTOR_configs[idx].in2_Pin    , LOW  );
        }
    }
}
            