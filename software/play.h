/**
 * @file    play.h
 *
 * @author  
 *
 * @date    18/05/2006
 *
 * @version
 **/
#ifndef __PLAY_H
#define __PLAY_H

#include "includes.h"

//--

/* Track defines */
typedef unsigned char Track;
#define TRACK1              0

//--

extern bool playIsBusy( void );
extern void playSetPlayContineous( bool b );
extern void playStart( Track track );
extern void playStop( void );
extern int  putPlayBuf( int c );
extern void playHandler( void );
extern void playInit( void );

extern Track playGetTrackPlaying( void );

#endif /* __PLAY_H */

