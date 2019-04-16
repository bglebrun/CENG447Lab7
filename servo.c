#include "servo.h"

void initServo() {
    //set pin and timers
    // set to 1 as output
    setBit(DDRD, 3);

    OCR2A = 0;
    OCR2B = 0;

    TCNT2 = 0x00;

    TCCR2A = 0xA3; // Fast PWM mode
    TCCR2B = 0x05; //1024 prescale
    // Counter match interrupt
    TIMSK2 = 0x02;
}

void moveServo(unsigned int deg) {
    unsigned int pwm = (deg > 180 ? 180 : deg);
    
    // TODO calculation here or something
    pwm = pwm;

    OCR2A = pwm;
}