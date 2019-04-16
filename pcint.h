#ifndef _PCINT_H_
#define _PCINT_H_
#include "avr/io.h"
#include "robotIo.h"
#include "ultrasonic.h"
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>

#define PCMSK1_CONFIG                                                          \
    (0 << PCINT14) | (0 << PCINT13) | (1 << PCINT12) | (0 << PCINT11) |        \
        (0 << PCINT10) | (0 << PCINT9) | (0 << PCINT8)

#define PCICR_CONFIG (0 << PCIE2) | (1 << PCIE1) | (0 << PCIE0)

volatile unsigned int timeResponse;
volatile bool responseAvailable;

void initPCINT();

#endif
