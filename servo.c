#include "servo.h"

void initServo()
{
    // set pin and timers
    // set to 1 as output
    setBit(DDRD, 3);

    // init TC2

    // phase correct with 1024 prescaler gets us a high enough max time
    // use OCR2A to set TOP (WGM 5) such that we interrupt as close to 2ms
    // as possible

    // OCR2A = 16MHz/(2*1024*50Hz)
    // we choose 50Hz because 50Hz==20ms
    // OCR2A = 156.25, we can't have fractions so we use 156
    OCR2A = 156;
    // OCR2B determines the width of the pulse
    // OCR2B = 16MHz*(pulse width in ms)/(2*1024)
    // 1ms = 8, 1.5ms = 12, 2ms = 16
    // start facing forward
    OCR2B = 12;

    // start TC2 at 0
    TCNT2 = 0x00;

    // phase corrected PWM mode with 1024 clock prescale
    TCCR2A |= (0 << COM2A1) | (0 << COM2A0) | (1 << COM2B1) | (0 << COM2B0) |
              (1 << WGM21) | (0 << WGM20);
    TCCR2B |= (1 << WGM22) | (1 << CS22) | (1 << CS21) | (1 << CS20);
}

void moveServo(unsigned int deg) { OCR2A = mapAngle(deg); }

// mapping assumes 0 degrees is full CCW (left) and 180 degrees is full CW
// (Right)
unsigned char mapAngle(unsigned int angleDeg)
{
    unsigned char result;
    if (angleDeg <= 0)
    {
        result = 8;
    }
    else if (angleDeg >= 180)
    {
        result = 16;
    }
    else
    {
        result = 8 + (unsigned char)((float)angleDeg / 22.5);
    }

    return result;
}
