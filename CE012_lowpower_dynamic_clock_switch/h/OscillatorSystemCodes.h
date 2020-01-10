/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        OscillatorSystemCodes.h
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC30Fxxxx
* Compiler:        MPLAB® C30 v3.00 or higher
* IDE:             MPLAB® IDE v7.52 or later
* Dev. Board Used: dsPICDEM 1.1 Development Board
* Hardware Dependencies: None
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
* HV               09/30/05  First release of source file
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* This header file contains useful constants to configure OSCCON.
* This header file is used by Code Examples published by Microchip for
* performing clock switch, clock divide and FRC tuning functions on
* the dsPIC30F device family
**********************************************************************/

#define RET_CODE_OSC_ERROR      -1      /*Error code to return on illegal request*/
#define RET_CODE_OSC_SUCCESS    0       /*Error code to return on successful request*/

#define OSCCONH_UNLOCK_CODE1    0x78    //First byte in OSCCONH unlock sequence
#define OSCCONH_UNLOCK_CODE2    0x9A    //Second byte in OSCCONH unlock sequence
#define OSCCONL_UNLOCK_CODE1    0x46    //First byte in OSCCONL unlock sequence
#define OSCCONL_UNLOCK_CODE2    0x57    //Second byte in OSCCONL unlock sequence

#define DIVIDE_BY_1             0x00    //Value to load into OSCCONL for Fcy/1
#define DIVIDE_BY_4             0x40    //Value to load into OSCCONL for Fcy/4
#define DIVIDE_BY_16            0x80    //Value to load into OSCCONL for Fcy/16
#define DIVIDE_BY_64            0xC0    //Value to load into OSCCONL for Fcy/64


#define NOMINAL_PLUS_7_STEPS    7       //Value to load into TUN bits to change
#define NOMINAL_PLUS_6_STEPS    6       //FRC from nominal value
#define NOMINAL_PLUS_5_STEPS    5
#define NOMINAL_PLUS_4_STEPS    4
#define NOMINAL_PLUS_3_STEPS    3
#define NOMINAL_PLUS_2_STEPS    2
#define NOMINAL_PLUS_1_STEPS    1
#define NOMINAL                 0
#define NOMINAL_MINUS_1_STEPS   -1
#define NOMINAL_MINUS_2_STEPS   -2
#define NOMINAL_MINUS_3_STEPS   -3
#define NOMINAL_MINUS_4_STEPS   -4
#define NOMINAL_MINUS_5_STEPS   -5
#define NOMINAL_MINUS_6_STEPS   -6
#define NOMINAL_MINUS_7_STEPS   -7
#define NOMINAL_MINUS_8_STEPS   -8

/* The following defines have been provided for devices that contain Oscillator Version 1 and 2 */
#if defined (__dsPIC30F4011__) || defined (__dsPIC30F4012__) || defined (__dsPIC30F5011__) || defined (__dsPIC30F5013__) || \
defined (__dsPIC30F2010__) || defined (__dsPIC30F6010__) || defined (__dsPIC30F6011__) || defined (__dsPIC30F6012__) || \
defined (__dsPIC30F6013__) ||defined (__dsPIC30F6014__)
                                        //Value to load into OSCCONH.NOSC bits for:
#define NOSC_PRIOSC     0x03            //Primary Oscillator source selected by FOSC fuse - FPR bits
#define NOSC_LPRC       0x02            //Intenal LPRC oscillator
#define NOSC_FRC        0x01            //Internal Fast RC oscillator
#define NOSC_LP         0x00            //Secondary Low-Power 32KHz oscillator on SOSC pins

//AND-ing OSCCON with the values below will zero out the OSCCON bit field specified in the comments:
#define ZERO_MASK_FOR_NOSC_IN_OSCCON 0xFCFF     //NOSC1:NOSC0 mask
#define ZERO_MASK_FOR_TUN_IN_OSCCON 0x33FF      //TUN3:TUN0 mask
#define ZERO_MASK_FOR_POST_IN_OSCCON 0xFF3F     //POST1:POST0 mask

/* The following defines have been provided for devices that contain Oscillator Version 3 */
#elif defined (__dsPIC30F2011__) || defined (__dsPIC30F2012__) || defined (__dsPIC30F3010__) || defined (__dsPIC30F3011__) || \
    defined (__dsPIC30F3012__) || defined (__dsPIC30F3013__) || defined (__dsPIC30F3014__) || defined (__dsPIC30F4013__) || \
    defined (__dsPIC30F5015__) || defined (__dsPIC30F5016__) || defined (__dsPIC30F6015__) || defined (__dsPIC30F6010A__)|| \
    defined (__dsPIC30F6011A__)|| defined (__dsPIC30F6012A__)|| defined (__dsPIC30F6013A__)|| defined (__dsPIC30F6014A__)

                                        //Value to load into OSCCONH.NOSC bits for:
#define NOSC_PLLOSC     0x07            //PLL source selected by FOSC fuse - FPR bits
#define NOSC_EXTOSC     0x03            //External Oscillator source selected by FOSC fuse - FPR bits
#define NOSC_LPRC       0x02            //Intenal LPRC oscillator
#define NOSC_FRC        0x01            //Internal Fast RC oscillator
#define NOSC_LP         0x00            //Secondary Low-Power 32KHz oscillator on SOSC pins

//AND-ing OSCCON with the values below will zero out the OSCCON bit field specified in the comments:
#define ZERO_MASK_FOR_NOSC_IN_OSCCON 0xF8FF     //NOSC2:NOSC0 mask
#define ZERO_MASK_FOR_POST_IN_OSCCON 0xFF3F     //POST1:POST0 mask



#endif


/*
EOF
*/
