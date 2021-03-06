
                              Readme File for Code Example:
                        CE006 - Address Error Traps for Easy Debugging
                        ----------------------------------------------

This file contains the following sections:
1. Code Example Description
2. Folder Contents
3. Suggested Development Resources
4. Reconfiguring the project for a different dsPIC30F device
5. Revision History


1. Code Example Description:
----------------------------
Microchip's 16-bit dsPIC� Digital Signal Controllers feature an on-chip mechanism to detect software errors and take corrective action. Specifically, the ability to detect memory addressing errors is provided by means of automatic Address Error Trap detection. Memory addressing errors may be caused by one of the following:

a. A misaligned data word fetch is attempted. This condition occurs when an instruction performs a word access with the LSb of the effective address set to �1�. The dsPIC30F CPU requires all word accesses to be aligned to an even address boundary.

b. A bit manipulation instruction using the Indirect Addressing mode with the LSb of the effective address set to �1�.

c. A data fetch from unimplemented data address space is attempted.

d. Execution of a �BRA #literal� instruction or a �GOTO #literal� instruction, where literal is an unimplemented program memory address.

e. Executing instructions after modifying the PC to point to unimplemented program memory addresses. The PC may be modified by loading a value into the stack and executing a RETURN instruction.

If the application defines an Address Error Trap service routine (trap handler), the processor will vector to the trap handler when it detects an Address Error trap.

The attached code example contains two assembler files. The code example in the "address_error_trap.s" file demonstrates a simple means by which the user may detect the location of the instruction that causes an address error trap to occur.  You may add this file to your project to ease debugging during development of your application. The code in the "main.s" file simply performs an illegal MOV instruction so as to cause an Address Error Trap.

Note:
The user should note that the MPLAB� C30 C compiler will not intentionally generate any instructions that cause an address error trap to occur.
The compiler/assembler will also detect address error instances in code whenever possible.

2. Folder Contents:
-------------------
This folder contains the following sub-folders:
a. gld
        This folder contains a linker script file for the example project.
        This file is used for building the project for a 30F6014A device.
        This file simply includes the relevant device linker script, 
        "p30F6014A.gld" and the relevant MPLAB� C30 library files, 
        "libdsp-coff.a", "libc-coff.a", and "libm-coff.a" or 
        "libdsp-elf.a", "libc-elf.a", and "libm-elf.a" from their installed 
        location. 

b. h
        This folder contains C header files useful in building this
        project. Device register and bit definitions are provided in
        the "p30F6014A.h" file, which may be found in the installation folder
        of the MPLAB� C30 toolsuite.

c. hex
        This folder contains three file types - coff, hex and map.
        These are files generated by the MPLAB� C30 toolsuite on build
        operation performed within MPLAB� IDE. The *.map file contains
        details on memory allocation for various variables, constants
        and dsPIC30F instructions specified in the source and library
        code. The *.hex file contains a binary file that may be
        programmed into the dsPIC30F device. The *.coff file contains
        a binary file that is used by MPLAB� IDE for simulation.

d. src
        This folder contains all the C and Assembler source files (*.c,
        *.s) used in demonstrating the described example. This folder
        also contains a sub-folder named "obj" that stores compiled
        object files generated when the project is built.

3. Suggested Development Resources:
-----------------------------------
        a. dsPICDEM� 1.1 Development Board (See below)
        b. dsPIC30F6014A Digital Signal Controller Plug-In Module (See below)

4. Reconfiguring the project for a different dsPIC30F device:
-------------------------------------------------------------
The Project/Workspace can be easily reconfigured for any dsPIC30F device.
Please use the following general guidelines:
        a. Change device selection within MPLAB� IDE to a dsPIC30F device of
        your choice by using the following menu option:
        MPLAB IDE>>Configure>>Select Device

        b. Provide the correct device linker script and header file for your
        device. Device linker scripts and header files are available in your
        MPLAB� C30 installation folder under:
        Device Linker Script-
                YourDrive:>Program Files\Microchip\MPLAB C30\support\gld
        Device C Header file-
                YourDrive:>Program Files\Microchip\MPLAB C30\support\h
        Device ASM Include file-
                YourDrive:>Program Files\Microchip\MPLAB C30\support\inc

        c. Provide the appropriate path to your MPLAB C30 support file locations
        using the menu option:
        MPLAB IDE>>Project>>Build Options>>Project

        d. Chose the development board applicable to your device. Some options
        are provided below:
        - dsPICDEM� 2 Development Board supports:
          30F2010, 30F2011, 30F2012, 30F3010, 30F3011, 30F3012, 30F3013,
          30F3014, 30F4011, 30F4012, 30F4013

        - dsPICDEM� 1.1 Development Board supports:
          30F5013, 30F6010, 30F6011, 30F6012, 30F6013, 30F6014,
          30F6011A, 30F6012A, 30F6013A, 30F6014A

        - dsPICDEM� MC1 Development Board supports:
          30F6010, 30F6010A, 30F5016

        e. Re-build the MPLAB� project using the menu option:
        MPLAB IDE>>Project>>Build All

        f. Download the hex file into the device and run.

5. Revision History :
---------------------
        09/30/2005 - Initial Release of the Code Example
