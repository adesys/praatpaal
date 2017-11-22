/**
 * @file    main_private.h
 *          
 * 
 * @author  
 *
 * @date    18/05/2006
 *
 * @version 
 **/
#ifndef __MAIN_PRIVATE_H
#define __MAIN_PRIVATE_H

//--

#ifdef DEBUG_MAIN
#define MAIN_DBGPRINT(x) dbgPrint( x );
#else
#define MAIN_DBGPRINT(x)
#endif

//--

//--

PROGMEM const char VERSION_SW[] = "V1.00";

//--


void mainTaskInitAndStart( void );

#endif /* __MAIN_PRIVATE_H */

