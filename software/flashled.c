/**
 * @file    flashled.c
 *          Led
 * 
 * @date    18/05/2006
 **/

#include "includes.h"

#include "flashled_private.h"
#include "flashled.h"

#include "main.h"

static unsigned int flashLedTimeOn;
static unsigned int flashLedTimeOff;

AVRX_GCC_TASKDEF(flashledTask, 10, 5) //!!!!!!!!!!!!!!!!!!
{
    TimerControlBlock flashledTimer;

    while(1)
    {
        AvrXDelay( &flashledTimer, flashLedTimeOn );
        FLASHLEDON();
        AvrXDelay( &flashledTimer, flashLedTimeOff );        
        FLASHLEDOFF();
    }
}

void flashledSet( unsigned int timeOn, unsigned int timeOff )
{
    flashLedTimeOn = timeOn;
    flashLedTimeOff = timeOff;
}

void flashledTaskInitAndStart( unsigned int timeOn, unsigned int timeOff )
{
    FLASHLEDINIT();
	
	flashledSet( timeOn, timeOff );
    AvrXRunTask( TCB(flashledTask) );    
}
