/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        clock_switch.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC30Fxxxx
* Compiler:        MPLAB® C30 v3.00 or higher
* IDE:             MPLAB® IDE 7.52 or later
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
* Ensure Clock Switching has been enabled in FOSC configuration register
* if you need to use the functions in this file.
**********************************************************************/

#include "p30fxxxx.h"
#include "OscillatorSystemCodes.h"

int clockSwitch (unsigned int);        /*Subroutine to perform dynamic clock switching operation*/

/*
Function:       int clockSwitch (unsigned int)
Input:          int data type of a value chosen from OscillatorSystemCodes.h file
                Valid values are 0,1,2,3 and for devices featuring Oscillator System version 3
                a value of 7 is also supported. Please read the dsPIC30F Family Reference Manual
                for further details.
Return:         RET_CODE_OSC_SUCCESS for a successful clock switch operation
                RET_CODE_OSC_ERROR for an illegal clock switch request
Description:    This subroutine performs an OSCCONH unlock and then writes the
                requested new oscillator source value to OSCCONH. Next, it
                unlocks OSCCONL and sets the OSWEN bit to initiate a clock-switch.
                The subroutine returns when OSWEN has been cleared by hardware
                to indicate a successful clock switch.
*/
int clockSwitch (unsigned int newNOSCCode)
{
        int current_cpu_ipl;                            /* Declare temp variable for storing CPU IPL */
        int newOSCCONHCode;
        char a, b, c, *p;

        newOSCCONHCode = OSCCON;
        newOSCCONHCode = newOSCCONHCode & ZERO_MASK_FOR_NOSC_IN_OSCCON;
        newOSCCONHCode = newOSCCONHCode >> 8;

        switch (newNOSCCode)
        {
                case 0: newOSCCONHCode = newOSCCONHCode | newNOSCCode ;
                        break;
                case 1: newOSCCONHCode = newOSCCONHCode | newNOSCCode ;
                        break;
                case 2: newOSCCONHCode = newOSCCONHCode | newNOSCCode ;
                        break;
                case 3: newOSCCONHCode = newOSCCONHCode | newNOSCCode ;
                        break;
#if defined (__dsPIC30F2011__) || defined (__dsPIC30F2012__) || defined (__dsPIC30F3010__) || defined (__dsPIC30F3011__) || \
    defined (__dsPIC30F3012__) || defined (__dsPIC30F3013__) || defined (__dsPIC30F3014__) || defined (__dsPIC30F4013__) || \
    defined (__dsPIC30F5015__) || defined (__dsPIC30F5016__) || defined (__dsPIC30F6015__) || defined (__dsPIC30F6010A__)|| \
    defined (__dsPIC30F6011A__)|| defined (__dsPIC30F6012A__)|| defined (__dsPIC30F6013A__)|| defined (__dsPIC30F6014A__)

                case 7: newOSCCONHCode = newOSCCONHCode | newNOSCCode ;
                        break;
#endif
                default: return RET_CODE_OSC_ERROR ;
        }

        b = OSCCONH_UNLOCK_CODE1;                       /* Load OSCCONH unlock sequence parameters */
        c = OSCCONH_UNLOCK_CODE2;
        p = (char *)&OSCCON + 1;

        SET_AND_SAVE_CPU_IPL(current_cpu_ipl, 7);       /* Disable interrupts for unlock sequence below */

        /* Perform OSCCONH unlock sequence and write the new oscillator value to the NOSC bits */
        asm volatile ("mov.b %1,[%0] \n"
                  "mov.b %2,[%0] \n"
                  "mov.b %3,[%0] \n" : /* no outputs */ : "r"(p), "r"(b), "r"(c),
                                                          "r"(newOSCCONHCode));

        b = OSCCONL_UNLOCK_CODE1;                       /* Load OSCCONL unlock sequence parameters */
        c = OSCCONL_UNLOCK_CODE2;
        p = (char *)&OSCCON;
        a = OSCCON | 0x01;

        /* Perform OSCCONL unlock sequence and request an Oscillator switch by setting OSWEN bit */
        asm volatile ("mov.b %1,[%0] \n"
                  "mov.b %2,[%0] \n"
                  "mov.b %3,[%0] \n" : /* no outputs */ : "r"(p), "r"(b), "r"(c),
                                                          "r"(a));
        while (OSCCONbits.OSWEN);                       /* Wait until OSWEN has been cleared by hardware */

        RESTORE_CPU_IPL(current_cpu_ipl);               /* Restore CPU IPL value after executing unlock sequence */

        return RET_CODE_OSC_SUCCESS ;
}


/*
EOF
*/


