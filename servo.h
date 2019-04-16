#ifndef _SERVO_H_
#define _SERVO_H_
#include <avr/io.h>

void initServo();
void moveServo(unsigned int deg);

#endif