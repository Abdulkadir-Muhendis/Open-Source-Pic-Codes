/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        main.c
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
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Settu D 			03/15/06  First release of source file
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* Code Tested on:
* dsPICdem1.1+ Demo board with dsPIC30F6014A
**********************************************************************/

#include "p30Fxxxx.h"
#include "typeDef.h"
#include "rtspApi.h"
#include "testData.h"

//-----------------------------------------------------------------------------
//Macros for Configuration Fuse Registers:
//-----------------------------------------------------------------------------
//Invoke macros to set up  device configuration fuse registers.
//The fuses will select the oscillator source, power-up timers, watch-dog
//timers etc. The macros are defined within the device
//header files. The configuration fuse registers reside in Flash memory.
// External Oscillator
_FOSC(CSW_FSCM_OFF & XT_PLL16);  //Run this project using an external crystal
                                //routed via the PLL in 16x multiplier mode
                                //For the 7.3728 MHz crystal we will derive a
                                //throughput of 7.3728e+6*16/4 = 29.4 MIPS(Fcy)
                                //,~33.9 nanoseconds instruction cycle time(Tcy).
_FWDT(WDT_OFF);                 //Turn off the Watch-Dog Timer.
_FBORPOR(MCLR_EN & PWRT_OFF);   //Enable MCLR reset pin and turn off the
                                //power-up timers.
_FGS(CODE_PROT_OFF);            //Disable Code Protection


//-----------------------------------------------------------------------------
unsigned int rowMirrorBuff[32];

// RTSP variable 
u16 nvmAdr,nvmAdru;

// Data to be written to Flash
u16	MyRowDataInRam[64] = { 0,1,2,3,4,5,6,7,8,9,
					   10,11,12,13,14,15,16,17,18,19,
					   20,21,22,23,24,25,26,27,28,29,
					   30,31};

i16 main(void)
{
i16 i,temp;

	PSVPAG = 0;
	CORCONbits.PSV=1;


// Disable Watch Dog Timer
	RCONbits.SWDTEN=0;


// Wait for PLL to lock
	while(OSCCONbits.LOCK!=1) {};	

	nvmAdru=__builtin_tblpage(&MyRowData6InFlash[0]);
	nvmAdr=__builtin_tbloffset(&MyRowData6InFlash[0]);

// Read the row and place the data into rowMirrorBuf array 
	temp = flashRowRead(nvmAdru,nvmAdr, rowMirrorBuff);

// Modify the rowMirrorBuf array
	for(i=0;i<32;i++) {
        rowMirrorBuff[i]=MyRowDataInRam[i];
    }

// Erase the row in Flash
	temp = flashRowErase(nvmAdru,nvmAdr);


// Program the row with modified data
	temp = flashRowWrite(nvmAdru,nvmAdr,rowMirrorBuff);

// Clear Row Mirror Buffer
	for (i=0; i<32;i++) {
		rowMirrorBuff[i]=0;
	}

//Read the row and place the data into rowMirrorBuf array 
	temp = flashRowRead(nvmAdru,nvmAdr, rowMirrorBuff);


	while(1); 
}


