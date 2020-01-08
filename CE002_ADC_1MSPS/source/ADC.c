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
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* This file contains two functions - ADC_Init() and _ADCInterrupt().
*
**********************************************************************/

#include "p30fxxxx.h"


unsigned int ADResult1 = 0;
unsigned int ADResult2 = 0;

//Functions and Variables with Global Scope:
void ADC_Init(void);
void __attribute__((__interrupt__)) _ADCInterrupt(void);

//Functions:
//ADC_Init() is used to configure A/D to convert 16 samples of 1 input
//channel per interrupt. The A/D is set up for a sampling rate of 1MSPS
//Timer3 is used to provide sampling time delay.
//The input pin being acquired and converted is AN7.
void ADC_Init(void)
{
        //ADCON1 Register
        //Set up A/D for Automatic Sampling
        //Use internal counter (SAMC) to provide sampling time
        //Set up A/D conversrion results to be read in 1.15 fractional
        //number format.
        //Set up Sequential sampling for multiple S/H amplifiers
        //All other bits to their default state
        ADCON1bits.FORM = 3;
        ADCON1bits.SSRC = 7;
        ADCON1bits.ASAM = 1;
        ADCON1bits.SIMSAM = 0;

        //ADCON2 Register
        //Set up A/D for interrupting after 2 samples get filled in the buffer
        //Set up to sample on 2 S/H amplifiers - CH0 and CH1
        //All other bits to their default state
        ADCON2bits.SMPI = 1;
        ADCON2bits.CHPS = 1;
	//ADCON2bits.VCFG = 3; //Ideally use external references

        //ADCON3 Register
        //We would like to set up a sampling rate of 1 MSPS
        //Total Conversion Time= 1/Sampling Rate = 125 microseconds
        //At 29.4 MIPS, Tcy = 33.9 ns = Instruction Cycle Time
        //The A/D converter will take 12*Tad periods to convert each sample
        //So for ~1 MSPS we need to have Tad close to 83.3ns
        //Using equaion in the Family Reference Manual we have
        //ADCS = 2*Tad/Tcy - 1
        ADCON3bits.SAMC = 0;
        ADCON3bits.ADCS = 4;

        //ADCHS Register
        //Set up A/D Channel Select Register to convert AN3 on Mux A input
        //of CH0 and CH1 S/H amplifiers
        ADCHS = 0x0023;

        //ADCSSL Register
        //Channel Scanning is disabled. All bits left to their default state
        ADCSSL = 0x0000;

        //ADPCFG Register
        //Set up channels AN7 as analog input and configure rest as digital
        //Recall that we configured all A/D pins as digital when code execution
        //entered main() out of reset
        ADPCFG = 0xFFFF;
        ADPCFGbits.PCFG3 = 0;

        //Clear the A/D interrupt flag bit
        IFS0bits.ADIF = 0;

        //Set the A/D interrupt enable bit
        IEC0bits.ADIE = 1;

        //Turn on the A/D converter
        //This is typically done after configuring other registers
        ADCON1bits.ADON = 1;

}

//_ADCInterrupt() is the A/D interrupt service routine (ISR).
//The routine must have global scope in order to be an ISR.
//The ISR name is chosen from the device linker script.
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
	ADResult1 = ADCBUF0;
	ADResult2 = ADCBUF1;
	
        //Clear the A/D Interrupt flag bit or else the CPU will
        //keep vectoring back to the ISR
        IFS0bits.ADIF = 0;
	
        
}

