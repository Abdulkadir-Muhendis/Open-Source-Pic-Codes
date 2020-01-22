/**********************************************************************
* © 2008 Microchip Technology Inc.
*
* FileName:        main.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC33Fxxxx
* Compiler:        MPLAB® C30 v3.00 or higher
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify, test, 
* certify, or support the code.
************************************************************************/

/* This code example will run on the Explorer 16
 * board with ECAN LIN PICtail Plus board. The 
 * 8MHz crystal on the board is used as clock
 * source.*/
 
/* The code example uses LEDs to indicate status
 * LED3 - Message Transmitted
 * LED4 - Message Received
 * LED5 - CAN BUS Error
 * LED9 - Data Payload CRC check error */
 
/* stdlib.h is included for the rand()
 * and srand() function call */

#include <p33Fxxxx.h>
#include "..\h\ECAN1Drv.h"
#include "..\h\crc16.h"
#include "..\h\Explorer16.h"
#include "..\h\node.h"
#include <stdlib.h> 

_FGS(GWRP_OFF & GCP_OFF);
_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF);

/* Define the number of ECAN RX buffers.
 * Only one TX buffer is used. This 
 * is explained in the readme file along with
 * this code example. */
 
#define NUM_OF_RX_BUFFERS 8

/* Create the message arrays. Note the size
 * of the TX Message. It is 7 and not 8 */
 
int ecanTxMsgBuffer[7] __attribute__((space(dma)));
int ecanRxMsgBuffer[NUM_OF_RX_BUFFERS][8] __attribute__((space(dma)));

/* The received flag is checked in the main loop 
 * to compute CRC on the received message
 * and flags errors. The transmitNext flag 
 * transmits the next packet. The sentPacket 
 * variable tracks the number of packets
 * sent.*/
 
volatile int received = 0;
volatile int transmitNext = 1;
int sentPacket = 0;

/* In Register Indirect mode, the ECAN/DMA
 * cannot differentiate between buffers. The
 * application must keep track of where the
 * received message was stored */
 
volatile int rxBufferIndex = -1;
int rxIndex;
int txBufferIndex = 0;


void RandomWait(void)
{
	/* This function will wait for a randon period
	 * of time before exiting. The rand() and srand() functions
	 * used for generating the random numbers */
	
	unsigned long wait;
	wait = rand();
	srand(wait);
	while(wait > 0)
	{
		wait--;
	}	
	
	
}

int main(void)
{
	/* Configure Oscillator to operate the device at 40MHz.
	 * Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
	 * Fosc= 8M*40/(2*2)=80Mhz for 8MHz input clock */
	
	int data[4];
	int crcval;

	 
	PLLFBD=38;					/* M= 40	*/
	CLKDIVbits.PLLPOST=0;		/* N1=2	*/
	CLKDIVbits.PLLPRE=0;		/* N2=2	*/
	OSCTUN=0;			

	/* Initiate Clock Switch to Primary Oscillator 
	 * with PLL (NOSC=0b011)*/
	/* Wait for Clock switch to occur	*/
	
	__builtin_write_OSCCONH(0x03);		
	__builtin_write_OSCCONL(0x01);
	while (OSCCONbits.COSC != 0b011);	
	while(!OSCCONbits.LOCK);
	
	/* Configure the ECAN */
	Explorer16Init();
	ECAN1DMAConfig(__builtin_dmaoffset(ecanTxMsgBuffer),
					__builtin_dmaoffset(ecanRxMsgBuffer), 
					NUM_OF_RX_BUFFERS);
	ECAN1ClockConfig();
	ECAN1InterruptConfig();
	ECAN1RxFiltersConfig();
	ECAN1TxRxBuffersConfig();
	ECAN1SetOPMode();

	/* Sow the seed for the random number generator.*/

	srand(RANDOM_SEED);
	
	
	/* The timer is only used to turn the LEDs off.
	 * It is not needed for the operation of ECAN */
	 
	T1CON = 0x0;
	PR1 = 0xFF00;
	_T1IF = 0;
	_T1IE = 1;
	T1CONbits.TON = 1;

	while(1)
	{
		
		if(transmitNext == 1)
		{
			/* Send a new packet. Create the packet using
			 * data structure and the SID and EID.*/ 
			
			data[0] = rand();
			data[1] = rand();
			data[2] = rand();
			data[3] = crc16((unsigned char *)data, 6,0);
			ECANCreateEIDPacket(data,TXSID1,TXEID1,ecanTxMsgBuffer);
			transmitNext = 0;
		}	

		/* Wait for a random period of time 
		 * and then send the message. This code example
		 * does not check if the message was aborted
		 * but that could be checked here. Note that if
		 * if the message was aborted the TBIF flag will not
		 * be set and you will not get the associated event
		 * interrupt. */
					
		RandomWait();
		ECAN1SendPacket();
				
		if(received == 1)
		{
			/* Check integrity of received packet. The 
			 * rxBufferIndex keeps track of where the latest 
			 * message is stored. 
			 
			 * The CRC is calculated for the payload section
			 * of the received message and compared against
			 * the CRC stored in the message. The payload starts
			 * from the third word of message. If there is an
			 * errror then LED9 on the board will glow.
			 
			 * You can always check the 8th word of the message
			 * to see which filter let it through.*/
		
			received = 0;
			rxIndex = rxBufferIndex;
			crcval= crc16((unsigned char *)&(ecanRxMsgBuffer[rxIndex][3]),6,0);
			if(crcval != ecanRxMsgBuffer[rxIndex][6])
			{
				/* If the CRC is invalid then stop the ECAN module,
				 * switch on LED10 and wait */
				LED9 = EXPLORER16_LED_ON;
				C1CTRL1bits.REQOP = 1;
				while(1);
			}
		
		}

	}			

}

void __attribute__((__interrupt__,no_auto_psv)) _C1Interrupt(void)
{
	/* Only the Transmit Message, Receive 
	 * Message Events and Error flags are processed. You can
	 * check for the other events as well.*/
	
	_C1IF = 0;
	
	if(C1INTFbits.TBIF == 1)
	{
		/* Transmit done. Set the flag so that
		 * the main application loop knows that
		 * the message was transmitted */

		C1INTFbits.TBIF = 0;
		transmitNext = 1;
		LED3 = EXPLORER16_LED_ON;
		T1CONbits.TON = 1;
			
	}
	
	if(C1INTFbits.RBIF == 1)
	{
		/* Received a packet. Check if the
		 * rxBufferIndex is at the boundary
		 * and reset to initial condition
		 * if needed. 
		 
		 * You can check the RXFUL flags
		  if needed. */
		
		if(rxBufferIndex == (NUM_OF_RX_BUFFERS - 1))
			rxBufferIndex = -1;	
		
		C1INTFbits.RBIF = 0;
		C1RXFUL1 = 0;
		received = 1;
		rxBufferIndex ++;
		LED4 = EXPLORER16_LED_ON;
		T1CONbits.TON = 1;	
		
	}
		
	LED5 = EXPLORER16_LED_OFF;
	if(C1INTFbits.ERRIF == 1)
	{
	
		C1INTFbits.ERRIF = 0;
		LED5 = EXPLORER16_LED_ON;
	}
}	

void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{
	/* This is a simple ISR which switches the 
	 * LEDs off and stops the timer */
	
	_T1IF = 0;
	LED4 = EXPLORER16_LED_OFF;
	LED3 = EXPLORER16_LED_OFF;
	T1CONbits.TON = 0;
}	
