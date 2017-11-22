/**
 * @file    hardware.c
 *
 * @author  
 *
 * @date    18/05/2006
 *
 * @version
 **/
#include "includes.h"

#include "hardware.h"
#include "hardware_private.h"

#include "dataflash.h"
#include "powersupply.h"


/* NOTE: 16 bits registers
 *   Some of the timer-related 16-bit IO registers use a temporary register
 *   TCNT1, ICR1, OCR1A, OCR1B, ADCW
 *   (called TEMP in the Atmel datasheet) to guarantee an atomic access to the
 *   register despite the fact that two separate 8-bit IO transfers are required
 *   to actually move the data. Typically, this includes access to the current
 *   timer/counter value register (TCNTn), the input capture register (ICRn),
 *   and write access to the output compare registers (OCRnM). Refer to the actual
 *   datasheet for each device's set of registers that involves the TEMP register.
 *   When accessing one of the registers that use TEMP from the main application,
 *   and possibly any other one from within an interrupt routine, care must be taken
 *   that no access from within an interrupt context could clobber the TEMP register
 *   data of an in-progress transaction that has just started elsewhere.
 */

/* NOTE: I/O port
 * When init the I/O ports, set the output value before
 * the direction is set to output to prevent a glitch.
 */

void initIO( void )
{
    /* Port B
     *   0 O MDM-ON  OFF (=0)
     *   1 O PWM     1 (Setting this to '1' prevents a loud tick on the speaker)
     *   2 O SPI-CS1 Not active (=1)
     *   3 O SPI-SDO Not active (=1)
     *   4 I SPI-SDI no pull-up (=0)
     *   5 O SPI-SCK Not active (=1)
     */
    PORTB = 0x2E;        // 0b00101110;
    DDRB  = 0xEF;        // 0b11101111;

    /* Port C
     *   0 O NC        
     *   1 O OUT1      OFF (=0)
     *   2 O PWR-OFF   OC-PASSIVE (=0)
     *   3 I PWR-PIEZO pull-up (=1)
     *   4 I I2C-SDA   no pull-up (=0)
     *   5 0 I2C-SCL   0
     *   6 I RESET     0
     */
    PORTC = 0x08;        // 0b00001000;
    DDRC  = 0xA7;        // 0b10100111;

    /* Port D
     *   0 I UART-RX   no pull-up (=0)
     *   1 O UART-TX   1
     *   2 O UART-SEL  COMPORT (=1)
     *   3 I MDM-SYNC  no pull-up (=0)
     *   4 O MDM-EMOFF OC-PASSIVE (=0)
     *   5 I MDM-VDD   no pull-up (=0)
     *   6 O MDM-DTR   ACTIVE (=0)
     *   7 I MDM-DCD   no pull-up (=0)
     */
    PORTD = 0x06;        // 0b00000110;
    DDRD  = 0x56;        // 0b01010110;
}

void initHardware( void )
{
    /* Init I/O */
    initIO();

    /* Init powersupply module hardware */
    powersupplyInit();
}

void setUartSel( unsigned char sel )
{
    if( sel == UARTSEL_MDM )
    {
        UARTSEL_OFF();
    }
    else
    {
        UARTSEL_ON();
    }
}
