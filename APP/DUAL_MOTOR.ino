/**
 *****************************************************************************
 * @file    MOTOR.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Static code of Dual DC Motor Driver with Direction and speedPercentage Control.
 * @version 0.1
 * @date    2021-08-26
 *****************************************************************************
 */
#include "include/STD_TYPES.h"
#include "include/DUAL_MOTOR.h"
#include "include/DUAL_MOTOR_cfg.h"

/**
 **************************************************************************************
 *                                Interfaced Functions
 **************************************************************************************
 */
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

void goForward(u8 leftSpeedPercentage, u8 rightSpeedPercentage){
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_FWD, leftSpeedPercentage, rightSpeedPercentage);
}

void turnLeft(u8 leftSpeedPercentage, u8 rightSpeedPercentage){
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_LEFT, leftSpeedPercentage, rightSpeedPercentage);
}

void turnRight(u8 leftSpeedPercentage, u8 rightSpeedPercentage){
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_RIGHT, leftSpeedPercentage, rightSpeedPercentage);
}

void stopMotors(void){
    DUAL_MOTOR_rotate(DUAL_MOTOR0, DUAL_MOTOR_STOP);
}

/**
 **************************************************************************************
 *                                Private Functions
 **************************************************************************************
 */
/**
 * @brief Rotate a specific motor forward, backward, or stop it.
 * @param motor The motor to rotate; options specified in MOTOR_t enum.
 * @param direction Direction to rotate motor with; options specified in MOTOR_DIR_t enum.
 * @param leftSpeedPercentage Speed of left motor as a percentage.
 * @param rightSpeedPercentage Speed of right motor as a percentage.
 * @details Rotating motor forward or backward, motors rotates at a speed of motorSpeed
 *          parameter.
 *          With stop motor, speed does not matter, motor stops whatever speed is passed.
 */
void DUAL_MOTOR_rotate(DUAL_MOTOR_t dualMotorNum, DUAL_MOTOR_DIR_t direction, u8 leftSpeedPercentage, u8 rightSpeedPercentage)
{
    u8 leftSpeed = 0, rightSpeed = 0;
    /* Convert from percentage value (0 ~ 100) to PWM analog vlaue (0 ~ 255)    */
    leftSpeed     = (leftSpeedPercentage      * 255) / 100;
    rightSpeed   = (rightSpeedPercentage    * 255) / 100;

    switch(direction)
    {
        case DUAL_MOTOR_FWD  :  
            DUAL_MOTOR_forward(dualMotorNum , leftSpeed, rightSpeed);   
            break;        
        case DUAL_MOTOR_BACK :  
            DUAL_MOTOR_back(dualMotorNum    , leftSpeed, rightSpeed);    
            break;
        case DUAL_MOTOR_RIGHT:  
            DUAL_MOTOR_right(dualMotorNum   , leftSpeed, rightSpeed);    
            break;
        case DUAL_MOTOR_LEFT :  
            DUAL_MOTOR_left(dualMotorNum    , leftSpeed, rightSpeed);    
            break;
        case DUAL_MOTOR_STOP :  
            DUAL_MOTOR_stop(dualMotorNum);                  
            break;

        default:
        /* Invalid state    */  
        break;    
    }
}

/**
 * @brief Rotate a specific motor forward, backward, or stop it.
 * @param motor The motor to rotate; options specified in MOTOR_t enum.
 * @param direction Direction to rotate motor with; options specified in MOTOR_DIR_t enum.
 * @details When rotating motor forward or backward, motors rotates at a speed defined 
 *          with MOTOR_DEFAULT_SPEED macro in configurations header file.
 */
void DUAL_MOTOR_rotate(DUAL_MOTOR_t dualMotorNum, DUAL_MOTOR_DIR_t direction)
{
    switch(direction)
    {
        case DUAL_MOTOR_FWD  :  
            DUAL_MOTOR_forward(dualMotorNum, LEFT_DEFAULT_SPEED, RIGHT_DEFAULT_SPEED);    
            break;        
        case DUAL_MOTOR_BACK : 
             DUAL_MOTOR_back(dualMotorNum  , LEFT_DEFAULT_SPEED, RIGHT_DEFAULT_SPEED);    
             break;
        case DUAL_MOTOR_RIGHT:  
            DUAL_MOTOR_right(dualMotorNum  , LEFT_DEFAULT_SPEED, RIGHT_DEFAULT_SPEED);    
            break;
        case DUAL_MOTOR_LEFT :  
            DUAL_MOTOR_left(dualMotorNum   , LEFT_DEFAULT_SPEED, RIGHT_DEFAULT_SPEED);    
            break;
        case DUAL_MOTOR_STOP :  
            DUAL_MOTOR_stop(dualMotorNum);                                 
            break;

        default:
        /* Invalid state    */  
        break;    
    }
}

static void DUAL_MOTOR_forward(DUAL_MOTOR_t dualMotorNum, u8 leftSpeed, u8 rightSpeed){
    u8 idx = 0;

    for (idx = 0; idx < countDualMotorConfigs; idx++){
        if(dualMotorNum == DUAL_MOTOR_configs[idx].dualMotorNum){
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin1, leftSpeed);
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin2, rightSpeed);

            digitalWrite(DUAL_MOTOR_configs[idx].in1_Pin    , HIGH );
            digitalWrite(DUAL_MOTOR_configs[idx].in2_Pin    , LOW  );
            digitalWrite(DUAL_MOTOR_configs[idx].in3_Pin    , HIGH );
            digitalWrite(DUAL_MOTOR_configs[idx].in4_Pin    , LOW  );
        }
    }
}

static void DUAL_MOTOR_back(DUAL_MOTOR_t dualMotorNum, u8 leftSpeed, u8 rightSpeed){
    u8 idx = 0;

    for (idx = 0; idx < countDualMotorConfigs; idx++){
        if(dualMotorNum == DUAL_MOTOR_configs[idx].dualMotorNum){
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin1, leftSpeed);
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin2, rightSpeed);

            digitalWrite(DUAL_MOTOR_configs[idx].in1_Pin    , LOW   );
            digitalWrite(DUAL_MOTOR_configs[idx].in2_Pin    , HIGH  );
            digitalWrite(DUAL_MOTOR_configs[idx].in3_Pin    , LOW   );
            digitalWrite(DUAL_MOTOR_configs[idx].in4_Pin    , HIGH  );
        }
    }
}

static void DUAL_MOTOR_right(DUAL_MOTOR_t dualMotorNum, u8 leftSpeed, u8 rightSpeed){
    u8 idx = 0;

    for (idx = 0; idx < countDualMotorConfigs; idx++){
        if(dualMotorNum == DUAL_MOTOR_configs[idx].dualMotorNum){
            /* Starting mode for        */
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin1, leftSpeed);
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin2, rightSpeed);

            digitalWrite(DUAL_MOTOR_configs[idx].in1_Pin    , HIGH );
            digitalWrite(DUAL_MOTOR_configs[idx].in2_Pin    , LOW  );
            digitalWrite(DUAL_MOTOR_configs[idx].in3_Pin    , LOW  );
            digitalWrite(DUAL_MOTOR_configs[idx].in4_Pin    , HIGH );
        }
    }
}

static void DUAL_MOTOR_left(DUAL_MOTOR_t dualMotorNum, u8 leftSpeed, u8 rightSpeed){
    u8 idx = 0;

    for (idx = 0; idx < countDualMotorConfigs; idx++){
        if(dualMotorNum == DUAL_MOTOR_configs[idx].dualMotorNum){
            /* Starting mode for        */
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin1, leftSpeed);
            analogWrite(DUAL_MOTOR_configs[idx].pwmPin2, rightSpeed);

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

            digitalWrite(DUAL_MOTOR_configs[idx].in1_Pin    , LOW   );
            digitalWrite(DUAL_MOTOR_configs[idx].in2_Pin    , LOW   );
            digitalWrite(DUAL_MOTOR_configs[idx].in3_Pin    , LOW   );
            digitalWrite(DUAL_MOTOR_configs[idx].in4_Pin    , LOW   );
        }
    }
}
            