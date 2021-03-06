
                              Readme File for Code Example:
                        CE014 - Fast wake-up from SLEEP mode
                        ------------------------------------

This file contains the following sections:
1. Code Example Description
2. Folder Contents
3. Suggested Development Resources
4. Reconfiguring the project for a different dsPIC30F device
5. Revision History


1. Code Example Description:
----------------------------
Microchip's 16-bit dsPIC� Digital Signal Controllers are capable of resuming regular operation after waking up from a low-power mode, for example, SLEEP mode, within 10 microseconds. Additionally, within 30 microseconds of waking up from SLEEP mode, the device can operate at its highest speed of operation.

To wake up from SLEEP in 10 microseconds or less, the device should be made to operate off the Fast RC (FRC) Oscillator prior to entering SLEEP mode. To wake up from SLEEP and operate at maximum speed in 30 microseconds or lesser, the device should be made to operate off the Fast RC (FRC) Oscillator with the PLL enabled, prior to entering SLEEP mode. This is possible because the PLL locks in 20 microseconds and the FRC oscillator, unlike a crystal oscillator has no start-up time. The POR circuit in the device inserts a small delay of 10 microseconds to ensure all bias circuits have stabilized on a power-up event.

The attached code example demonstrates this capability using external interrupt pin, INT1. Using this example, the user can measure the time elapsed between a falling edge on the INT1 pin and a rising edge on any pin on Port D. The time measured will be the time to wake up from SLEEP using an FRC oscillator plus the time taken by the PLL to lock plus the 5*Tcy consistent interrupt service routine entry time.

Some dsPIC30F devices allow the FRC oscillator to be provided as an input to the PLL module. The attached code example will configure the FOSC oscillator configuration register to use the FRCxPLL16 mode for these devices via config macros in the source file. For devices that do not feature the FRCxPLL option, the FOSC configuration register will be set up to use the FRC oscillator on power-up.

The benefit offered by dsPIC30F devices to low-power applications is not only a low-power SLEEP mode option but also the option to wake-up from SLEEP in a short amount of time and execute code at the highest speed possible.

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
