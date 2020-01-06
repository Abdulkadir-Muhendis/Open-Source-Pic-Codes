; ..............................................................................
;    File   bandpassexample.s
; ..............................................................................

		.equ bandpassexampleNumTaps, 123

; ..............................................................................
; Allocate and initialize filter taps

		.section .xdata
		.align 256

bandpassexampleTaps:
.hword 	0x0006,	0x000A,	0x000C,	0x000C,	0x0008,	0x0002,	0xFFFF,	0xFFFE,	0x0002
.hword 	0x000C,	0x0017,	0x001A,	0x0012,	0xFFFD,	0xFFDE,	0xFFBF,	0xFFAD,	0xFFAE
.hword 	0xFFC3,	0xFFE3,	0xFFFD,	0x0000,	0xFFE6,	0xFFB3,	0xFF7D,	0xFF5E,	0xFF70
.hword 	0xFFB8,	0x0028,	0x009E,	0x00F0,	0x00FE,	0x00C6,	0x0065,	0x0010,	0xFFFF
.hword 	0x004F,	0x00F8,	0x01C2,	0x0257,	0x0268,	0x01D0,	0x00A8,	0xFF4D,	0xFE37
.hword 	0xFDCF,	0xFE3B,	0xFF41,	0x0050,	0x00B3,	0xFFD6,	0xFD90,	0xFA4F,	0xF708
.hword 	0xF4F6,	0xF531,	0xF847,	0xFDF7,	0x0526,	0x0C2F,	0x114E,	0x132D,	0x114E
.hword 	0x0C2F,	0x0526,	0xFDF7,	0xF847,	0xF531,	0xF4F6,	0xF708,	0xFA4F,	0xFD90
.hword 	0xFFD6,	0x00B3,	0x0050,	0xFF41,	0xFE3B,	0xFDCF,	0xFE37,	0xFF4D,	0x00A8
.hword 	0x01D0,	0x0268,	0x0257,	0x01C2,	0x00F8,	0x004F,	0xFFFF,	0x0010,	0x0065
.hword 	0x00C6,	0x00FE,	0x00F0,	0x009E,	0x0028,	0xFFB8,	0xFF70,	0xFF5E,	0xFF7D
.hword 	0xFFB3,	0xFFE6,	0x0000,	0xFFFD,	0xFFE3,	0xFFC3,	0xFFAE,	0xFFAD,	0xFFBF
.hword 	0xFFDE,	0xFFFD,	0x0012,	0x001A,	0x0017,	0x000C,	0x0002,	0xFFFE,	0xFFFF
.hword 	0x0002,	0x0008,	0x000C,	0x000C,	0x000A,	0x0006

; ..............................................................................
; Allocate delay line in (uninitialized) Y data space

		.section .ybss,  "b"
		.align 256

bandpassexampleDelay:
		.space bandpassexampleNumTaps*2

; ..............................................................................
; Allocate and intialize filter structure

		.section .data
		.global _bandpassexampleFilter

_bandpassexampleFilter:
.hword bandpassexampleNumTaps
.hword bandpassexampleTaps
.hword bandpassexampleTaps+bandpassexampleNumTaps*2-1
.hword 0xff00
.hword bandpassexampleDelay
.hword bandpassexampleDelay+bandpassexampleNumTaps*2-1
.hword bandpassexampleDelay

; ..............................................................................
; ..............................................................................
; Sample assembly language calling program
;  The following declarations can be cut and pasted as needed into a program
;		.extern	_FIRFilterInit
;		.extern	_BlockFIRFilter
;		.extern	_bandpassexampleFilter
;
;		.section	.bss
;
;	 The input and output buffers can be made any desired size
;	   the value 40 is just an example - however, one must ensure
;	   that the output buffer is at least as long as the number of samples
;	   to be filtered (parameter 4)
;input:		.space	40
;output:	.space	40
;		.text
;
;
;  This code can be copied and pasted as needed into a program
;
;
; Set up pointers to access input samples, filter taps, delay line and
; output samples.
;		mov	#_bandpassexampleFilter, W0	; Initalize W0 to filter structure
;		call	_FIRFilterInit	; call this function once
;
; The next 4 instructions are required prior to each subroutine call
; to _BlockFIRFilter
;		mov	#_bandpassexampleFilter, W0	; Initalize W0 to filter structure
;		mov	#input, W1	; Initalize W1 to input buffer 
;		mov	#output, W2	; Initalize W2 to output buffer
;		mov	#20, W3	; Initialize W3 with number of required output samples
;		call	_BlockFIRFilter	; call as many times as needed
