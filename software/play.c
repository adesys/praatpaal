/**
 * @file    play.c
 *
 * @author  
 *
 * @date    18/05/2006
 *
 * @version
 **/
#include "includes.h"

#include "play.h"
#include "play_private.h"

#include "main.h"
#include "pwm1.h"
#include "dataflash.h"

//--

/* Global var is used because off speed, used in timer0 interrupt */

bool playSample;

volatile unsigned int pwmValue;

static Track trackCurrent;
static unsigned long trackEnd;
static unsigned long trackSampleIdx;
static bool playing;
static bool playContineous;

//--

/* First track is started at 0x00 of the WAV file */
static unsigned long trackIndex[MAXTRACKS][2];

//--

void playInit( void )
{
    playSample = false;
    playing = false;
    playContineous = false;
    playGetTrackIndex();
}

bool playIsBusy( void )
{
    return( playing );
}

Track playGetTrackPlaying( void )
{
    return( trackCurrent );
}

void playSetPlayContineous( bool b )
{
    playContineous = b;
}

void playStart( Track track )
{
    trackCurrent = track;   //save track
    trackSampleIdx = trackIndex[track][TRACKSTART];
    trackEnd = trackIndex[track][TRACKEND];

    dataflashStartContinuousArrayRead( trackSampleIdx );

    playing = true;
    playSample = true;
}

void playStop( void )
{
    playSample = false;

    dataflashStopContinuousArrayRead();

    if( playContineous == true )
    {
        playStart( trackCurrent );
    }
    else
    {
        playSample = false;
        playing = false;
    }
}

void playHandler( void )
{
    register unsigned char valueL;

	PWM1ASETVALUE( pwmValue );        //Send pwmvalue to the pwm register.

    if( playSample == true )
    {
        /* Get the 16 bits value, and convert it to an 10 bits value */
        valueL   = DATAFLASHREADBYTE();
        pwmValue = DATAFLASHREADBYTE();
        pwmValue = (pwmValue << 8) + valueL;
        pwmValue *= 5;                       // scaling 10 bits sample (max 1024) 
        pwmValue >>= 3;                      //   to max volume (=760)             => x 0.625 = *5 / 8

        trackSampleIdx += 2;                 //Next sample

        if( trackSampleIdx > trackEnd )
        {
            /* All samples are played, stop playing */
    	    playSample = false;
            playStop();
        }
	}
}

void playGetTrackIndex( void )
{
    unsigned char *p;
    unsigned char i;

    p = (unsigned char *)(trackIndex);
    dataflashStartContinuousArrayRead( TRACKINDEXSTART );

    for( i=1; i<(MAXTRACKS*8); i++ )
    {
        *p = DATAFLASHREADBYTE();
        p++;
    }

    dataflashStopContinuousArrayRead();
}

