/**
 * @file    generic.c
 *
 * @author  
 *
 * @date    18/05/2006
 *
 * @version
 **/
#include "includes.h"

#include "generic.h"
#include "generic_private.h"

//--

char genericString[GEN_STRING_SIZE];

//--

TimerControlBlock delayTimer;
unsigned char sreg;

//--

