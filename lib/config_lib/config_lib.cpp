#include "config_lib.h"



void test(uint8_t pin_test){
    static bool initialized = false;
    if(!initialized){
        pinMode(pin_test,OUTPUT);
        initialized = true;
        }
    
    digitalWrite(pin_test,HIGH);
    delay(500);
    digitalWrite(pin_test,LOW);
    delay(500);

    
} 