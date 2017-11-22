/**
 * @file    powersupply.c
 *
 * @author  
 *
 * @date    18/05/2006
 *
 * @version
 **/
#include "includes.h"

#include "powersupply.h"
#include "powersupply_private.h"


//--

void powersupplyInit( void)
{
    PWROFF_DISABLE();
    PWROFF_INIT();
    
    PWRONPIEZO_INIT();

    PCICR = (1<<PCIE1);                         //enable pin change interrupt
    PCMSK1 = (1<<PCINT11);                      // on PC3 (piezo)
}

void powersupplyOff( void )
{
    /* Switch off the powersupply.
     * If the ISP activated the powersupply (PWR-ON-ISP=0), the poweroff output
     *   is overruled and the powersupply will stay on.
     * If PWR-ON-ISP is 1 or becomes 1, then the powersupply is switched off.
     * The PWN-OFF pin must be pulsed because the piezo can be pressed again before
     * we are actually powered down. If PWR_OFF is held active then the power-down
     * can't be interrupted again by the piezo.
     * V1.03: 18/12/2006
     *   Desided is to hold the PWR_OFF active, to be sure the unit is powered down.
     *   This is more critical because of change in hardware (C201 connected to GND).
     *   So consequence is off cource that the user must wait until the unit is powered
     *   dowm before the piezo will be detected again.
     */
    PWROFF_ENABLE();
}


