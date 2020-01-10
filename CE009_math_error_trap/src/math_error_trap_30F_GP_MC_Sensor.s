/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        math_error_trap_30F_GP_MC_Sensor.s
* Dependencies:    Header (.inc) files if applicable, see below
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
**********************************************************************/

.include "p30fxxxx.inc"

.global __MathError
.global _accAOvfl
.global _accBOvfl
.global _divByZero
.global _MathErrInstructionAddrLow
.global _MathErrInstructionAddrHigh

.section .data
_accAOvfl: .hword 0x0000
_accBOvfl: .hword 0x0000
_divByZero: .hword 0x0000
_MathErrInstructionAddrLow: .hword 0x0000
_MathErrInstructionAddrHigh: .hword 0x0000

.section .text
__MathError:
        push.d  w0                      ;Save context of w0, w1 and w2
        push    w2

        mov     #0xFFFF, w0             ;Load an error flag value into w0

        btss    SR, #OA                 ;Test whether Math Error was caused by AccA Overflow
        bra     testOvflAccB            ;So we'll first check if Accumulator A Overflow Errors were
        btsc    INTCON1, #OVATE         ;enabled by the user to begin with. If neither OVATE
        bra     confirmedOvflAccA       ;nor COVTE is set then the user did not enable
        btss    INTCON1, #COVTE         ;Accumulator A overflow error traps in which case,
        bra     testOvflAccB            ;we'll check Accumulator B
confirmedOvflAccA:                      ;We are here if AccA overflow error traps were enabled
        clr     a                       ;For GP, MC and Sensor family dsPIC30F devices
        bclr    SR, #OA                 ;the condition causing the accumulator overflow error trap
        bclr    SR, #OAB                ;must be cleared prior to clearing the MATHERR flag
        mov     w0, _accAOvfl           ;Set a flag variable for the user
        bra     exit

testOvflAccB:
        btss    SR, #OB                 ;Test whether Math Error was caused by AccB Overflow
        bra     confirmedDivByZero      ;So we'll first check if Accumulator B Overflow Errors were
        btsc    INTCON1, #OVBTE         ;enabled by the user to begin with. If neither OVBTE
        bra     confirmedOvflAccB       ;nor COVTE is set then the user did not enable
        btss    INTCON1, #COVTE         ;Accumulator B overflow error traps in which case,
        bra     confirmedDivByZero      ;we know that the math error was caused by a divide by zero op
confirmedOvflAccB:
        clr     b                       ;We are here if AccB overflow error traps were enabled
        bclr    SR, #OB                 ;For GP, MC and Sensor family dsPIC30F devices
        bclr    SR, #OAB                ;the condition causing the accumulator overflow error trap
        mov     w0, _accBOvfl           ;must be cleared prior to clearing the MATHERR flag
        bra     exit                    ;Set a flag variable for the user

confirmedDivByZero:                     ;Math Error was caused by Divide by Zero error
        mov     w0, _divByZero
exit:
        bclr    INTCON1, #MATHERR       ;Clear the Math Error Trap

        ;Next we will estimate which instruction caused the the Math Error trap to take place
        mov     w15, w0                 ;Copy Stack Pointer (SP) into w0
        sub    w0, #6, w0               ;NOTE: Subtracting 6 from SP to estimate stack pointer
                                        ;location prior to 1 push.d and 1 push operation
        mov     #_MathErrInstructionAddrHigh, w1
        mov     [--w0], [w1--]          ;Pop the Program Counter (PC) from the stack
        mov     [--w0], [w1++]          ;Remember that the PC(PCH and PCL) is stacked
        bclr    [w1], #7                ;along with the SRL byte and IPL3 bit from
        inc     w1, w1                  ;CORCON. So we need to extract just the 24-bit
        clr.b   [w1]                    ;PCH:PCL information from the stack
                                        ;Store the 24-bit result into 2x16-bit words
                                        ;in RAM at- MathErrInstructionAddrHigh:Low
        mov     #_MathErrInstructionAddrLow, w1
        clr     w2                      ;Decrement the address value by 2 if Divide-by-Zero error occurred
        cp0     _divByZero              ;but
        btsc    SR, #Z
        mov     #2, w2                  ;Store the 24-bit result into 2x16-bit words
        subr    w2, [w1], [w1++]        ;in RAM at- AddrErrInstructionAddrHigh:Low
        clr     w2
        subbr   w2, [w1], [w1]
        pop     w2                      ;Restore w0, w1 and w2
        pop.d   w0

        retfie                          ;Return from interrupt


.end



