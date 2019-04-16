#ifndef _SERVO_H_
#define _SERVO_H_
#include <avr/io.h>
#include "pin_map.h"

void initServo();
void moveServo(unsigned int deg);

#endif