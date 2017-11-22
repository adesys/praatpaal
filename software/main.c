/**
 * @file    main.c
 *
 * @author  
 *
 * @date    18/05/2006
 *
 * @version
 **/

#include "includes.h"

#include "main.h"
#include "main_private.h"

#include "os.h"

#include "powersupply.h"
#include "hardware.h"
#include "timer0.h"
#include "pwm1.h"
#include "play.h"
#include "dataflash.h"


//--

//#define DEBUG_STACK				// Debug purpose only!!!!!!

//--

/* Globals */

//--


AVRX_GCC_TASKDEF( mainTask, MAIN_TASK_STACK, MAIN_TASK_PRIO )
{
    while ( 1 )
    {
        playSetPlayContineous( false );
        playStart( TRACK1 );

        while( playIsBusy() == true );

        /* Stick here forever, we MUST powerdown */
		while( 1 )
		{
            powersupplyOff();
		}
	}
}

void mainTaskInitAndStart( void )
{
    /* Init hardware */
    initHardware();

    initDataFlash();

    pwm1AInitAndStart();
    playInit();

    AvrXRunTask( TCB(mainTask) );
}


//--


int main( void )
{
    volatile unsigned long i;

#ifdef DEBUG_STACK    
    uint8_t * p;
    unsigned char * lastAddress;

    for( p = (uint8_t *)&_end; p < (uint8_t *)0x4FF; ++p )
    {
        *p = 0xc0;
    }

    lastAddress = mainTaskStk + MAIN_TASK_STACK;
    for (p = mainTaskStk; p < lastAddress;++p)
    {
        *p = 0xc1;
    }

    lastAddress = voicecallTaskStk + VOICECALL_TASK_STACK;
    for (p = voicecallTaskStk; p < lastAddress;++p)
    {
        *p = 0xc2;
    }
    
#endif /* DEBUG_STACK */    
    
    for (i=0; i<0x100000L; i++ );

    /* Init I/O */
    initOs();

    /* Delay to allow the powersupply to become stable */
    mainTaskInitAndStart();

    /* Avrx: Do not modify! */
    Epilog();

    while (1);


}

