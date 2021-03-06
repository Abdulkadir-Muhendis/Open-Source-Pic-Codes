
                              Readme File for Code Example:
            CE010 - Performing A/D conversions in SLEEP (low-power) mode
            -------------------------------------------------------------

This file contains the following sections:
1. Code Example Description
2. Folder Contents
3. Suggested Development Resources
4. Reconfiguring the project for a different dsPIC30F device
5. Revision History

1. Description:
---------------
Microchip's 16-bit dsPIC Digital Signal Controllers feature one or more on-chip A/D converters. These 10 or 12-bit A/D converter modules are capable of performing Analog to Digital conversions even when the device has been placed in a low-power mode of operation, for example SLEEP or IDLE mode.

When a device is placed in SLEEP mode, the CPU turns off the system clock thereby ensuring the device consumes the lowest power. The absence of the system clock signal minimizes digital noise. Applications may therefore find it beneficial to perform A/D conversions when the device is placed in SLEEP mode. To allow the A/D converter to operate when the device is in SLEEP mode, the A/D converter on dsPIC DSC devices feature an internal RC oscillator that can provide clock signals to the A/D converter module alone. This RC oscillator is enabled by setting the ADRC bit in the ADCON3 control register. When the A/D converter uses the ADRC oscillator for a clock source, the conversion rate is not user-configurable. Refer to the device datasheets for the conversion rate of the ADRC oscillator.

Note: The ADRC oscillator is a different oscillator than the on-chip 7.37 MHz Fast RC oscillator and the 512 KHz Low-power RC oscillator.

The Code Example attached here demonstrates how the user may enable the ADRC oscillator and perform A/D conversions in SLEEP mode. An A/D interrupt will wake the processor up from SLEEP mode. Upon waking up, the processor will vector to the A/D interrupt service routine (ISR) if one has been defined and enabled. If an A/D ISR has not been enabled, the processor will execute the instruction immediately following the PWRSAV instruction that placed the device in SLEEP mode.

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
