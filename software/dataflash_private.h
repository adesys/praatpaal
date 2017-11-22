/**
 * @file    dataflash_private.h
 *          dataflash definitions
 * 
 * @date    22/05/2006
 **/

#ifndef __DATAFLASH_PRIVATE_H
#define __DATAFLASH_PRIVATE_H

//--

#define DATAFLASH_ENABLE_READ
#define DATAFLASH_ENABLE_WRITE

//--

/* Hardware */

#ifndef DATAFLASHPORT
#define DATAFLASHPORT     PORTB
#define DATAFLASHPIN      PINB
#define DATAFLASHDDR      DDRB
#define DATAFLASHBIT      PB2
#endif 

#define DATAFLASH_INIT()        DATAFLASHDDR  |= (1<<DATAFLASHBIT)

// DATAFLASH_CS is low active
#define DATAFLASH_CS_ENABLE()   DATAFLASHPORT &= ~(1<<DATAFLASHBIT)
#define DATAFLASH_CS_DISABLE()  DATAFLASHPORT |= (1<<DATAFLASHBIT)

//--

// Constants
//Look-up table for these sizes ->    512k, 1M, 2M, 4M, 8M, 16M, 32M, 64M
PROGMEM unsigned char DF_PAGEBITS[] = {  9,  9,  9,  9,  9,  10,  10,  11};	//index of internal page address bits
//Look-up table for these sizes ->    512k, 1M, 2M, 4M, 8M, 16M, 32M, 64M
PROGMEM unsigned char DF_PAGESIZE[] = {  1,  1,  1,  1,  1,  2,   2,   4};	//index of pagesizes (n * 264)

/* Commands */
#define DF_CMD_CONTARRAYREAD     0x03
#define DF_CMD_STATUS            0xD7
#define DF_CMD_BUFFER1WRITE      0x84
#define DF_CMD_BUFFER1TOFLASHWE  0x83

//--

unsigned int dataflashGetPageSize( void );

/**
 * initDataFlash: Init
 * Init dataflash
 *
 * @par        None
 *
 * @return     None
 *
 * @see        
 **/
void initDataFlash( void );

/**
 * dataflashReadWriteByte:
 *   write to SPI and then read from SPI 
 *
 * @par        output: byte to write
 *
 * @return     input: byte read
 *
 * @see        
 **/
unsigned char dataflashReadWriteByte( unsigned char output );

/**
 * dataflashReadStatus:
 *   Read status byte
 *   Also inits the pagebit an pagesize globals
 *
 * @par        output: byte to write
 *
 * @return     input: byte read
 *
 * @see dataflashPageBits, dataflashPageSize       
 **/
unsigned char dataflashReadStatus( void );

/**
 * dataflashStartContinuousArrayRead:
 *   Start Contineous Array Read
 *   Also inits the pagebit an pagesize globals
 *
 * @par        output: byte to write
 *
 * @return     input: byte read
 *
 * @see dataflashPageBits, dataflashPageSize, dataflashStopContinuousArrayRead     
 **/
void dataflashStartContinuousArrayRead( unsigned long address );

/**
 * dataflashStopContinuousArrayRead:
 *   Stop Contineous Array Read
 *
 * @par        None
 *
 * @return     None
 *
 * @see dataflashStartContinuousArrayRead
 **/
void dataflashStopContinuousArrayRead( void );

void dataflashBufferWriteByte( unsigned int intPageAdr, unsigned char value );
//void dataflashBufferWrite( unsigned int intPageAdr, unsigned int bytes, unsigned char *bufferPtr );
void dataflashBufferToPage( unsigned int pageAdr );

#endif /* __DATAFLASH_PRIVATE_H */
