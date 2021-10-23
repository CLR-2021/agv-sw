/**
 *****************************************************************************
 * @file    MOTOR.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Static code of Dual DC Motor Driver with Direction and Speed Control.
 * @version 0.1
 * @date    2021-08-26
 *****************************************************************************
 */
#include "include/STD_TYPES.h"
#include "include/DUAL_MOTOR.h"
#include "include/DUAL_MOTOR_cfg.h"

void DUAL_MOTOR_init(void)
{
    u8 idx = 0;

    for (idx = 0; idx < countDualMotorConfigs; idx++){
        /*
        *************************************************************************************
        *                            Motor driver pins configuration as outputs         
        *************************************************************************************
        */
        pinMode(DUAL_MOTOR_configs[idx].in1_Pin  , OUTPUT);
        pinMode(DUAL_MOTOR_configs[idx].in2_Pin  , OUTPUT);
        pinMode(DUAL_MOTOR_configs[idx].in3_Pin  , OUTPUT);
        pinMode(DUAL_MOTOR_configs[idx].in4_Pin  , OUTPUT);
        pinMode(DUAL_MOTOR_configs[idx].pwmPin1  , OUTPUT);
        pinMode(DUAL_MOTOR_configs[idx].pwmPin2  , OUTPUT);

        /*
        *************************************************************************************
        *                            Pulling all control pins down at start-up         
        *************************************************************************************
        */
        digitalWrite(DUAL_MOTOR_configs[idx].in1_Pin , LOW);
        digitalWrite(DUAL_MOTOR_configs[idx].in2_Pin , LOW);
        digitalWrite(DUAL_MOTOR_configs[idx].in3_Pin , LOW);
        digitalWrite(DUAL_MOTOR_configs[idx].in4_Pin , LOW);
        analogWrite(DUAL_MOTOR_configs[idx].pwmPin1  , 255);
        analogWrite(DUAL_MOTOR_configs[idx].pwmPin2  , 255);       
    }
}

void DUAL_MOTOR_rotate(DUAL_MOTOR_t dualMotorNum, DUAL_MOTOR_DIR_t direction, u8 speed)
{
    switch(direction)
    {
        case DUAL_MOTOR_FWD  :  DUAL_MOTOR_forward(dualMotorNum, speed);   break;        
        case DUAL_MOTOR_BACK :  DUAL_MOTOR_back(dualMotorNum  , speed);    break;
        case DUAL_MOTOR_RIGHT:  DUAL_MOTOR_right(dualMotorNum , speed);    break;
        case DUAL_MOTOR_LEFT :  DUAL_MOTOR_left(dualMotorNum  , speed);    break;
        case DUAL_MOTOR_STOP :  DUAL_MOTOR_stop(dualMotorNum);                  break;

        default:
        /* Invalid state    */  
        break;    
    }
}

void DUAL_MOTOR_rotate(DUAL_MOTOR_t dualMotorNum, DUAL_MOTOR_DIR_t direction)
{
    switch(direction)
    {
        case DUAL_MOTOR_FWD  :  DUAL_MOTOR_forward(dualMotorNum, DUAL_MOTOR_DEFAULT_SPEED);    break;        
        case DUAL_MOTOR_BACK :  DUAL_MOTOR_back(dualMotorNum   , DUAL_MOTOR_DEFAULT_SPEED);    break;
        case DUAL_MOTOR_RIGHT:  DUAL_MOTOR_right(dualMotorNum  , DUAL_MOTOR_DEFAULT_SPEED);    break;
        case DUAL_MOTOR_LEFT :  DUAL_MOTOR_left(dualMotorNum   , DUAL_MOTOR_DEFAULT_SPEED);    break;
        case DUAL_MOTOR_STOP :  DUAL_MOTOR_stop(dualMotorNum);                                 break;

        default:
        /* Invalid state    */  
        break;    
    }
}

static void DUAL_MOTOR_forward(DUAL_MOTOR_t dualMotorNum, u8 speed){
    u8 idx = 0;
    /* Convert from percentage value (0 ~ 100) to PWM analog vlaue (0 ~ 255)    */
    speed = (speed * 255) / 100;

    for (idx = 0; idx < countDualMotorConfigs; idx++){
        if(dualMotorNum == DUAL_MOTOR_configs[idx].dualMotorNum){
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin1, speed);
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin2, speed);

            digitalWrite(DUAL_MOTOR_configs[idx].in1_Pin    , HIGH );
            digitalWrite(DUAL_MOTOR_configs[idx].in2_Pin    , LOW  );
            digitalWrite(DUAL_MOTOR_configs[idx].in3_Pin    , HIGH );
            digitalWrite(DUAL_MOTOR_configs[idx].in4_Pin    , LOW  );
        }
    }
}

static void DUAL_MOTOR_back(DUAL_MOTOR_t dualMotorNum, u8 speed){
    u8 idx = 0;
    /* Convert from percentage value (0 ~ 100) to PWM analog vlaue (0 ~ 255)    */
    speed = (speed * 255) / 100;

    for (idx = 0; idx < countDualMotorConfigs; idx++){
        if(dualMotorNum == DUAL_MOTOR_configs[idx].dualMotorNum){
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin1, speed);
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin2, speed);

            digitalWrite(DUAL_MOTOR_configs[idx].in1_Pin    , LOW   );
            digitalWrite(DUAL_MOTOR_configs[idx].in2_Pin    , HIGH  );
            digitalWrite(DUAL_MOTOR_configs[idx].in3_Pin    , LOW   );
            digitalWrite(DUAL_MOTOR_configs[idx].in4_Pin    , HIGH  );
        }
    }
}

static void DUAL_MOTOR_right(DUAL_MOTOR_t dualMotorNum, u8 speed){
    u8 idx = 0;
    /* Convert from percentage value (0 ~ 100) to PWM analog vlaue (0 ~ 255)    */
    speed = (speed * 255) / 100;

    for (idx = 0; idx < countDualMotorConfigs; idx++){
        if(dualMotorNum == DUAL_MOTOR_configs[idx].dualMotorNum){
            /* Starting mode for        */
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin1, speed);
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin2, speed);

            digitalWrite(DUAL_MOTOR_configs[idx].in1_Pin    , HIGH );
            digitalWrite(DUAL_MOTOR_configs[idx].in2_Pin    , LOW  );
            digitalWrite(DUAL_MOTOR_configs[idx].in3_Pin    , LOW  );
            digitalWrite(DUAL_MOTOR_configs[idx].in4_Pin    , HIGH );
        }
    }
}

static void DUAL_MOTOR_left(DUAL_MOTOR_t dualMotorNum, u8 speed){
    u8 idx = 0;
    /* Convert from percentage value (0 ~ 100) to PWM analog vlaue (0 ~ 255)    */
    speed = (speed * 255) / 100;  

    for (idx = 0; idx < countDualMotorConfigs; idx++){
        if(dualMotorNum == DUAL_MOTOR_configs[idx].dualMotorNum){
            /* Starting mode for        */
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin1, speed);
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin2, speed);

            digitalWrite(DUAL_MOTOR_configs[idx].in1_Pin    , LOW   );
            digitalWrite(DUAL_MOTOR_configs[idx].in2_Pin    , HIGH  );
            digitalWrite(DUAL_MOTOR_configs[idx].in3_Pin    , HIGH  );
            digitalWrite(DUAL_MOTOR_configs[idx].in4_Pin    , LOW   );
        }
    }
}

static void DUAL_MOTOR_stop(DUAL_MOTOR_t motor){
    u8 idx = 0;

    for (idx = 0; idx < countDualMotorConfigs; idx++){
        if(motor == DUAL_MOTOR_configs[idx].dualMotorNum){
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin1   , 0);
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin1   , 0);

            digitalWrite(DUAL_MOTOR_configs[idx].in1_Pin    , HIGH   );
            digitalWrite(DUAL_MOTOR_configs[idx].in2_Pin    , HIGH   );
            digitalWrite(DUAL_MOTOR_configs[idx].in3_Pin    , HIGH   );
            digitalWrite(DUAL_MOTOR_configs[idx].in4_Pin    , HIGH   );
        }
    }
}
            