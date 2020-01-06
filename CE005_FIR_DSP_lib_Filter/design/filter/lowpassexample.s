; ..............................................................................
;    File   lowpassexample.s
; ..............................................................................

		.equ lowpassexampleNumTaps, 75

; ..............................................................................
; Allocate and initialize filter taps

		.section .xdata
		.align 256

lowpassexampleTaps:
.hword 	0xFFFA,	0xFFFB,	0x0000,	0x000B,	0x0017,	0x001E,	0x0017,	0x0000,	0xFFDF
.hword 	0xFFBF,	0xFFB2,	0xFFC7,	0x0000,	0x004F,	0x0095,	0x00AC,	0x007A,	0x0000
.hword 	0xFF61,	0xFEDA,	0xFEB2,	0xFF16,	0x0000,	0x012E,	0x022B,	0x0277,	0x01BD
.hword 	0x0000,	0xFDB7,	0xFBB4,	0xFAF3,	0xFC45,	0x0000,	0x05CF,	0x0CB1,	0x1337
.hword 	0x17E1,	0x1993,	0x17E1,	0x1337,	0x0CB1,	0x05CF,	0x0000,	0xFC45,	0xFAF3
.hword 	0xFBB4,	0xFDB7,	0x0000,	0x01BD,	0x0277,	0x022B,	0x012E,	0x0000,	0xFF16
.hword 	0xFEB2,	0xFEDA,	0xFF61,	0x0000,	0x007A,	0x00AC,	0x0095,	0x004F,	0x0000
.hword 	0xFFC7,	0xFFB2,	0xFFBF,	0xFFDF,	0x0000,	0x0017,	0x001E,	0x0017,	0x000B
.hword 	0x0000,	0xFFFB,	0xFFFA

; ..............................................................................
; Allocate delay line in (uninitialized) Y data space

		.section .ybss,  "b"
		.align 256

lowpassexampleDelay:
		.space lowpassexampleNumTaps*2

; ..............................................................................
; Allocate and intialize filter structure

		.section .data
		.global _lowpassexampleFilter

_lowpassexampleFilter:
.hword lowpassexampleNumTaps
.hword lowpassexampleTaps
.hword lowpassexampleTaps+lowpassexampleNumTaps*2-1
.hword 0xff00
.hword lowpassexampleDelay
.hword lowpassexampleDelay+lowpassexampleNumTaps*2-1
.hword lowpassexampleDelay

; ..............................................................................
; ..............................................................................
; Sample assembly language calling program
;  The following declarations can be cut and pasted as needed into a program
;		.extern	_FIRFilterInit
;		.extern	_BlockFIRFilter
;		.extern	_lowpassexampleFilter
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
;		mov	#_lowpassexampleFilter, W0	; Initalize W0 to filter structure
;		call	_FIRFilterInit	; call this function once
;
; The next 4 instructions are required prior to each subroutine call
; to _BlockFIRFilter
;		mov	#_lowpassexampleFilter, W0	; Initalize W0 to filter structure
;		mov	#input, W1	; Initalize W1 to input buffer 
;		mov	#output, W2	; Initalize W2 to output buffer
;		mov	#20, W3	; Initialize W3 with number of required output samples
;		call	_BlockFIRFilter	; call as many times as needed
