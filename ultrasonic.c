#include "ultrasonic.h"

/*
 * Flag for overflow:
 * false = no overflow.
 * true = overflow happened in test
 */
volatile bool TimerOverflow = false;

/*
 *
 * Ultrasonic sensor: A4 A5 (portc 4 5)
 * Servo Motor: 3 (portd 3)
 */

/*
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

    PORTC = 0x00;

    // setBit(PORTC, US_ECHO); // pull-up for echo

    /*
     * Timer 1
     * Pins 7:4 zeroes
     * tccr1a high byte zeroes
     * 16 us
     */
    OCR1A = 0;
    OCR1B = 0;
    // Start tcount at 1
    TCNT1 = 0x00;
    // Normal mode
    TCCR1A = 0x00;

    // ensure we start with the timer off
    turnoffTimer1();
}

// convenience function to turn the timer off
void turnoffTimer1() { TCCR1B &= 0x00; }

// convenience function to turn the timer back on with a default prescaler
void turnonTimer1()
{
    /*
     * Prescaler value goes here
     * 1 - no prescaling
     * 2 - clock /8
     * 3 - clock /64
     * 4 - clock /256 - 16us
     * 5 - clock /1024 - 64us
     * source -
     * https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328
     */
    TCCR1B |= 0x05;
}

// Triggers ultrasonic sensor, then waits 60 ms
void triggerUltrasonic()
{
    TimerOverflow = false;
    setBit(PORTC, US_TRIG);
    _delay_us(10);
    clearBit(PORTC, US_TRIG);
    // reset counter 1
    // TIM16_WriteTCNT1(0);
    // Delay while pulse is sent
    _delay_ms(60);
}

// Getter for overflow status
bool getOverflowStatus() { return TimerOverflow; }

// Overflow vector
ISR(TIMER1_OVF_vect)
{
    // Timer 1 overflow
    TimerOverflow = true;
}

/*
 * Gets the current status of timer 1, then
 * converts it into clock/cm
 */
unsigned int receiveUltrasonic()
{
    unsigned int i = TIM16_ReadTCNT1();
    // 64 us per count in i
    // return ((58 * 64) / i);
    return (i * 64) / 58;
}

// Reads from timer 1 counter
unsigned int TIM16_ReadTCNT1()
{
    unsigned char sreg;
    unsigned int i;
    // Save global interrupt flag
    sreg = SREG;
    // Disable interrupts
    cli();
    // Read TCNT1 into i
    i = TCNT1;
    // Restore global interrupt flag
    SREG = sreg;
    return i;
}

// Sets timer 1 counter
void TIM16_WriteTCNT1(unsigned int i)
{
    unsigned char sreg;
    // Save global interrupt flag
    sreg = SREG;
    // Disable interrupts
    cli();
    // Set TCNT1  to i
    TCNT1 = i;
    // Restore global interrupt flag
    SREG = sreg;
}
