/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        math_error_trap_30F_GP_MC_Sensor.c
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
* This routine applies for all dsPIC30F Motor Control, General Purpose
* and Sensor family devices.
* NOTE: Disable compiler optimizations for this file
**********************************************************************/

#include "p30fxxxx.h"
void __attribute__((__interrupt__)) _MathError(void);

unsigned char   accAOvfl = 0;
unsigned char   accBOvfl = 0;
unsigned char   divByZero = 0;
unsigned int    MathErrInstructionAddr[2];

//_MathErr() is the Arithmetic Error Trap handler.
//The routine must have global scope in order to be an ISR.
//The trap handler name is chosen from the device linker script.
//The code execution reaches here based on Accumulator overflow errors
//or divide by zero errors
void __attribute__((__interrupt__)) _MathError(void)
{
        if (SRbits.OA && (INTCON1bits.OVATE || INTCON1bits.COVTE) )
        {
                ACCA.L = 0;
                ACCA.H = 0;     /* Before clearing the MATHERR flag, */
                ACCA.U = 0;     /* we should clear the condition causing the trap */
                SRbits.OA = 0;  /* This is true of Math errors caused by Accumulator */
                SRbits.OAB = 0; /* overflows only */
                accAOvfl = 0xFF;
        }
        else if (SRbits.OB && (INTCON1bits.OVBTE || INTCON1bits.COVTE) )
        {
                ACCB.L = 0;
                ACCB.H = 0;
                ACCB.U = 0;
                SRbits.OB = 0;
                SRbits.OAB = 0;
                accBOvfl = 0xFF;
        }
        else
        {
                divByZero = 0xFF;
        }
        INTCON1bits.MATHERR = 0;
        asm volatile (" push.d   w0 \n"
                        "push     w2 \n"
                        "mov    w15, w0 \n"
                        "sub    w0, #(6+4), w0 \n"           /*NOTE: Subtracting 6 to estimate stack pointer*/
                                                             /*location prior to 2 push ops*/
                                                             /*Subtracting an additional 4 to compensate for compiler*/
                                                             /*pushing 2 words at the beginning of the trap handler*/
                        "mov     #_MathErrInstructionAddr+2, w1 \n"
                        "mov     [--w0], [w1--] \n"          /*Pop the Program Counter (PC) from the stack */
                        "mov     [--w0], [w1++] \n"          /*Remember that the PC(PCH and PCL) is stacked  */
                        "bclr    [w1], #7 \n"                /*along with the SRL byte and IPL3 bit from */
                        "inc     w1, w1 \n"                  /*CORCON. So we need to extract just the 24-bit */
                        "clr.b   [w1] \n"                    /*PCH:PCL information from the stack */
                                                               /*Store the 24-bit result into 2x16-bit words */
                                                             /*in RAM at- MathErrInstructionAddrHigh:Low */
                        "mov     #_MathErrInstructionAddr, w1 \n"  /*Decrement that value by 2 if Accumulator based trap occurred*/
                        "clr     w2 \n"
                        "cp0     _divByZero \n"
                        "btsc    _SR, #1 \n"
                        "mov     #2, w2 \n"                  /*Store the 24-bit result into 2x16-bit words*/
                        "subr    w2, [w1], [w1++] \n"        /*in RAM at- AddrErrInstructionAddrHigh:Low*/
                        "clr     w2 \n"
                        "subbr   w2, [w1], [w1] \n"
                        "pop     w2 \n"
                        "pop.d   w0 ");
}

/*
EOF
*/


