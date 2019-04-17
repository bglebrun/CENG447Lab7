#ifndef _SERVO_H_
#define _SERVO_H_
#include "bit_macros.h"
#include "pin_map.h"
#include "timers.h"
#include <avr/io.h>

void initServo();
void moveServo(unsigned int deg);
unsigned char mapAngle(unsigned int angleDeg);

#endif
