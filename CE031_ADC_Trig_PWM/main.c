/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; * © 2006 Microchip Technology Inc.
; *
; * FileName:              main.c
; * Dependencies:          Header (.inc) files if applicable, see below
; * Processor:             dsPIC30F2020
; * Compiler:              MPLAB® C30 v3.00 or higher
; * IDE:                   MPLAB® IDE v7.52 or later
; * Hardware Dependencies: dsPICDEM SMPS Buck Development Board
; *
; * SOFTWARE LICENSE AGREEMENT:
; * Microchip Technology Incorporated ("Microchip") retains all ownership and 
; * intellectual property rights in the code accompanying this message and in all 
; * derivatives hereto.  You may use this code, and any derivatives created by 
; * any person or entity by or on your behalf, exclusively with Microchip,s 
; * proprietary products.  Your acceptance and/or use of this code constitutes 
; * agreement to the terms and conditions of this notice.
; *
; * CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
; * WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
; * TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
; * PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP,S 
; * PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
; *
; * YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
; * IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
; * STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
; * PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
; * ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
; * ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
; * ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
; * THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
; * HAVE THIS CODE DEVELOPED.
; *
; * You agree that you are solely responsible for testing the code and 
; * determining its suitability.  Microchip has no obligation to modify, test, 
; * certify, or support the code.
; *
; * REVISION HISTORY:
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; * Author            Date      Comments on this revision
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; * Sunil Fernandes   08/31/06  First release of source file
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; *
; * Description:
; * This code demonstrates the use of PWM Trigger for ADC conversion 		
; * The PWM1 generator will trigger Pair 0 at a time interval from the start
; * of the PWM period. This value is determined by the TRIG1 register. For 	
; * further details refer to the PWM section. The value read by AN0 is then	
; * used to determine the duty cycle.									
; *
; * In this example, the FRC with Hi-Range is set up to run at un-tuned      	
; * frequency of 14.55 MHz. This will result in Fcy = 29.1 MHz. The input       
; * clock to the ADC  clock divider will be Fadc = 232.8 MHz					
; *
; * Tcy = 34.364 nsec  												
; * Time required for one conversion  = 721.64 nsec					
; *
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "p30F2020.h"

/* Configuration Bit Settings */
_FOSCSEL(FRC_PLL)
_FOSC(CSW_FSCM_OFF & FRC_HI_RANGE & OSC2_CLKO)
_FPOR(PWRT_128)
_FGS(CODE_PROT_OFF)
_FBS(BSS_NO_FLASH)


int main(void)
{
	PTPER = 2048;                   /* PWM Period = 2.199 usec @ 29.1 MIPS */
	                                /* Refer to PWM section for more details */	

	/* Initialize PWM Generator 1 */
	
	IOCON1bits.PENH		= 1;        /* PWM Module controls High output */
	IOCON1bits.PENL		= 1;        /* PWM Module controls Low output */
	IOCON1bits.POLH		= 0;        /* High Output Polarity is active High */
	IOCON1bits.POLL		= 0;        /* Low Output Polarity is active High */
	IOCON1bits.PMOD		= 1;        /* Independant output mode */
	IOCON1bits.OVRENH 	= 0;        /* High Output Override disabled */
	IOCON1bits.OVRENL 	= 0;        /* Low Output Override disabled */
	
	TRGCON1bits.TRGDIV = 0;         /* Trigger on evry event */
	TRGCON1bits.TRGSTRT	= 0;        /* Start the counting at the start */
	
	TRIG1 = 200;                    /* Trigger event at  0.214 usec from
	                                   start of the PWM cycle */
										
	PWMCON1bits.FLTSTAT = 0;        /* Clear Fault Interrupt flag */
	PWMCON1bits.CLSTAT = 0;         /* Clear Current Limit Interrupt flag */
	PWMCON1bits.TRGSTAT = 0;        /* Clear PWM Trigger Interrupt flag */
	PWMCON1bits.FLTIEN = 0;         /* Disable Fault Interrupt */
	PWMCON1bits.CLIEN = 0;          /* Disable Current Limit Interrupt */
	PWMCON1bits.TRGIEN = 0;         /* Disable Trigger Interrupt */
	PWMCON1bits.ITB	= 0;            /* Time base is read from PTMR */
	PWMCON1bits.MDCS = 0;           /* Duty cycle is read from PDC */
	PWMCON1bits.DTC	= 2;            /* No Dead Time */
	PWMCON1bits.XPRES = 0;          /* No extenal reset for PTMR */
	PWMCON1bits.IUE = 0;            /* Immediate update to PDC */
										
	PDC1 = 128;                     /* Start with a Ton value of 0.137usec */
	PHASE1 = 0;                     /* No staggering */
		
	/* Intialize the ADC */
	
	ADCONbits.ADSIDL = 0;           /* Operate in Idle Mode */
	ADCONbits.FORM = 0;             /* Output in Integer Format */
	ADCONbits.EIE = 1;              /* Enable Early Interrupt */
	ADCONbits.ORDER = 0;            /* Even channel first */
	ADCONbits.SEQSAMP = 1;          /* Sequential Sampling Enabled */
	ADCONbits.ADCS = 5;             /* Clock Divider is set up for Fadc/14 */
	
	ADPCFG = 0xFFFC;                /* AN0 and AN1 are analog inputs */
	ADSTAT = 0;                     /* Clear the ADSTAT register */
	ADCPC0bits.TRGSRC0 = 0x4;       /* Trigger conversion on PWM#1 Trigger */
	ADCPC0bits.IRQEN0 = 1;          /* Enable the interrupt */
	
	ADCONbits.ADON = 1;             /* Start the ADC module */	
				
	/* Set up the Interrupts */
	
	IFS0bits.ADIF = 0;              /* Clear AD Interrupt Flag */	
	IPC2bits.ADIP = 4;              /* Set ADC Interrupt Priority */
	IEC0bits.ADIE = 1;              /* Enable the ADC Interrupt */
	
	PTCON = 0x8000;                 /* Enable PWM Module */
	 
	while(1);
}

void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt()
{
	int channel0Result;
	
	IFS0bits.ADIF = 0;              /* Clear ADC Interrupt Flag */
	ADSTATbits.P0RDY = 0;           /* Clear the ADSTAT bits */
	channel0Result = ADCBUF0;       /* Get the conversion result */
	
	/* Update the Duty cycle with value read from AN0 
	   PDC value will be such that 7F >= PDC1 >= 3F0 */
	
	PDC1 = (channel0Result >= 0x03F0) ? 0x03F0 :
			 ((channel0Result <= 0x007F) ? 0x007F : channel0Result);
}
