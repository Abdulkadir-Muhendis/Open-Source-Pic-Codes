/***********************************************************************
; * © 2006 Microchip Technology Inc.
; *
; * FileName:        PWM Dither.c
; * Dependencies:    Header (.inc) files if applicable, see below
; * Processor:       dsPIC30F2020
; * Compiler:        MPLAB® C30 v3.00 or higher
; * IDE:             MPLAB® IDE v7.52 or later
; * Dev. Board Used: Sync Buck Converter Using SMPS dsPIC
; *
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
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; * Author            Date      Comments on this revision
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; * Sagar Khare       09/26/06  First release of source file
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; *
; * Description:
; * This program illustrates the use of the Dithering mode of the SMPS dsPIC
; * devices. It uses a sequential tuning of the FRC oscillator to produce a 
; * +/- 3% dither in the frequency.
; * The dithering mode is useful in reducing the effective EMI produced by 
; * high frequency switching of semiconductor switches used in switched mode
; * power supply applications.
; * In this program, PWM1 and PWM2 are configured in the complementary mode
; * and produce constant duty cycles. The dither mode will cause the PWM
; * signals to jitter about the factory calibrated frequency.
; * All timings are calculated assuming 30 MIPS operation.
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#include "p30f2020.h"

/* Configuration Bit Settings */
_FOSCSEL(FRC_PLL)
_FOSC(CSW_FSCM_OFF & FRC_HI_RANGE & OSC2_CLKO)
_FPOR(PWRT_128)
_FGS(CODE_PROT_OFF)
_FBS(BSS_NO_FLASH)

int main()
{
    //~~~~~~~~~~~~~~~~~~~~~~~ FRC Dither Configuration ~~~~~~~~~~~~~~~~~~~~~~~~
     __builtin_write_OSCCONL(4);            // Built-in function to unlock
    							  // OSCCON register
							  // Writing 0x0004 sets the TSEQEN  
							  // bit to enable FRC tune sequencer

    // FRC will tune to one of the following every 8 PWM cycles
    OSCTUNbits.TUN = 8;                     // Minimum frequency
    OSCTUNbits.TSEQ1 = 10; 
    OSCTUNbits.TSEQ2 = 12;
    OSCTUNbits.TSEQ3 = 14;
    OSCTUN2bits.TSEQ4 = 1;
    OSCTUN2bits.TSEQ5 = 3;
    OSCTUN2bits.TSEQ6 = 5;    
    OSCTUN2bits.TSEQ7 = 7;                   // Maximum frequency    
    
    //~~~~~~~~~~~~~~~~~~~~End FRC Dither Configuration ~~~~~~~~~~~~~~~~~~~~~~~~
    
        
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~ PWM Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    PTPER = 9520;                           // PWM period of 10 usec
    
    PDC1 = 4761;                            // PWM1 pulse width of 5 usec
    PDC2 = 2380;                            // PWM2 pulse width of 2.5 usec
    
    DTR1 = 64;                              // 67.2 nsec dead time
    DTR2 = 64;                              // 67.2 nsec dead time
    
    ALTDTR1 = 64;                           // 67.2 nsec dead time
    ALTDTR2 = 64;                           // 67.2 nsec dead time
    
    IOCON1bits.PENH = 1;                    // PWM1 outputs controlled by PWM 
    IOCON1bits.PENL = 1;                    // module
    
    IOCON2bits.PENH = 1;                    // PWM2 outputs controlled by PWM
    IOCON2bits.PENL = 1;                    // module
    
    PTCONbits.PTEN = 1;                     // Turn ON PWM module
    //~~~~~~~~~~~~~~~~~~~~~~ End PWM Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    while(1);                               // Infinite loop

}
