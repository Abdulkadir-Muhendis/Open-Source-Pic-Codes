/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        oscillator_failure_trap.s
* Dependencies:    Header (*.inc/.h) files if applicable, see below
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
* THIS CODE ASSUMES THAT THE FAIL-SAFE CLOCK MONITOR HAS BEEN
* TURNED ON WITHIN FOSC CONFIGURATION REGISTER !!
* P.S. main.c file for config macro examples.
**********************************************************************/

.include "p30fxxxx.inc"

.global __OscillatorFail                ;Provide global scope to the Oscillator
                                        ;Failure Trap Handler. This ensures that
                                        ;the linker will place the address of
                                        ;the routine in the Interrupt Vector
                                        ;Table

.section .ndata, data, near
flagPLLoutOfLock: .hword 0x0000

.section .text                  ;Code section in Program Memory

/*
;On encountering a clock failure, if the fail-safe clock monitor (FSCM)
;is enabled, device executes code using the FRC oscillator and code execution
;reaches the Oscillatore Fail trap
*/
__OscillatorFail:
        push.d  w0                      ;Save w0, w1, w2 and w3 on to stack
        push.d  w2                      ;For fast context saving use "push.s"
                                        ;However, push.s may be used only once
                                        ;in your project

        mov     OSCCON, WREG            ;Read OSCCON in to w0

        btss    w0, #LOCK               ;Test the PLL LOCK bit
        setm    flagPLLoutOfLock        ;If LOCK bit is clear then flag this to the
                                        ;user for diagnostic information

        bclr    w0, #CF                 ;Before clearing the OSCFAIL trap status flag
                                        ;we should clear the Clock Fail(CF) bit in
                                        ;OSCCONL

                                        ;Load w0 with a byte value to write to
                                        ;OSCCONL so that the CF bit is cleared
        mov     #OSCCONL, w1            ;Point w1 to OSCCONL byte
        disi    #4                      ;Disable interrupts for the next
                                        ;5 instruction cycles
        mov     #0x46, w2               ;Move first OSCCONL unlock code byte
                                        ;to w2
        mov     #0x57, w3               ;Move second OSCCONL unlock code byte
                                        ;to w3
        mov.b   w2, [w1]                ;Perform byte-wide move of w2 to OSCCONL
        mov.b   w3, [w1]                ;Perform byte-wide move of w2 to OSCCONL

        mov.b   w0, [w1]                ;Write parameter in w0 (lower byte)to
                                        ;OSCCONL within one instruction cycle
                                        ;of unlocking OSCCONL using MOV instruction

        bclr.b    INTCON1, #OSCFAIL     ;Clear the Oscillator Failure Trap
                                        ;flag bit


        pop.d   w2                      ;Restore w0, w1, w2 and w3 from stack
        pop.d   w0                      ;You may use pop.s for fast context saving
                                        ;However pop.s may only be used once
                                        ;in your project.
        retfie                          ;Return from interrupt



.end



/*
EOF
*/

