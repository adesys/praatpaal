/**
 * @file    powersupply.h
 *
 * @author  
 *
 * @date    23/05/2006
 **/

#ifndef __POWERSUPPLY_H
#define __POWERSUPPLY_H

//--
extern void powersupplySetPiezo( bool b );

extern void powersupplyInit( void );
extern void powersupplyOff( void );

extern bool powersupplyPiezoIs( void );

#endif /* __POWERSUPPLY_H */
