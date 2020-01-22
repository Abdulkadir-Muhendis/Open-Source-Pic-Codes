Readme File for Code Example:
CE156 - ECAN DMA Register Indirect Code Example for Extended Messages
---------------------------------------------------------------------

This file contains the following sections:
1. Code Example Description
2. Folder Contents
3. Suggested Development Resources
4. Reconfiguring the project for a different dsPIC33F device
5. Revision History


1. Code Example Description:
----------------------------
This code example demonstrates the use of dsPIC33F ECAN module with DMA in
Regsiter Indirect Mode. The code example is specific to Extended type CAN
Messages. A code example for Standard type CAN messages is available seperately.

The code example runs on a CAN bus with two nodes. The address of the CAN nodes
and the node selection is defined in file ..\h\node.h. Two Explorer 16 Development
boards along with 2 ECAN LIN PICtail Plus boards are used. The ECAN1 peripheral on the
dsPIC33F device is used. For node 1 define NODE1 macro in node.h and for node 2 
define NODE2 macro in node.h

The nodes send messages to each other. The 8 byte message data payload contains 
6 random bytes and 2 CRC bytes. The CRC is evaluated on  the 6 random 
bytes of data. The data payload of the received message is check for integrity 
by comparing the calculated CRC against the recieved CRC. They should match.

Note that the CRC is only used as an example in the application. It is not needed for the
ECAN to work.

The message are transmitted at random intervals to simulate example CAN bus traffic.
The code example uses the LEDs on the Explorer 16 Development Board to indicate 
status.

LED3 - Indicates message tranmitted.
LED4 - Indicates message received.
LED5 - Indicates CAN bus error.
LED9 - Indicates data payload corruption.

Timer 1 is used to switch the LEDs off when there is no activity on the CAN Bus.

To understand how the ECAN module works with DMA Register Indirect mode let's first
consider the case of how the ECAN module works with the DMA Peripheral Indirect mode.
In Peripheral Indirect mode, the ECAN module provides the DMA with a portion of the 
DMA RAM address from where data is read or written to. This allows the ECAN module to address
memory location in terms of buffers while using the  DMA as the transfer mechanism. This
enables the following ECAN features

1. Multiple TX and RX buffers. 
2. FIFO start buffer and length can be configured.
3. Filtered messages can be stored in specific buffers
4. ECAN module can re-transmit messages in case of lost arbitration
5. TX and RX buffers can be interspersed (within the first 8 buffers).
6. Standard and Extended ID message length during transmit are same

All of the above features require the ECAN module to provide the DMA module with a portion 
of the target DMA address.

In using the ECAN with DMA Register Indirect mode, the DMA ignores the address generated
by the ECAN module and only uses the DMAxSTA register for addressing. This will affect all
the features mentioned above. 

1. For sake of application error handling simplicity, one TX buffer should be implemented.
2. RX buffers are not limited to 32.
3. ECAN module looses capability to address TX and RX buffer. Hence the received messages
are stored in consecutive memory locations irrespective of the CxBUFPNT settings.
4. Transmit buffer and Receive buffers still need to be defined in CxTRmnCON registers. The
CxBUFPNTx bits should still point to a receieve buffer.
5. Filters and masks work normally.
6. The output of each filter will not be stored in the receive buffer pointed by the 
CxBUFPNTx bits. Rather they will be stored in sequential order starting from the location
specfied by the receive DMA channel register.
7. In case of arbitration loss, the application must rewind the DMA pointer to the start
of the TX buffer manually. This can be done by disabling and enabling the channel.
8. The DMA channel count for transmit must equal the actual number of words to be transmitted.
9. The DMA channel count for receive must be equal to 8 times number of receive buffers.
10. The application must keep track of where the messages are stored. This can be implemented
simply by using a receive buffer tracking index which is incremented when a CAN message is 
received.

2. Folder Contents:
-------------------
This folder contains the following sub-folders:
a. .\src
      Contains all the C source code files

b. .\h
      Contains all the C header files


3. Suggested Development Resources:
-----------------------------------
        a. 2 x Explorer 16 Demo board with dsPIC33FJ128MC710 controller
        b. 2 x ECAN LIN Pictail Plus Board

4. Reconfiguring the project for a different dsPIC33F device:
-------------------------------------------------------------

To use another dsPIC33F device

1. Ensure that the selected dsPIC33F device has a ECAN module
2. Open the MPLAB project and change the device thorugh Configure->Select Device.
3. Make changes to the Explorer16.c and Explorer16.h file. Comment out code that
accesses un-implemented port pins.


5. Revision History :
---------------------
        12/09/2008 - Initial Release of the Code Example

