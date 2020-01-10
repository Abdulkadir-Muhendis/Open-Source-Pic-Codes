/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        fast_wake_up_from_SLEEP_mode.c
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

#if defined (__dsPIC30F6010__) || defined (__dsPIC30F6011__) || defined (__dsPIC30F6012__) || defined (__dsPIC30F6013__) || \
    defined (__dsPIC30F6014__) || defined (__dsPIC30F2010__)
_FOSC(CSW_FSCM_OFF & FRC);       /* Set up for Internal Fast RC*/
#else
/* Macros for Configuration Fuse Registers (copied from device header file):*/
_FOSC(CSW_FSCM_OFF & FRC_PLL16); /* Set up for Internal Fast RC by 16x PLL */
#endif

_FWDT(WDT_OFF);                 /* Turn off the Watch-Dog Timer.  */
_FBORPOR(MCLR_EN & PWRT_OFF);   /* Enable MCLR reset pin and turn off the power-up timers. */
_FGS(CODE_PROT_OFF);            /* Disable Code Protection */

/* Global Variables and Functions */
int main (void);
void INT1_Init(void);
void __attribute__((__interrupt__)) _INT1Interrupt(void);

int main (void)
{
        ADPCFG = 0xFFFF;        /* Configure ANx pins used by ICD for digital i/o*/
        TRISD = 0x0000;         /* LEDs on dsPICDEM 1.1 board are connected to RD0-RD3 */
        LATD = 0x0000;          /* We will configure Port D to be output so we can use */
                                /* use LEDs as an indicator of the occurrence of external */
                                /* interrupts */

        INT1_Init();            /* Call function to initialize the External Interrupt- INT1 */
        while (1)               /* Loop endlessly */
        {
                Sleep();        /* View the time between the falling edge on the INT1 pin*/
                                /* and the toggling of Port D pins to estimate the */
                                /* time it takes to wake up from SLEEP */
                /*NOTE: In this project, we set up FOSC so that the device */
                /*operates using the Internal Fast RC oscillator and the PLL 16 multiplier mode */
                /*The PLL has a lock time of ~20us. So the device will wake up*/
                /*and execute code in the INT1 ISR within 30us(=10us+20us). Further, it */
                /*run at a throughput of ~29.4 MIPS upon wake-up.*/
                /*NOTE2: If you need the device to wake up in less than 10us*/
                /*simply, configure the FOSC to use the FRC mode without PLL*/
        }
}
/*
Functions:
INT1_Init() sets up the INT1 pin.
INT1 pin on the 30F6014A device is connected to switch S1, on the dsPICDEM1.1 board.
*/
void INT1_Init(void)
{
        //S1 connected to INT1
        INTCON2 = 0x0002;       /*Setup INT1 to interupt on falling edge*/
        IFS1bits.INT1IF = 0;    /*Reset INT1 interrupt flag */
        IEC1bits.INT1IE = 1;    /*Enable INT1 Interrupt Service Routine */
}


/*
_INT1Interrupt() is the INT1 interrupt service routine (ISR).
The routine must have global scope in order to be an ISR.
The ISR name is chosen from the device linker script.
*/
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void)
{
        LATD ^= 0xFFFF;         /* Toggle Port D bits */
        Nop();
        LATD ^= 0xFFFF;         /* Toggle Port D bits */
        IFS1bits.INT1IF = 0;    /* Clear the INT1 interrupt flag or else */
                                /* the CPU will keep vectoring back to the ISR */
                                /* View the time between the falling edge on the INT1 pin*/
                                /* and the rising edge of Port D pins to estimate the */
                                /* time it takes to wake up from SLEEP */
        /*NOTE: In this project, we set up FOSC so that the device */
        /*operates using the Internal Fast RC oscillator and the PLL 16 multiplier mode */
        /*The PLL has a lock time of ~20us. So the device will wake up*/
        /*and execute code in the INT1 ISR within 30us (=10us+20us). Further, it */
        /*run at a throughput of ~29.4 MIPS upon wake-up.*/
        /*NOTE2: If you need the device to wake up in 10us*/
        /*simply, configure the FOSC to use the FRC mode without PLL*/
}


/*
EOF
*/


