/**
 * @file    play_private.h
 *
 * @author  
 *
 * @date    18/05/2006
 *
 * @version
 **/
#ifndef __PLAY_PRIVATE_H
#define __PLAY_PRIVATE_H

#include "play.h"

//--

#define TRACKINDEXSTART 0L

#define MAXTRACKS     1
#define TRACKSTART    0
#define TRACKEND      1

//--

Track playGetTrackPlaying( void );
void playGetTrackIndex( void );
void playInit( void );
bool playIsBusy( void );
void playStart( Track track );
void playStop( void );
void playHandler( void );

//--

#endif /* __PLAY_PRIVATE_H */

