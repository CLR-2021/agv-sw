#include "include/STD_TYPES.h"
#include "include/IR.h"
#include "include/IR_ARRAY.h"

int main(void){
    u8 idx = 0;

    init();
    Serial.begin(9600);
    IR_init();

    while (1)
    {   
        scanIR_Sensors();

        for(idx = 0; idx < countIRSensors; idx++){
            Serial.print("Sensor ");
            Serial.print(idx);
            Serial.print("= ");
            Serial.print(IR_Values[idx]);
            Serial.print("    ");
        }

        Serial.println();
        _delay_ms(1000);                
    }

    return 0;
}