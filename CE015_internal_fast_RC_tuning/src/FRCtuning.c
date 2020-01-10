/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        FRCtuning.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC30Fxxxx
* Compiler:        MPLAB® C30 v3.00 or higher
* IDE:             MPLAB® IDE v7.52 or later
* Dev. Board Used: dsPICDEM 1.1 Development Board
* Hardware Dependencies: None
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip,s 
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP,S 
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify, test, 
* certify, or support the code.
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
*
**********************************************************************/

#include "p30fxxxx.h"
#include "OscillatorSystemCodes.h"


int FRC_Freq_Change(int);
/*
Function:       int FRC_Freq_Change(int)
Input:          signed int data type equal in the range [-8,+7]
Return:         RET_CODE_OSC_SUCCESS for valid FRC tuning request
                RET_CODE_OSC_ERROR for illegal FRC tuning request (i.e. values
                outside range [-8,+7])
Description:    This subroutine writes to TUN bits which are present in the
                OSCTUN register (for some devices) or the OSCCON register (for
                some other devices)
*/

int FRC_Freq_Change(int newFRCTunVal)
{
#if defined (__dsPIC30F2011__) || defined (__dsPIC30F2012__) || defined (__dsPIC30F3010__) || \
    defined (__dsPIC30F3011__) || defined (__dsPIC30F3012__) || defined (__dsPIC30F3013__) || \
    defined (__dsPIC30F3014__) || defined (__dsPIC30F4013__) || defined (__dsPIC30F5015__) || \
    defined (__dsPIC30F5016__) || defined (__dsPIC30F6015__) || defined (__dsPIC30F6010A__)|| \
    defined (__dsPIC30F6011A__)|| defined (__dsPIC30F6012A__)|| defined (__dsPIC30F6013A__)|| \
    defined (__dsPIC30F6014A__)

        OSCTUN = newFRCTunVal;

#elif defined (__dsPIC30F4011__) || defined (__dsPIC30F4012__) || defined (__dsPIC30F5011__) || \
    defined (__dsPIC30F5013__) defined (__dsPIC30F2010__) || defined (__dsPIC30F6010__) || \
    defined (__dsPIC30F6011__) || defined (__dsPIC30F6012__) || defined (__dsPIC30F6013__) || \
    defined (__dsPIC30F6014__)

        unsigned int temp;
        int current_cpu_ipl;                            /* Declare temp variable for storing CPU IPL */
        char b, c, *p;

        b = OSCCONH_UNLOCK_CODE1;                       /* Load OSCCONH unlock sequence parameters */
        c = OSCCONH_UNLOCK_CODE2;
        p = (char *)&OSCCON + 1;

        temp = OSCCON;
        temp = temp & ZERO_MASK_FOR_TUN_IN_OSCCON;

        switch (newFRCTunVal)
        {
                case 7: temp = temp | 0x4C00 ;
                        break;

                case 6: temp = temp | 0x4800 ;
                        break;

                case 5: temp = temp | 0x4400 ;
                        break;

                case 4: temp = temp | 0x4000 ;
                        break;

                case 3: temp = temp | 0x0C00 ;
                        break;

                case 2: temp = temp | 0x0800 ;
                        break;

                case 1: temp = temp | 0x0400 ;
                        break;

                case 0: temp = temp | 0x0000 ;
                        break;

                case -1: temp = temp | 0xCC00 ;
                        break;

                case -2: temp = temp | 0xC800 ;
                        break;

                case -3: temp = temp | 0xC400 ;
                        break;

                case -4: temp = temp | 0xC000 ;
                        break;

                case -5: temp = temp | 0x8C00 ;
                        break;

                case -6: temp = temp | 0x8800 ;
                        break;

                case -7: temp = temp | 0x8400 ;
                        break;

                case -8: temp = temp | 0x8000 ;
                        break;

                default: return (RET_CODE_OSC_ERROR);
        }

        temp = temp >> 8;

        SET_AND_SAVE_CPU_IPL(current_cpu_ipl, 7);       /* Disable interrupts for unlock sequence below */

        /* Perform OSCCONH unlock sequence and write the new oscillator value to the NOSC bits */
        asm volatile ("mov.b %1,[%0] \n"
                  "mov.b %2,[%0] \n"
                  "mov.b %3,[%0] \n" : /* no outputs */ : "r"(p), "r"(b), "r"(c),
                                                          "r"(temp));

        RESTORE_CPU_IPL(current_cpu_ipl);               /* Restore CPU IPL value after executing unlock sequence */

        return RET_CODE_OSC_SUCCESS ;

#endif

}


/*
EOF
*/


