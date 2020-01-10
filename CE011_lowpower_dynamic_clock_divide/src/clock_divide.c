/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        clock_divide.c
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

int clockDivide (unsigned int); //Subroutine to perform dynamic clock division operation


/*
Function:       int clockDivide (unsigned int)
Input:          int data type equal in value to 1, 4, 16 or 64
Return:         RET_CODE_OSC_SUCCESS for successful dynamic clock divide
                RET_CODE_OSC_ERROR for illegal clock divide request (i.e. values other than 1, 4, 16, 64)
Description:    This subroutine performs an OSCCONL unlock and then writes the
                correct requested clock divide value into the POST<1:0> bits in OSCCONL.
*/
int clockDivide (unsigned int dividerValue)
{
        int current_cpu_ipl;    /* declare temp variable for CPU IPL storing */
        char a, b, c, *p;
        b = OSCCONL_UNLOCK_CODE1;
        c = OSCCONL_UNLOCK_CODE2;
        p = (char *)&OSCCON;
        a = OSCCON;
        a = a & ZERO_MASK_FOR_POST_IN_OSCCON;

        switch (dividerValue)
        {
                case 1: a |= DIVIDE_BY_1 ;
                        break;
                case 4: a |= DIVIDE_BY_4 ;
                        break;
                case 16: a |= DIVIDE_BY_16;
                        break;
                case 64: a |= DIVIDE_BY_64;
                        break;
                default: return (RET_CODE_OSC_ERROR);
        }


        SET_AND_SAVE_CPU_IPL(current_cpu_ipl, 7);       /* Disable interrupts for unlock sequence below */

        /* Write Oscillator Post-scaler here low byte unlock sequence and enable LP Oscillator */
        asm volatile ("mov.b %1,[%0] \n"
                  "mov.b %2,[%0] \n"
                  "mov.b %3,[%0] \n" : /* no outputs */ : "r"(p), "r"(b), "r"(c),
                                                          "r"(a));

        /* restore CPU IPL value after executing unlock sequence */
        RESTORE_CPU_IPL(current_cpu_ipl);

        return RET_CODE_OSC_SUCCESS;
}

/*
EOF
*/


