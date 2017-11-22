/**
 * @file    powersupply_private.h
 *
 * @author  
 *
 * @date    23/05/2006
 **/

#ifndef __POWERSUPPLY_PRIVATE_H
#define __POWERSUPPLY_PRIVATE_H

//--

/* PWR-ON-PIEZO */

#ifndef PWRONPIEZOPORT
#define PWRONPIEZOPORT  PORTC
#define PWRONPIEZOPIN   PINC
#define PWRONPIEZODDR   DDRC
#define PWRONPIEZOBIT   PC3
#endif

//Pull-up is required
#define PWRONPIEZO_INIT() \
    PWRONPIEZOPORT |= (1<<PWRONPIEZOBIT); \
    PWRONPIEZODDR  &= ~(1<<PWRONPIEZOBIT)

#define PWRONPIEZO_IS() (!(PWRONPIEZOPIN & (1<<PWRONPIEZOBIT)))        //Low active

/* PWR-OFF */

#ifndef PWROFFPORT
#define PWROFFPORT      PORTC
#define PWROFFPIN       PINC
#define PWROFFDDR       DDRC
#define PWROFFBIT       PC2
#endif

#define PWROFF_INIT()    PWROFFDDR  |= (1<<PWROFFBIT)
#define PWROFF_ENABLE()  PWROFFPORT |= (1<<PWROFFBIT)
#define PWROFF_DISABLE() PWROFFPORT &= ~(1<<PWROFFBIT)

//--

#define POWEROFF_TIMEOUT 10000

//--
void powersupplySetPiezo( bool b );

void powersupplyInit( void );
void powersupplyOff( void );

bool powersupplyPiezoIs( void );
unsigned char powersupplyWakeupReason( void );


#endif /* __POWERSUPPLY_PRIVATE_H */
