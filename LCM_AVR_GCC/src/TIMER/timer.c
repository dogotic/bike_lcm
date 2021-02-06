#include  <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

// initialize timer, interrupt and variable
void TIMER_Init(uint16_t tcnt_val)
{
    // set up timer with prescaler = 8
    TCCR1B |= (1 << CS11);
    TCCR1B |= (1 << CS10);

    // initialize counter
    TCNT1 = tcnt_val;
 
    // enable overflow interrupt
    TIMSK1 |= (1 << TOIE1);
 
    // enable global interrupts
    sei();
}