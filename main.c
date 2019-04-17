#define F_CPU 16000000
#include "bit_macros.h"
#include "pcint.h"
#include "robotIo.h"
#include "servo.h"
#include "ultrasonic.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void printAngleDistance(unsigned char angle, unsigned int distance);

/* stdout stream */
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void Init()
{
    // configure UART and I/O
    initUART();

    // configure ultrasonic range sensor
    initUltrasonic();

    // configure servo
    initServo();

    // Enable global interrupts
    sei();
}

int main()
{
    Init();
    while (1)
    {
        // start centered
        moveServo(90);
        printAngleDistance(90, readUltrasonic());
        // full CCW (left)
        moveServo(0);
        printAngleDistance(0, readUltrasonic());
        // full CW (right)
        moveServo(180);
        printAngleDistance(180, readUltrasonic());
        for (float i = 0; i < 180; i += 22.5)
        {
            moveServo(i);
            printAngleDistance(i, readUltrasonic());
        }
    }
    return 1;
}

void printAngleDistance(unsigned char angle, unsigned int distance)
{
    fprintf(&mystdout, "Position: %d degrees | Distance: %d cm", angle,
            distance);
}
