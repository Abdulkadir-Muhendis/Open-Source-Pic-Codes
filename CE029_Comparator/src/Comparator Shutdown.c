/***********************************************************************
; * © 2006 Microchip Technology Inc.
; *
; * FileName:        Comparator Shutdown.c
; * Dependencies:    Header (.inc) files if applicable, see below
; * Processor:       dsPIC30F2020
; * Compiler:        MPLAB® C30 v3.00 or higher
; * IDE:             MPLAB® IDE v7.52 or later
; * Demo Board:      dsPICDEM SMPS Buck Development Board
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
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; * Author            Date      Comments on this revision
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; * Sagar Khare       09/26/06  First release of source file
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; *
; * Description:
; *   In this code example, the on-chip analog comparators are used as fault
; * inputs to the PWM generators. When the voltage at the analog comparator
; * pin goes above the programmed reference, a PWM fault condition occurs, 
; * and the PWM output is overriden by the value in the FLTDAT bits. The
; * fault condition is reset every PWM cycle. It can also be configured to
; * latch up in the event of a fault.
; *   Assuming AVdd = 5V, PWM1 goes into Fault state when voltage at AN5
; * drops below 1.25V.
; *   PWM2 enters Fault state when AN6 drops below 2.5V.
; * All timing parameters are approximate and assuming 30MIPS operation.
; *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#include "p30f2020.h"

/* Configuration Bit Settings */
_FOSCSEL(FRC_PLL)
_FOSC(CSW_FSCM_OFF & FRC_HI_RANGE & OSC2_CLKO)
_FPOR(PWRT_128)
_FGS(CODE_PROT_OFF)
_FBS(BSS_NO_FLASH)

void init_PWM();
void init_CMP();

int main()
{

    init_PWM();                         /* Initialize PWM module */
    init_CMP();                         /* Initialize CMP module */
            
    while(1);                           /* Infinite loop */

}


void init_PWM()
{
    /* ~~~~~~~~~~~~~~~~~~~~~~~~ PWM1 Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    PDC1 = 4761;                        /* PWM1 pulse width of 5 usec */
                                        /* Duty Cycle = PDC1*1.05nsec */
    
    IOCON1bits.PENH = 1;                /* PWM1 outputs controlled by PWM */
    IOCON1bits.PENL = 1;                /* module */

    IOCON1bits.PMOD = 2;                /* Choose Independent PWM mode */
    IOCON1bits.FLTDAT = 0;              /* Turn OFF both PWM1 outputs
                                           in case of a fault condition */

    PWMCON1bits.DTC = 2;                /* Dead time function disabled */

    FCLCON1bits.FLTSRC = 1;             /* Comparator #2 is Fault source */
    FCLCON1bits.FLTPOL = 1;             /* Fault source is active high */
    FCLCON1bits.FLTMOD = 1;             /* FLTDAT from IOCONx register
                                           provides data to PWM output
                                           when in fault state, and the
                                           fault state is reset every 
                                           PWM cycle */
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~ PWM2 Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~ */    

    PDC2 = 2380;                        /* PWM2 pulse width of 2.5 usec */
                                        /* Duty Cycle = PDC2*1.05nsec */    
                                        
    IOCON2bits.PENH = 1;                /* PWM2 outputs controlled by PWM */
    IOCON2bits.PENL = 1;                /* module */
    IOCON2bits.PMOD = 2;                /* Choose Independent PWM mode */
    IOCON2bits.FLTDAT = 0;              /* Turn OFF both PWM1 outputs
                                           in case of a fault condition */
                                            
    PWMCON2bits.DTC = 2;                /* Dead time function disabled */

    FCLCON2bits.FLTSRC = 2;             /* Comparator #3 is Fault source */
    FCLCON2bits.FLTPOL = 1;             /* Fault source is active high */
    FCLCON2bits.FLTMOD = 1;             /* FLTDAT from IOCONx register
                                           provides data to PWM output
                                           when in fault state */
                                            
    /* ~~~~~~~~~~~~~~~~~~~~~~~ Common PWM Settings ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    
    PTPER = 9520;                       /* PWM period of 10 usec */
                                        /* Period = PTPER*1.05nsec = 9.99us */
    PTCONbits.PTEN = 1;                 /* Turn ON PWM module */
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
}

void init_CMP()
{
    /* ~~~~~~~~~~~~~~~~~~~~~~~~ CMP2 Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    CMPCON2bits.INSEL = 3;               /* Select CMP2D input */
    CMPCON2bits.EXTREF = 0;              /* Choose internal reference */
    CMPCON2bits.RANGE = 1;               /* Max DAC voltage = AVdd/2 */
    
    CMPDAC2 = 0x01FF;                    /* Choose comparator reference
                                            voltage = AVdd/4 */
    CMPCON2bits.CMPON = 1;               /* CMP2 enabled */
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~ CMP3 Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    CMPCON3bits.INSEL = 2;               /* Select CMP3C input */
    CMPCON3bits.EXTREF = 0;              /* Choose internal reference */
    CMPCON3bits.RANGE = 1;               /* Max DAC voltage = AVdd/2 */
    
    CMPDAC3 = 0x03FF;                    /* Choose comparator reference
                                            voltage = AVdd/2 */
    CMPCON3bits.CMPON = 1;               /* CMP3 enabled */
        
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
}

