                 Readme File for Code Example:
             CE031 - dsPIC SMPS ADC Triggered by PWM
             ---------------------------------------

The dsPIC SMPS Family of Digital Signal Controllers feature an on-chip 
10-bit 2 MSPS A/D Converter. The module is designed to trigger and convert
Analog Channels in pairs. A trigger source can be chosen from the PWM
outputs, Analog Comparators, timers, external fault pins, PWM fault and
current limit inputs, or through software.

This code demonstrates the use of PWM Trigger for ADC conversion 		
The PWM1 generator will trigger Pair 0 at a time interval from the start
of the PWM period. This value is determined by the TRIG1 register. For 	
further details refer to the PWM section. The value read by AN0 is then	
used to determine the duty cycle.									

In this example, the FRC with Hi-Range is set up to run at un-tuned      	
frequency of 14.55 MHz. This will result in Fcy = 29.1 MHz. The input       
clock to the ADC  clock divider will be Fadc = 232.8 MHz					

Tcy = 34.364 nsec  												
Time required for one conversion  = 721.64 nsec					

This file provides a brief description of files and folders provided
in the accompanying workspace.

This folder contains the following files:
1. This file
        This file provides a description of the functionality demonstr-
        ated by the example source code.

2. ADC Triggered By PWM.mcw, ADC Triggered By PWM.mcp
        These are MPLAB® IDE workspace and project files that may be
        used to examine, build, program and debug the example source
        code.

3. main.c
        This file contains the source code for this code example.
