/**
 * @file    generic.h
 *
 *
 * @author  
 *
 * @date    18/05/2006
 **/

#ifndef __GENERIC_H
#define __GENERIC_H

//--
\
extern TimerControlBlock delayTimer;
extern unsigned char sreg;

#define GEN_STRING_SIZE     50
extern char genericString[];

#define TELNO_STRING_SIZE   15

//--

/* General purpose test pin */

#ifndef TESTPORT
#define TESTPORT        PORTC
#define TESTPIN         PINC
#define TESTDDR         DDRC
#define TESTBIT         PC0
#endif

#define TEST_INIT()     TESTDDR  |= (1<<TESTBIT)

// TEST_CS is low active
#define TEST_OFF()      TESTPORT &= ~(1<<TESTBIT)
#define TEST_ON()       TESTPORT |= (1<<TESTBIT)
#define TEST_TOGGLE()   TESTPIN |= (1<<TESTBIT)

//--

/**
 * BEGINCRITICAL: Begin critical condition
 *   Save SREG in sreg var and disable global interrupt flag
 *
 * @par        None
 *
 * @return     None
 **/
#define BEGINCRITICAL() \
    sreg = SREG; \
    cli();

/**
 * ENDCRITICAL: End critical condition
 *   Restore SREG.
 *
 * @par        None
 *
 * @return     None
 **/
#define ENDCRITICAL() \
    SREG = sreg;

/**
 * WRITE16BITREG: Write value to 16-bits register
 *
 * @par        unsigned int: value
 *
 * @return     None
 **/
#define WRITE16BITREG( reg, value ) \
    BEGINCRITICAL(); \
    reg = value; \
    ENDCRITICAL();

/**
 * READ16BITREG: Write value to 16-bits register
 *
 * @par        unsigned int: value
 *
 * @return     None
 *
 * @warning    NOT TESTED (2006-03-08) !
 **/
#define READ16BITREG( reg, value ) \
    BEGINCRITICAL(); \
    value = reg; \
    ENDCRITICAL();

//--

extern void putStringData( unsigned char d, char *p );
extern void putStringCode( unsigned char d, const char *p );

#endif /* __GENERIC_H */
