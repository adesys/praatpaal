/**
 * @file    os.c
 *          Generic OS functions
 *
 * @author  
 *
 * @date    18/05/2006
 *
 * @version 
 **/

#include "includes.h"

#include "timer0.h"

//--

void initOs( void )
{
    AvrXSetKernelStack( 0 );        //Init stack pointer

    wdt_disable();                  //Disable watchdog

    timer0InitAndStart();           //Start timertick
}

