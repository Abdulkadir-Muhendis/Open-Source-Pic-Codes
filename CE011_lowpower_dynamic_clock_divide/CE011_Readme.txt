
                              Readme File for Code Example:
              CE011 - Dynamic Clock Division for Low-Power Operation
              --------------------------------------------------------

This file contains the following sections:
1. Code Example Description
2. Folder Contents
3. Suggested Development Resources
4. Reconfiguring the project for a different dsPIC30F device
5. Revision History

1. Description:
---------------
Microchip's dsPIC30F Digital Signal Controllers provide several means to reduce power consumption while the application is running. Power consumption is directly proportional to the operating MIPS. In certain applications, it may be possible to run the device at lower MIPS for a certain tasks and at higher MIPS for certain compute-intensive tasks. In such applications, one of the mechanisms available to the user to dynamically increase or decrease the system clock frequency is to use the programmable system-clock post-scaler. This feature allows the application to divide the system clock by 4, 16 or 64 at run-time by writing to the POST bits in the OSCCON register.

The attached code example demonstrates how the programmable post-scaler may be used to dynamically change the system clock frequency. The workspace contains 2 C files - main.c and clock_divide.c

The code in clock_divide.c contains a C function which has the following prototype:
Function:       int clockDivide(unsigned int)
Input:          int data type equal in value to 1, 4, 16 or 64
Return:         RET_CODE_OSC_SUCCESS for a successful clock divide operation
                RET_CODE_OSC_ERROR for an illegal clock divide request
                (i.e. values other than 1, 4, 16, 64)
Description:    This subroutine unlocks the OSCCONL SFR and then writes the
                correct requested clock divide value into the POST<1:0> bits in
                OSCCONL.
The code in the main.c file simply calls the function above and requests to divide the system clock down by 64.

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
