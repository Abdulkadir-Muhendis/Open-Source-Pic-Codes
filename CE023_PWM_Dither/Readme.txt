                     Readme File for Code Example:
               CE023 - PWM Frequency Dither using dsPIC SMPS DSC
               -------------------------------------------------

This program illustrates the use of the Dithering mode of the SMPS dsPIC
devices. It uses a sequential tuning of the FRC oscillator to produce a 
+/- 3% dither in the frequency.

The dithering mode is useful in reducing the effective EMI produced by 
high frequency switching of semiconductor switches used in switched mode
power supply applications.

In this program, PWM1 and PWM2 are configured in the complementary mode
and produce constant duty cycles. The dither mode will cause the PWM
signals to jitter about the factory calibrated frequency.

All timings are calculated assuming 30 MIPS operation.

This file provides a brief description of files and folders provided
in the accompanying workspace.

This folder contains the following files:
1. This file
        This file provides a description of the functionality demonstr-
        ated by the example source code.

2. PWM Dither.mcw, PWM Dither.mcp
        These are MPLAB® IDE workspace and project files that may be
        used to examine, build, program and debug the example source
        code.

This folder contains the following sub-folders:

1. src
        This folder contains all the C and Assembler source files (*.c,
        *.s) used in demonstrating the described example.

