/**********************************************************************
* � 2005 Microchip Technology Inc.
*
* FileName:        main.s
* Dependencies:    Header (.h/.inc) files if applicable, see below
* Processor:       dsPIC30Fxxxx
* Compiler:        MPLAB� C30 v3.00 or higher
* IDE:             MPLAB� IDE v7.52 or later
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

.include "p30f6014a.inc"
config __FOSC, CSW_FSCM_OFF & XT_PLL8  ;Set up for crystal multiplied by 8x PLL
config __FWDT, WDT_OFF                 ;Turn off the Watch-Dog Timer.
config __FBORPOR, MCLR_EN & PWRT_OFF   ;Enable MCLR reset pin and turn off the power-up timers.
config __FGS, CODE_PROT_OFF            ;Disable Code Protection

.equ    STACK_OVERFLOW_TEST, 1
.equ    STACK_UNDERFLOW_TEST, 0

.global _main

.section .text
_main:

        mov     #0xFFFF, w0     ;Load a count into w0
.if STACK_OVERFLOW_TEST
L1:     push    w1              ;This instruction will eventually cause
        dec     w0, w0          ;a stack overflow because we are continuously
        bra     nz, L1          ;pushing data into the stack
.endif


        mov     #0xFFFF, w0     ;Load a count into w0
.if STACK_UNDERFLOW_TEST
L2:     pop     w1              ;This instruction will eventually cause
        dec     w0, w0          ;a stack underflow because we are continuously
        bra     nz, L2          ;popping data out of the stack
.endif

done:   bra     done            ;Code execution never reaches here.

/*
EOF
*/


