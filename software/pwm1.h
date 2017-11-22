/**
 * @file    pwm.h
 * 
 * @author  
 *
 * @date    18/05/2006
 *
 * @version 
 **/
#ifndef __PWM1_H
#define __PWM1_H

//--

#define PWM_50PERSENT   0x0100              //50% for 9-bits resolution


//--

/**
 * PWM1ASETVALUE: Write value to OCR1A register
 *
 * @par        unsigned int: pwm value
 *
 * @return     None
 **/
#define PWM1ASETVALUE( value ) WRITE16BITREG( OCR1A, value )

//--

extern void pwm1AInitAndStart( void );

#endif /* __PWM1_H */

