#include "servo.h"

void initServo()
{
    // set pin and timers
    // set to 1 as output
    setBit(DDRD, 3);

    // init TC2

    initTimer2();
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
