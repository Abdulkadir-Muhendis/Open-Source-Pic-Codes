
				Readme File for Code Example:
              CE400 - ADC Sampling and IIR Filtering 
             ----------------------------------------

This file contains the following sections:
1. Code Example Description
2. Folder Contents
3. Suggested Development Resources
4. Reconfiguring the project for a different dsPIC33E device
5. Revision History


1. Code Example Description:
----------------------------
In this example, ADC is configured to sample (AIN5) at 8Khz rate and converted data is assembled as 256 sample buffer before triggering filtering operation.

Timer 3 is setup to time-out every 125 microseconds (8Khz Rate). 
As a result, the module will stop sampling and trigger a 12-bit A/D conversion on every Timer3 time-out, i.e., Ts=125us. 
At that time, the conversion process starts and completes Tc=14*Tad periods later.
When the conversion completes, the module starts sampling again. However, since Timer3 
is already on and counting, about (Ts-Tc)us later, Timer3 will expire again and trigger 
next conversion. 

ADC module clock time period is configured as Tad=Tcy*(ADCS+1)= (1/40M)*64 = 1.6us (625Khz). 
Hence the conversion time for 12-bit A/D Conversion Time Tc=14*Tad = 22.4us

void initTmr3();
Timer 3 is configured to time-out at 8Khz rate. 

void initAdc1(void);
ADC module is set-up to convert AIN5 input using CH0 S/H on Timer 3 event in 12-bit mode.

void initDma0(void);
DMA channel 0 is configured in ping-pong mode to move the converted data from ADC to DMA RAM on every sample/convert sequence. 
It generates interrupt after every 256 sample transfer. 

void __attribute__((__interrupt__)) _DMA0Interrupt(void);
DMA interrupt service routine performs IIR filtering on the data buffer.


2. Folder Contents:
-------------------
a. firmware
        This folder contains all the C, Assembler source files and include files(*.c,
        *.s, *.h) and project specific files used in demonstrating the described example. 
b. system_config
		This folder contains the chip-set specific configuration code. More specifically it in-turn contains a folder called exp16/ 
		which holds configuration files.
c. exp16/
		This folder contains various folders like dspic33ep512gm710/dspic33ep512mu810/dspic33ep256gp506 depending on the platform.Each platform folder contain,configuration 
		specific source files.

 
3. Suggested Development Resources:
-----------------------------------
        a. Explorer 16 Demo board with dspic33ep512gm710/dspic33ep512mu810/dspic33ep256gp506 controller

4. Reconfiguring the project for a different dsPIC33E device:
-------------------------------------------------------------
The Project/Workspace can be easily reconfigured for dspic33ep512gm710/dspic33ep512mu810/dspic33ep256gp506 device.
Please use the following general guidelines:
        a. Change device selection within MPLAB� IDE to dspic33ep512gm710/dspic33ep512mu810/dspic33ep256gp506 device of
        your choice by using the following menu option:
        MPLAB X>>Configuration drop-down option>><Listed Device Configuration>

        b. Re-build the MPLAB� project using the menu option:
        MPLAB X>>Build Main Project

        c. Download the hex file into the device and run.

       

5. Revision History :
---------------------
        04/01/2006 - Initial Release of the Code Example
		07/01/2010 - Code Example updated for dsPIC33E
		1/22/2014  - Code Example updated for dspic33ep512gm710/dspic33ep512mu810/dspic33ep256gp506
		01/08/2015 - TEST_MODE code added for test automation
