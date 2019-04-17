#include "ultrasonic.h"

/******************************************************************************
 *
 * Overflow detection helpers
 *
 * Flag for overflow:
 * false = no overflow.
 * true = overflow happened in test
 */
volatile bool TimerOverflow = false;

// Getter for overflow status
bool getOverflowStatus() { return TimerOverflow; }

// Overflow vector
ISR(TIMER1_OVF_vect)
{
    // Timer 1 overflow
    TimerOverflow = true;
}

/******************************************************************************
 *
 * Ultrasonic sensor functions
 *
 *
 * Sets the pins for ultrasonic sensor,
 * then will setup the necessary timer 1
 * to properly time the sensor
 */
void initUltrasonic()
{
    // Trig on A5
    setBit(DDRC, US_TRIG);
    // Echo on A4
    clearBit(DDRC, US_ECHO);

    clearBit(PORTC, US_TRIG);
    clearBit(PORTC, US_ECHO);

    // setBit(PORTC, US_ECHO); // pull-up for echo

    initTimer1();
}

unsigned int readUltrasonic()
{
    // Trigger the sensor
    triggerUltrasonic();
    // Spin while we either timeout or wait
    while (!TimerOverflow && !responseAvailable)
    {
    };

    unsigned int i = TIM16_ReadTCNT1();
    // 64 us per count in i
    return (i * 64) / 58;
}

// Triggers ultrasonic sensor, then waits 60 ms
void triggerUltrasonic()
{
    TimerOverflow = false;
    setBit(PORTC, US_TRIG);
    _delay_us(9);
    clearBit(PORTC, US_TRIG);
    // reset counter 1
    // TIM16_WriteTCNT1(0);
    // Delay while pulse is sent
    _delay_us(60);
}
