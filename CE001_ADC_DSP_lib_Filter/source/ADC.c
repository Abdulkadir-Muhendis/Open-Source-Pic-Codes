/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        ADC.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC30Fxxxx
* Compiler:        MPLAB® C30 v3.00 or higher
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
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
* Hrushikesh Vasuki 07/29/05  First release of source file
* Hrushikesh Vasuki 10/07/05  Mods to increase filter block size to 256
*                             samples and use 30F6014A device
*                             instead of 30F6014
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* This file contains two functions - ADC_Init() and _ADCInterrupt().
*
**********************************************************************/

#include "p30fxxxx.h"
#include "common.h"
#include "dsp.h"

extern fractional inputSignal[NUMSAMP];
extern int doFilterFlag;
extern fractional* iPtr;

//Functions and Variables with Global Scope:
void ADC_Init(void);
void __attribute__((__interrupt__)) _ADCInterrupt(void);

volatile unsigned int * adcPtr;

//Functions:
//ADC_Init() is used to configure A/D to convert 16 samples of 1 input
//channel per interrupt. The A/D is set up for a sampling rate of 8KHz
//Timer3 is used to provide sampling time delay.
//The input pin being acquired and converted is AN7.
void ADC_Init(void)
{
        //ADCON1 Register
        //Set up A/D for Automatic Sampling
        //Use Timer3 to provide sampling time
        //Set up A/D conversrion results to be read in 1.15 fractional
        //number format.
        //All other bits to their default state
        ADCON1bits.FORM = 3;
        ADCON1bits.SSRC = 2;
        ADCON1bits.ASAM = 1;

        //ADCON2 Register
        //Set up A/D for interrupting after 16 samples get filled in the buffer
        //All other bits to their default state
        ADCON2bits.SMPI = 15;

        //ADCON3 Register
        //We would like to set up a sampling rate of 8KHz
        //Total Conversion Time= 1/Sampling Rate = 125 microseconds
        //At 29.4 MIPS, Tcy = 33.9 ns = Instruction Cycle Time
        //Tad > 667ns (for -40C to 125C temperature range)
        //We will set up Sampling Time using Timer3 & Tad using ADCS<5:0> bits
        //All other bits to their default state
        //Let's set up ADCS arbitrarily to the maximum possible amount = 63
        //So Tad = Tcy*(ADCS+1)/2 = 1.085 microseconds
        //So, the A/D converter will take 14*Tad periods to convert each sample
        ADCON3bits.ADCS = 63;

        //Next, we will to set up Timer 3 to time-out every 125 microseconds
        //As a result, the module will stop sampling and trigger a conversion
        //on every Timer3 time-out, i.e., 125 microseconds. At that time,
        //the conversion process starts and completes 14*Tad periods later.
        //When the conversion completes, the module starts sampling again
        //However, since Timer3 is already on and counting, about 110
        //microseconds later (=125 microseconds - 14*Tad), Timer3 will expire
        //again. Effectively, the module samples for 110 microseconds and
        //converts for 15 microseconds
        //NOTE: The actual sampling rate realized may be 7998.698 Hz
        //      due to a small round off error. Ensure you provide the
        //      true sampling rate to dsPICworks if you are trying to plot
        //      the sampled or filtered signal.
        TMR3 = 0x0000;
        PR3 = SAMPCOUNT;
        IFS0bits.T3IF = 0;
        IEC0bits.T3IE = 0;

        //ADCHS Register
        //Set up A/D Channel Select Register to convert AN7 on Mux A input
        ADCHS = 0x0007;

        //ADCSSL Register
        //Channel Scanning is disabled. All bits left to their default state
        ADCSSL = 0x0000;

        //ADPCFG Register
        //Set up channels AN7 as analog input and configure rest as digital
        //Recall that we configured all A/D pins as digital when code execution
        //entered main() out of reset
        ADPCFG = 0xFFFF;
        ADPCFGbits.PCFG7 = 0;

        //Clear the A/D interrupt flag bit
        IFS0bits.ADIF = 0;

        //Set the A/D interrupt enable bit
        IEC0bits.ADIE = 1;

        //Turn on the A/D converter
        //This is typically done after configuring other registers
        ADCON1bits.ADON = 1;

        //Start Timer 3
        T3CONbits.TON = 1;
}

//_ADCInterrupt() is the A/D interrupt service routine (ISR).
//The routine must have global scope in order to be an ISR.
//The ISR name is chosen from the device linker script.
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
        //Clear the Timer3 Interrupt Flag
        IFS0bits.T3IF = 0;

        int i = 0;

        //Clear the A/D Interrupt flag bit or else the CPU will
        //keep vectoring back to the ISR
        IFS0bits.ADIF = 0;

        //Copy the A/D conversion results to variable "inputSignal"
        adcPtr = &ADCBUF0 ;
        for (i=0;i<16;i++)
        {
                *iPtr++ = *adcPtr++;
        }
        if (iPtr > &inputSignal[NUMSAMP]) doFilterFlag = 1;

}
