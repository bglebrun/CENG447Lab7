#include "pcint.h"

/*
 * stdout stream
 *
 * available for debugging but slows ISRs a lot.
 */
// static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,
// _FDEV_SETUP_WRITE);

void initPCINT()
{
    PCMSK1 |= PCMSK1_CONFIG;
    PCICR |= PCICR_CONFIG;
}

// specific pin change interrupt handler that is less general, but
// should be faster so less time is spent in the interrupt and
// measurements are more accurate.
//
// Expects only PCINT12 active (the ultrasonic sensor input)
ISR(PCINT1_vect)
{
    // used to detect whether pcint is going high->low or low->high
    // a value of false indicates we are low->high, a value of true indicates
    // high->low.
    static bool highEdge = false;

    if (highEdge)
    {
        turnoffTimer1();
        timeResponse = receiveUltrasonic();
        responseAvailable = true;
    }
    else
    {
        TIM16_WriteTCNT1(0);
        turnonTimer1();
        responseAvailable = false;
    }

    highEdge = !highEdge;
}

/*
// Pin change interrupt handler for pins 14-8
// written with a general switch design to
// handle cases where we are listening to more
// than one pin
ISR(PCINT1_vect)
{
    // pull current state of PORTC first thing
    unsigned char currState = PINC;

    // last state the pins were in
    static unsigned char lastState = 0x00;
    // used to detect whether pcint is going high->low or low->high
    // a value of 0 indicates we are low->high, a value of 1 indicates high->low
    static bool highEdge = false;
    // changed pins
    unsigned char pcflags = currState ^ lastState;
    lastState = currState;

    // to add handling for a specific set of pin changes, add a case
    // to the switch statement with the bits corresponding to a pin combination
    // set. Note that the specific combination must be available as a case.
    switch (pcflags)
    {
    case 0x00:
        // nothing happened, do nothing
        break;

    case 0x10: // PORTC4 (PCINT12) changed
        if (highEdge)
        {
            turnoffTimer1();
            timeResponse = receiveUltrasonic();
            responseAvailable = true;
        }
        else
        {
            TIM16_WriteTCNT1(0);
            turnonTimer1();
            responseAvailable = false;
        }
        highEdge = !highEdge;

        break;
    case 0x20: // PORTC4 (PCINT13) changed
        break;
    default:
        // a case we weren't expecting occurred, do nothing
        break;
    }
}
*/
