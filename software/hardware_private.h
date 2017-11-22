/**
 * @file    hardware_private.h
 *          Hardware macro's and definitions
 *
 * @author  
 *
 * @date    2006-03-06
 **/

#ifndef __HARDWARE_PRIVATE_H
#define __HARDWARE_PRIVATE_H

/* UART-SEL */

#ifndef UARTSELPORT
#define UARTSELPORT       PORTD
#define UARTSELPIN        PIND
#define UARTSELDDR        DDRD
#define UARTSELBIT        PD2
#endif

#define UARTSEL_INIT()    UARTSELDDR  |= (1<<UARTSELBIT)
#define UARTSEL_ON()      UARTSELPORT |= (1<<UARTSELBIT)
#define UARTSEL_OFF()     UARTSELPORT &= ~(1<<UARTSELBIT)

//--

void initIO( void );
void initHardware( void );
void setUartSel( unsigned char sel );

//--

#endif /* __HARDWARE_PRIVATE_H */
