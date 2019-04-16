#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_
#include "bit_macros.h"
#include "pin_map.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

bool getOverflowStatus();
void initUltrasonic();
void triggerUltrasonic();
void turnoffTimer1();
void turnonTimer1();
void TIM16_WriteTCNT1(unsigned int i);
unsigned int TIM16_ReadTCNT1();
unsigned int receiveUltrasonic();

#endif
