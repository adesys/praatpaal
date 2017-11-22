/**
 * @file    dataflash.h
 *          dataflash definitions
 * 
 * @date    22/05/2006
 **/

#ifndef __DATAFLASH_H
#define __DATAFLASH_H


//--

#define DF_FIRMWARE_INFOPAGE    4000
#define DF_FI_UPDATE_BYTE1_IDX	0
#define DF_FI_UPDATE_BYTE2_IDX	1
#define DF_FI_UPDATE_BYTE3_IDX	2
#define DF_FI_UPDATE_BYTE4_IDX	3
#define DF_FI_UPDATE_BYTE1      0x55
#define DF_FI_UPDATE_BYTE2      0xAA
#define DF_FI_UPDATE_BYTE3      0x33
#define DF_FI_UPDATE_BYTE4      0xCC

#define DF_FI_BYTES_HIGH_IDX    4
#define DF_FI_BYTES_LOW_IDX     5
 
#define DF_FI_CHECKSUM_HIGH_IDX 6
#define DF_FI_CHECKSUM_LOW_IDX  7


#define DF_FIRMWARE_STARTPAGE   4001

#define DF_LASTPAGE             4095

//--

#define DATAFLASHREADBYTE()   dataflashReadWriteByte( 0x00 )

//--

extern unsigned int dataflashGetPageSize( void );
extern void initDataFlash( void );
extern unsigned char dataflashReadWriteByte( unsigned char output );
extern unsigned char dataflashReadStatus( void );
extern void dataflashStartContinuousArrayRead( unsigned long address );
extern void dataflashStopContinuousArrayRead( void );
extern void dataflashBufferWriteByte( unsigned int intPageAdr, unsigned char value );
//extern void dataflashBufferWrite( unsigned int intPageAdr, unsigned int bytes, unsigned char *bufferPtr );
extern void dataflashBufferToPage( unsigned int pageAdr );

#endif /* __DATAFLASH_H */
