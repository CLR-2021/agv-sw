/**
 ****************************************************************************
 * @file    main.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Coordinnation system localization & navigation based on IR sensors.
 * @version 0.2.6
 * @date    2021-08-26
 * ***************************************************************************
 */
#include "include/STD_TYPES.h"
#include "include/DUAL_MOTOR.h"
#include "include/IR.h"
#include "include/IR_ARRAY.h"

#define DELAY_TIME              5    /* normal delay time  */
/* Navigation API  */
void navigate(void); 
void simpleTurnAlgorithm();
void sharpTurnAlgorithm();

/*************** Motors ***************/
/***** Configure this code *****/
#define MOTORS_NORMAL_SPEED       40

void setup()
{
    /* Initializations      */
    IR_init();
    DUAL_MOTOR_init();
}

u8 junctionCount = 0;

void loop(){
    /* Check batteries state    */
        /* If empty     */
            /* rise the robot not available flag */
            /* navigate to an available charging port  */
            /* rise the charging port not available flag */
            /* wait until battery is full     */
                /* if full      */
                    /* down the robot not available flag    */
                    /* down the charging port not available flag  */
                    /* return to waiting poision                */
        /* If good */
            /* Be ready to get orders   */
    
    /* Scan order available     */
        /* If available     */
            /* Get positions                    */
            /* navigate to rack's position      */
            /* lift the rack                    */
            /* navigate to client's position    */
            /* when reach the client, send a flag to the client's gui   */
            /* wait until the rack is lifted    */
            /* navigate back to waiting position      */
        /* If not available */
            /* nothing      */

    scanIR_Sensors();
    navigate();
}

void navigate(void){

    /* Check if any of Extra left or  Extra right sensors on track  */
    if( IR_Values[EXTRA_LEFT_IR_SENSOR] || IR_Values[EXTRA_RIGHT_IR_SENSOR] ){
        /* Apply 90 degrree (sharp turn) algorithm  */
        sharpTurnAlgorithm();
    }
    else{
        /* Apply simple turn algorithm  */
        simpleTurnAlgorithm();
    }
}

void simpleTurnAlgorithm(){
    /* Check to go forward */
    if ((IR_Values[LEFT_IR_SENSOR] && IR_Values[RIGHT_IR_SENSOR]))
    {
        goForward(MOTORS_NORMAL_SPEED, MOTORS_NORMAL_SPEED);
    }

    /* Check to go right    */
    else if ( ! IR_Values[RIGHT_IR_SENSOR])
    {
        /* Turn right until it back to line */
        do{
            /* Simple turn right by reducing right motor speed to the half of left motor speed  */
            goForward(MOTORS_NORMAL_SPEED, MOTORS_NORMAL_SPEED >> 2);
            
            scanIR_Sensors();
        }while ( ! IR_Values[RIGHT_IR_SENSOR]);
    }

    /* Otherwise, go left     */
    else{
        /* Turn right by reducing left motor speed to the half of right motor speed */
        do{   
            /* Simple turn left by reducing left motor speed to the half of right motor speed  */
            goForward(MOTORS_NORMAL_SPEED >> 2, MOTORS_NORMAL_SPEED);
            
            scanIR_Sensors();
        }while ( ! IR_Values[LEFT_IR_SENSOR] );
    }
}

void sharpTurnAlgorithm(){ 
    /* Check if junction detected   */
    if ( junctionDetected() ){
        /* Count Junction Algorithm  */
        stopMotors();
    }

    /* Check to turn right   */
    else if ( IR_Values[EXTRA_RIGHT_IR_SENSOR] ){
        
        /* Rotate until the sensor out of track */
        do {
            /* Sharp turn right by rotating right motor backward and left motor forward */
            turnRight(MOTORS_NORMAL_SPEED, MOTORS_NORMAL_SPEED);
            
            scanIR_Sensors();

            /* Check if junction detected   */
            if( junctionDetected() ){
                break;
            }

        }while ( IR_Values[EXTRA_RIGHT_IR_SENSOR] );
    }

    /* Check to turn left   */
    else if ( IR_Values[EXTRA_LEFT_IR_SENSOR] )
    {   
        /* Rotate until the sensor out of track */
        do {
            /* Sharp turn right by rotating right motor backward and left motor forward */
            turnLeft(MOTORS_NORMAL_SPEED, MOTORS_NORMAL_SPEED);
            
            scanIR_Sensors();

            /* Check if junction detected   */
            if( junctionDetected() ){
                break;
            }

        }while ( IR_Values[EXTRA_LEFT_IR_SENSOR] );
    }
}

int junctionDetected(){
    int state = 0;

    if (IR_Values[EXTRA_RIGHT_IR_SENSOR] && IR_Values[EXTRA_LEFT_IR_SENSOR]){
        state = 1;
    }

    return state;
}