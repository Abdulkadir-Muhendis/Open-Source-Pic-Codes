/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        ADC_conversions_in_SLEEP_mode.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC30F
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
//Macros for Configuration Fuse Registers (copied from device header file):
_FOSC(CSW_FSCM_OFF & XT_PLL8);  //Set up for crystal multiplied by 8x PLL
_FWDT(WDT_OFF);                 //Turn off the Watch-Dog Timer.
_FBORPOR(MCLR_EN & PWRT_OFF);   //Enable MCLR reset pin and turn off the power-up timers.
_FGS(CODE_PROT_OFF);            //Disable Code Protection

//Functions and Variables with Global Scope:
int main (void);
void ADC_Init(void);
void __attribute__((__interrupt__)) _ADCInterrupt(void);

unsigned int conversionResult[16];
volatile unsigned int *ptr;

int main (void)
{
        ADPCFG = 0xFFFF;        //Set AN pins to Digital mode for ICD 2 debugging
        ADC_Init();             //Initialize the A/D converter

        while (1)               //Loop Endlessly - Execution is interrupt driven
        {                       //from this point on.
                Sleep();
        }

        return 0;
}

//Functions:
//ADC_Init() is used to configure A/D to convert 16 samples of 1 input
//channel per interrupt. The A/D is set up for a using the ADRC oscillator
//Automatic conversion trigger is applied after 1Tad of sampling time.
//The input pin being acquired and converted is AN4.
void ADC_Init(void)
{
        //ADCON1 Register
        //Set up A/D for Automatic Sampling
        //Use internal counter (SAMC) to provide sampling time
        //Set up A/D conversrion results to be read in unsigned integer format.
        //Set up Sequential sampling for multiple S/H amplifiers
        //All other bits to their default state
        ADCON1bits.FORM = 0;
        ADCON1bits.SSRC = 7;
        ADCON1bits.ASAM = 1;

        //ADCON2 Register
        //Set up A/D for interrupting after 16 samples get filled in the buffer
        //All other bits to their default state
        ADCON2bits.SMPI = 15;

        //ADCON3 Register
        //We will set up the ADRC as the A/D conversion clock
        //so that the A/D converter can operate when the device is in
        //SLEEP mode. Also, 1 Tad period is allocated for sampling time.
        //The conversion rate for the ADRC oscillator is depends on whether
        //the device is a dsPIC30F or dsPIC33F device and also whether the
        //A/D module is a 10-bit or 12-bit A/D converter.
        //Please refer to the device Datasheet for "ADRC" conversion rate.
        ADCON3bits.SAMC = 1;
        ADCON3bits.ADRC = 1;

        //ADCHS Register
        //Set up A/D Channel Select Register to convert AN4 on Mux A input
        //of CH0 S/H amplifiers
        ADCHS = 0x0004;

        //ADCSSL Register
        //Channel Scanning is disabled. All bits left to their default state
        ADCSSL = 0x0000;

        //ADPCFG Register
        //Set up channels AN4 as analog input and configure rest as digital
        ADPCFG = 0xFFFF;
        ADPCFGbits.PCFG4 = 0;

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
//If the device is in SLEEP mode, the A/D interrupt wakes
//the device up. The device vectors to the A/D ISR upon wake-up.
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
        int i = 0;
        ptr = &ADCBUF0;
        while (i < 16)
        {
                conversionResult[i++] = *ptr++;
        }

        //Clear the A/D Interrupt flag bit or else the CPU will
        //keep vectoring back to the ISR
        IFS0bits.ADIF = 0;

}




/*
EOF
*/


