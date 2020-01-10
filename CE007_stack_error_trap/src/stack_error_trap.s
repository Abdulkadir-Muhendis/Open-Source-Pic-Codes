/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        stack_error_trap.s
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
*
**********************************************************************/

.include "p30f6014a.inc"

.global __StackError
.global _StkOvflErrInstructionAddrLow, _StkOvflErrInstructionAddrHigh



.section .bss
_StkOvflErrInstructionAddrLow: 	.space 2
_StkOvflErrInstructionAddrHigh: .space 2

.section .text

__StackError:
	mov	w15, w0		;Load w0 with the stack pointer value
	mov	SPLIM, w1	;Load w1 with the SPLIM value

StackOverflowCheck:
	cp	w0, w1
	bra	lt, StackUnderflow
	mov	#_StkOvflErrInstructionAddrHigh, w1
	pop	[w1--]		;Pop the PCL and PCH from the stack
	pop	[w1++]		;Decrement that value by 2
	bclr	[w1], #7	;Store the result into RAM at:
	inc	w1, w1		;OffendingInstructionAddrHigh:Low
	clr.b	[w1]		;Halt the Debugging process and view
				;the variables named:
				;OffendingInstructionAddrHigh:Low
	bclr	INTCON1, #STKERR ;Clear the trap flag
StkOverflowErr:			;Stay in this routine
	bra	StkOverflowErr

StackUnderflow:
	bclr	INTCON1, #STKERR ;Clear the trap flag
StkUnderflowErr:		;Stay in this routine
	bra	StkUnderflowErr	;To find the offending instruction that caused
				;the Stack underflow error use MPLAB SIM
	retfie


.end

/*
EOF
*/


