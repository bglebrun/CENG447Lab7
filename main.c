#define F_CPU 16000000
#include "bit_macros.h"
#include "pcint.h"
#include "robotIo.h"
#include "ultrasonic.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

/* stdout stream */
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void Init()
{
    // configure UART and I/O
    initUART();

    // configure ultrasonic range sensor
    initUltrasonic();

    // Enable global interrupts
    sei();
}

unsigned char motorSpeedMap(unsigned int USDistance) {
    unsigned int ans = ((USDistance - 3) * 255 / 27);
    return (ans > 255? 255 : ans);
}

int main()
{
    Init();
    while (1)
    {
        
    }
    return 1;
}
