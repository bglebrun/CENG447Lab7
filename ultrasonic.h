#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_
#include "bit_macros.h"
#include "pin_map.h"
#include "pcint.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>


/*
 *
 * Ultrasonic sensor: A4 A5 (portc 4 5)
 * Servo Motor: 3 (portd 3)
 */

bool getOverflowStatus();
void initUltrasonic();
void triggerUltrasonic();
void turnoffTimer1();
void turnonTimer1();
void TIM16_WriteTCNT1(unsigned int i);
unsigned int readUltrasonic();
unsigned int TIM16_ReadTCNT1();
unsigned int receiveUltrasonic();

#endif
