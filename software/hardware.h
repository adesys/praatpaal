/**
 * @file    hardware.h
 *          Hardware macro's and definitions
 * 
 * @author  
 *
 * @date    18/05/2006
 **/

#ifndef __HARDWARE_H
#define __HARDWARE_H

// CPU
#define CPUCLK                  12288000L     	// CPU xtal !!!!!!!!!!!!!!!!!!!!!!!!!!


//--
#define UARTSEL_MDM 0
#define UARTSEL_COM 1

//--

extern void initIO( void );
extern void initHardware( void );
extern void setUartSel( unsigned char sel );

#endif /* __HARDWARE_H */
