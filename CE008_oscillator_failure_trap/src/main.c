/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        main.c
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

/* Macros for Configuration Fuse Registers (copied from device header file):*/
_FOSC(CSW_FSCM_ON & ECIO_PLL8);   /* Set up for canned oscillator/clock by 8x PLL */
                                /* Ensure FSCM and Clock-switching are ON */
_FWDT(WDT_OFF);                 /* Turn off the Watch-Dog Timer.  */
_FBORPOR(MCLR_EN & PWRT_OFF);   /* Enable MCLR reset pin and turn off the power-up timers. */
_FGS(CODE_PROT_OFF);            /* Disable Code Protection */

/* Global Variables and Functions */
int main (void);

int main (void)
{
                                /* In order to easily create a clock fail */
                                /* condition, we've set up FOSC to use a canned */
                                /* oscillator (EC mode)*/
                                /* When the code starts running in the while Loop */
                                /* simply disconnect your canned oscillator from OSC1 pin*/
                                /* You will observe the pin RD0 toggle at a different rate */
        TRISD = 0x0000;         /* Set PORT D pins as output */
        while (1)               /* Loop endlessly */
        {                       /* If an Oscillator failure occurs, the device will */
                LATDbits.LATD0 = ~LATDbits.LATD0;
        }                       /* vector to the Oscillator Failure Trap */
                                /* Upon return from the trap, the device will operate */
                                /* using FRC oscillator (nominally 7.37MHz) */
                                /* Observe the toggling rate of pin RD0 */
/* Note:
Once you have recovered from the Clock failure (i.e. serviced the
Oscillator Fail trap and are now using the internal FRC), you can
switch back to the crystal if required using a clock switch operation
*/

}


/*
EOF
*/


