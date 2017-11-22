/**
 * @file    dataflash.c
 * 
 * @author  
 *
 * @date    22/05/2006
 *
 * @version 
 **/
#include "includes.h"

#include "dataflash.h"
#include "dataflash_private.h"

//--

/* Globals */
unsigned char dataflashPageBits;
unsigned int  dataflashPageSize;

//--

unsigned int dataflashGetPageSize( void )
{
	return( dataflashPageSize );
}

//--

unsigned char dataflashReadWriteByte( unsigned char output )
{
    unsigned char input;

    SPDR = output;                 //put byte 'output' in SPI data register
    while(!(SPSR & (1<<SPIF)));    //wait for transfer complete, poll SPIF-flag
    input = SPDR;                  //read value in SPI data reg.
	
    return( input );               //return the byte clocked in from SPI slave
}

void initDataFlash( void )
{
    BEGINCRITICAL();

    DATAFLASH_CS_DISABLE();
    DATAFLASH_INIT();

    /* Dataflash uses SPI mode 3 as default: clk is high in idle, data is sampled on the rising edge */
    PORTB |= (1<<PB3) | (1<<PB5);   //Set SDO and CLK high
    DDRB  |= (1<<PB3) | (1<<PB5);   //Set SDO and CLK as output

    SPSR = (1<<SPI2X);                                      //SPI double speed settings
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPHA) | (1<<CPOL);	//Enable SPI in Master mode, mode 3, Fosc/2

    dataflashReadStatus();

    ENDCRITICAL();
}

#ifdef DATAFLASH_ENABLE_READ

unsigned char dataflashReadStatus( void )
{
    unsigned char result, index;
  
    do{
        DATAFLASH_CS_DISABLE();                            //disable DATAFLASH_CS
        DATAFLASH_CS_ENABLE();                             //enable DATAFLASH_CS

        dataflashReadWriteByte( DF_CMD_STATUS );           //write status command
        result = dataflashReadWriteByte( 0x00 );           //dummy write to read status
    } while( result == 0 );

    index = ((result & 0b00111000) >> 3);	                       //get the size info from status register
    dataflashPageBits = __LPM(&DF_PAGEBITS[index]);        //get number of internal page address bits from look-up table
    dataflashPageSize = __LPM(&DF_PAGESIZE[index]) * 264;  //get the size of the page (in bytes)
        
    DATAFLASH_CS_DISABLE();                                //disable DATAFLASH_CS

    return( result );                                      //return the read status register value
}

void dataflashStartContinuousArrayRead( unsigned long address )
{
    unsigned int p, b;;

    p = address / dataflashPageSize;
    b = address % dataflashPageSize;

    DATAFLASH_CS_DISABLE();                                //disable DATAFLASH_CS
    DATAFLASH_CS_ENABLE();                                 //enable DATAFLASH_CS
    
    dataflashReadWriteByte( DF_CMD_CONTARRAYREAD );
    dataflashReadWriteByte( (unsigned char)(p >> (16-dataflashPageBits)) );                        //write address
    dataflashReadWriteByte( (unsigned char)((p << (dataflashPageBits-8)) + (b>>8)));
    dataflashReadWriteByte( (unsigned char)(b) );
}

void dataflashStopContinuousArrayRead( void )
{
    DATAFLASH_CS_DISABLE();                                //disable DATAFLASH_CS
}

#endif /* DATAFLASH_ENABLE_READ */


#ifdef DATAFLASH_ENABLE_WRITE

void dataflashBufferWriteByte( unsigned int intPageAdr, unsigned char value )
{
    DATAFLASH_CS_DISABLE();                                    //disable DATAFLASH_CS
    DATAFLASH_CS_ENABLE();                                     //enable DATAFLASH_CS
	
    dataflashReadWriteByte( DF_CMD_BUFFER1WRITE );             //buffer 1 write op-code
    dataflashReadWriteByte( 0x00 );                            //don't cares
    dataflashReadWriteByte( (unsigned char)(intPageAdr>>8) );  //upper part of internal buffer address
    dataflashReadWriteByte( (unsigned char)(intPageAdr) );     //lower part of internal buffer address
    dataflashReadWriteByte( value );                           //write byte pointed at by *BufferPtr to dataflash buffer 1 location

    DATAFLASH_CS_DISABLE();                                    //disable DATAFLASH_CS
}

void dataflashBufferToPage( unsigned int pageAdr )
{
    DATAFLASH_CS_DISABLE();                                    //disable DATAFLASH_CS
    DATAFLASH_CS_ENABLE();                                     //enable DATAFLASH_CS
	
    dataflashReadWriteByte( DF_CMD_BUFFER1TOFLASHWE );         ///buffer 1 to flash with erase op-code
    dataflashReadWriteByte( (unsigned char)(pageAdr >> (16 - dataflashPageBits)) );  //upper part of internal buffer address
    dataflashReadWriteByte( (unsigned char)(pageAdr << (dataflashPageBits - 8)) );  //lower part of internal buffer address
    dataflashReadWriteByte( 0x00 );                            //don't cares

    DATAFLASH_CS_DISABLE();                                    //disable DATAFLASH_CS
    DATAFLASH_CS_ENABLE();                                     //enable DATAFLASH_CS

    while( !(dataflashReadStatus() & 0x80) );                  //monitor the status register, wait until busy-flag is high

    DATAFLASH_CS_DISABLE();                                    //disable DATAFLASH_CS
}

#endif /* DATAFLASH_ENABLE_WRITE */
