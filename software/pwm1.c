/**
 * @file    pwm1.c
 * 
 *          Sets the PWM in mode 14 (ICR1 is used for the TOP value)
 *          - ICR1 = 768 (@12.288MHz)
 *            - f(pwm) = 16kHz
 *            - 9 bits resolution
 *
 * @author  
 *
 * @date    28/06/2006
 *
 * @version 
 **/
#include "includes.h"

#include "pwm1.h"
#include "pwm1_private.h"

#include "play.h"

//--

void pwm1AInitAndStart( void )
{
    BeginCritical();

    DDRB |= (1<<PB1);                                //Set as output

    ICR1 = CPUCLK/16000;                             //f(pwm) = 16kHz, resolution depending on CPUCLK
                                                     // 18.432MHz -> 1152 > 1024 -> 10-bits
                                                     // 12.228MHz -> 768  > 512  -> 9-bits    

    PWM1ASETVALUE( PWM_50PERSENT );                  //PWM value = 50%

    TCCR1A = (1<<COM1A1) | (1<<WGM11);               //Compare match fast clear at TOP (=ICR1)
    TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS10);    //  fast PWM mode 14 (10-bits), timer started

    TIMSK1 = (1<<TOIE1);                             //Enable timer 1 overflow interrupts

    EndCritical();
}

AVRX_SIGINT( SIG_OVERFLOW1 )
{
    IntProlog();                                     //Switch to kernel stack/context

    TIMSK1 &= (~1<<TOIE1);                           // Disable T1 interrupt
    sei();					                         // Allow other interrupt activity to occur

    playHandler();                                   //Call the playhandler every pwm period -> 16kHz

    TIMSK1 = (1<<TOIE1);
    
    Epilog();                                        //Return to tasks
}

