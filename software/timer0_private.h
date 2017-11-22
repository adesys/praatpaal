/**
 * @file    timer0_private.h
 * 
 * @date    18/04/2006
 **/
#ifndef __TIMER0_PRIVATE_H
#define __TIMER0_PRIVATE_H

//--

#define T0_TICKRATE TIMERTICK		        //tickrate = 100Hz, ones every 10ms the OS is called

#define T0_TCNT     (0x100-CPUCLK/1024/T0_TICKRATE)
#define T0_PRECALER (1<<CS02) | (1<<CS00) 


/**
 * Timer 0: Init and start
 * An interrupt is generated -> 8kHz, used by AVRX and playing (PWM) samples
 *
 * @par        None
 *
 * @return     None
 *
 * @see        
 **/
void timer0InitAndStart( void );

/**
 * Timer 0 Overflow Interrupt Handler
 * - Switch to kernel context
 * - handle interrupt
 * - switch back to interrupted context.
 *
 * @par        None
 *
 * @return     None
 *
 * @see        timer0InitAndStart 
 **/
//AVRX_SIGINT( SIG_OVERFLOW0 );

#endif /* __TIMER0_PRIVATE_H */

