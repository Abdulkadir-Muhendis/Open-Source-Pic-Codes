                     Readme File for Code Example:
               CE029 - PWM Shutdown using Analog Comparator
               --------------------------------------------

In this code example, the on-chip analog comparators are used as fault
inputs to the PWM generators. When the voltage at the analog comparator
pin goes above the programmed reference, a PWM fault condition occurs, 
and the PWM output is overriden by the value in the FLTDAT bits. The
fault condition is reset every PWM cycle. It can also be configured to
latch up in the event of a fault.
Assuming AVdd = 5V, PWM1 goes into Fault state when voltage at AN5
drops below 1.25V.
PWM2 enters Fault state when AN6 drops below 2.5V.

All timing parameters are approximate and assuming 30MIPS operation.

This file provides a brief description of files and folders provided
in the accompanying workspace.

This folder contains the following files:
1. This file
        This file provides a description of the functionality demonstr-
        ated by the example source code.

2. Comparator Shutdown.mcw, Comparator Shutdown.mcp
        These are MPLAB® IDE workspace and project files that may be
        used to examine, build, program and debug the example source
        code.

This folder contains the following sub-folders:

1. src
        This folder contains all the C and Assembler source files (*.c,
        *.s) used in demonstrating the described example.