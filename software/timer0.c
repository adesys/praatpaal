/**
 * @file    timer0.c
 *          Timer0 functions
 *          - generates the timertick for the OS
 * 
 * @date    25/02/2006
 **/

#include "includes.h"

#include "timer0.h"
#include "timer0_private.h"

#include "main.h"

//--

void timer0InitAndStart( void )
{
    TCNT0  = T0_TCNT;
    TCCR0B = T0_PRECALER;
    TIMSK0 = (1<<TOIE0);
}

AVRX_SIGINT( SIG_OVERFLOW0 )
{
    IntProlog();                //Switch to kernel stack/context

    TCNT0 += T0_TCNT;           //Add to pre-load to account for any missed clocks

    TIMSK0 &= (~1<<TOIE0);      // Disable T0 interrupt
    sei();					    // Allow other interrupt activity to occur

    AvrXTimerHandler();

    TIMSK0 = (1<<TOIE0);
    
    Epilog();                   //Return to tasks
}
