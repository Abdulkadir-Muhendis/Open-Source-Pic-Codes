/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        rtsApi.h
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC30Fxxxx
* Compiler:        MPLAB® C30 v2.01.00 or higher
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Inc. (“Microchip”) licenses this software to you
* solely for use with Microchip dsPIC® digital signal controller
* products. The software is owned by Microchip and is protected under
* applicable copyright laws.  All rights reserved.
*
* SOFTWARE IS PROVIDED “AS IS.”  MICROCHIP EXPRESSLY DISCLAIMS ANY
* WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE, OR NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP
* BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
* DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF
* PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
* BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
* ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS.
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Settu D 			03/15/06  First release of source file
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
*
*
**********************************************************************/
#include "typeDef.h"

#ifndef __RTSPAPI_H__
#define __RTSPAPI_H__ 



// Flash Memory is organised into ROWs of 32 instructions or 96 bytes
// RTSP allows the user to erage/program a row at a time

/*
 * FLASH ROW ERASE
 *
 * Parameters Definition:
 * nvmAdru:	Selects the upper 8bits of the location to program or erase in program flash memory
 * nvmAdr:  Selects the location to program or erase in program flash memory
   It must be aligned to 32 instruction boundary, LSB 6bits of address must be zero
 * Return Value:
 * Function returns ERROREE (or -1), if it is not successful
 * Function return ZERO, if successful
*/
extern int flashRowErase(u16 nvmAdru, u16 nvmAdr);


/*
 * FLASH ROW READ
 *
 * Parameters Definition:
 * nvmAdru:	Selects the upper 8bits of the location to read in program flash memory
 * nvmAdr:  Selects the location to read in program flash memory
   It must be aligned to 32 instruction boundary, LSB 6bits of address must be zero
 * rowBufPtr Pointer to the data array in which read data will be stored

 
 * Return Value:
 * Function returns ERROREE (or -1), if it is not successful
 * Function return ZERO, if successful
*/

extern int flashRowRead(u16 nvmAdru, u16 nvmAdr, u16 *rowBufPtr);


/*
 * FLASH ROW WRITE
 *
 * Parameters Definition:
 * nvmAdru:	Selects the upper 8bits of the location to program or erase in program flash memory
 * nvmAdr:  Selects the location to program or erase in program flash memory
    It must be aligned to 32 instruction boundary, LSB 6bits of address must be zero
 * rowBufPtr Pointer to the data array that needs to be programmed 


 * Return Value:
 * Function returns ERROREE (or -1), if it is not successful
 * Function return ZERO, if successful
*/
extern int flashRowWrite(u16 nvmAdru, u16 nvmAdr, u16 *rowBufPtr);



#endif

