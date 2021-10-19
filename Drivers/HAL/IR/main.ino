/**
 **************************************************************************************
 * @file    main.ino
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Test IR sensors array used in Line follwer applications.
 * @version 0.1
 * @date    21 Aug 2021
 **************************************************************************************
 */

#include "include/STD_TYPES.h"
#include "include/IR.h"

#define NUM_OF_IR_SENSORS         4
#define EXTRA_LEFT_IR_SENSOR      0
#define LEFT_IR_SENSOR            1
#define RIGHT_IR_SENSOR           2
#define EXTRA_RIGHT_IR_SENSOR     3

int main(void) {
  /* Initializations    */
  init();
  Serial.begin(9600);
  IR_init();
  u8 IR_Values[NUM_OF_IR_SENSORS] = {0};

  while (1)
  {
    /* Scan IR sensors  */
    IR_Values[EXTRA_LEFT_IR_SENSOR]   = IR_getValue(IR0);
    IR_Values[LEFT_IR_SENSOR]         = IR_getValue(IR1);
    IR_Values[RIGHT_IR_SENSOR]        = IR_getValue(IR2);
    IR_Values[EXTRA_RIGHT_IR_SENSOR]  = IR_getValue(IR3);

    /* Print values of IR sensors */
    Serial.println("******************************");
    Serial.print("Extra Left  : ");
    Serial.println(IR_Values[EXTRA_LEFT_IR_SENSOR], DEC);

    Serial.print("Left        : ");
    Serial.println(IR_Values[LEFT_IR_SENSOR], DEC);

    Serial.print("Right       : ");
    Serial.println(IR_Values[RIGHT_IR_SENSOR], DEC);

    Serial.print("Extra Right : ");
    Serial.println(IR_Values[EXTRA_RIGHT_IR_SENSOR], DEC);

    _delay_ms(2000);
  }

  return 0;
}