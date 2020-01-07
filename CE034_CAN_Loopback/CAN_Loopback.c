/**********************************************************************
* © 2007 Microchip Technology Inc.
*
* FileName:        CAN_Loopback.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC30Fxxxx
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
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            		  Date      	Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*       		     							Initial Release
*
* ADDITIONAL NOTES:  
*
* Demo program showing CAN Module working in LoopBack Mode for dsPIC30F6014A Series
*/

#include <p30F6014A.h>


#define FCY 		30000000             		// 30 MHz
#define BITRATE 	1000000			 			// 1Mbps
#define NTQ 		15							// Number of Tq cycles which will make the 
												//CAN Bit Timing .
#define BRP_VAL		((FCY/(2*NTQ*BITRATE))-1)  //Formulae used for C1CFG1bits.BRP 

//---------------------------------------------------------------------

// Buffer Registers for CAN data to be send out in the transmit mode.

unsigned int OutData0[4] = {0x5251, 0x5453, 0x5655, 0x5857};            
unsigned int OutData1[2] = {0x5A59, 0x5C5B};
unsigned int OutData2[4] = {0x6261, 0x6463, 0x6665, 0x6867};            
unsigned int OutData3[2] = {0x6A69, 0x6C6B};

// Intilializing the receive registers to be 0

unsigned int InData0[4] = {0, 0, 0, 0};
unsigned int InData1[2] = {0, 0};
unsigned int InData2[4] = {0, 0, 0, 0};
unsigned int InData3[2] = {0, 0};

//---------------------------------------------------------------------

int main(void)
{



 TRISD = 0x0000;				// Initialize the PORTD as output
 LATD = 0xFFFF;                 // Initially LEDs of dsPICDEM1.1 Plus GP Board are off 


//--------------------------------------------------------------------------------------------------------------------
					//Initialization of CAN1 Module and Enabling of CAN1 Interrupts
//--------------------------------------------------------------------------------------------------------------------

 
 
 C1CTRLbits.CANCKS = 1;			// Select the CAN Master Clock . It is equal to Fcy here. 
								// equal to Fcy.(Fcy=30Mhz)


 C1CFG1bits.SJW=00;				//Synchronized jump width time is 1 x TQ when SJW is equal to 00

 
 C1CFG1bits.BRP = BRP_VAL;		//((FCY/(2*NTQ*BITRATE))-1) 	

 C1CFG2 = 0x03F5;               // SEG1PH=6Tq, SEG2PH=3Tq, PRSEG=5Tq 
                                // Sample 3 times
                                // Each bit time is 15Tq

///Interrupt Section of CAN Peripheral

 C1INTF = 0;					//Reset all The CAN Interrupts 
 IFS1bits.C1IF = 0;  			//Reset the Interrupt Flag status register
 C1INTE = 0x00FF;               //Enable all CAN interrupt sources
 IEC1bits.C1IE = 1;				//Enable the CAN1 Interrupt 


//-------------------------------------------------------------------------------------------------------------------
					//Initialization of CAN2 Module and Enabling of CAN2 Interrupts
//-------------------------------------------------------------------------------------------------------------------


C2CTRLbits.CANCKS = 1;			// Select the CAN Module Frequency Here CAN Master Clk is 
								// equal to Fcy.(Fcy=30Mhz)

C2CFG1bits.SJW=00;			   	//Synchronized jump width time is 1 x TQ when SJW is equal to 00
 
C2CFG1bits.BRP = BRP_VAL;		//((FCY/(2*NTQ*BITRATE))-1)  

 
C2CFG2 = 0x03F5;                // SEG1PH=6Tq, SEG2PH=3Tq, PRSEG=5Tq
                                // Sample 3 times
                                // Each bit time is 15Tq

//CAN2 Interrupt Section

 C2INTF = 0;					//Reset all The CAN Interrupts 
 IFS2bits.C2IF = 0;  			//Reset the Interrupt Flag status register
 C2INTE = 0x00FF;               //Enable all interrupt sources
 IEC2bits.C2IE = 1;				//Enable the CAN2 Interrupt 


//-----------------------------------------------------------------------------------------------------------------------
						// Configure Receive registers, Filters and Masks
//-----------------------------------------------------------------------------------------------------------------------

 // We are initializing the Receive Buffer 0 and Receive Buffer 1 for CAN1 and CAN2 

 
 C1RX0CON = C1RX1CON = C2RX0CON = C2RX1CON = 0x0000; 	// Receive Buffer1 and 0 Status
 														//and Control Register for CAN1 and CAN2

 
 // Acceptance Mask Register0SID and Register1SID associated with Recieve Buffer0
 // and Receive Buffer1 for CAN1 and CAN2 
 C1RXM0SID  = C1RXM1SID  = C2RXM0SID  = C2RXM1SID  = 0x1FFD; 
 
 // Acceptance Mask Register0EIDH and Register1EIDH associated with Recieve Buffer0
 // and Receive Buffer1 for CAN1 and CAN2
 C1RXM0EIDH = C1RXM1EIDH = C2RXM0EIDH = C2RXM1EIDH = 0x0FFF; 

 // Acceptance Mask Register0EIDL and Register1EIDL associated with Recieve Buffer0 
 //and Receive Buffer1 for CAN1 and CAN2
 C1RXM0EIDL = C1RXM1EIDL = C2RXM0EIDL = C2RXM1EIDL = 0xFC00; 

 
//Initializing of Acceptance Filter n Standard Identifier for CAN1

 C1RXF0SID 	= 0x0AA8;	//CAN1 Receive Acceptance Filter2 SID 		
 C1RXF2SID 	= 0x1555;   //CAN1 Receive Acceptance Filter2 SID
 C1RXF2EIDH = 0x0004;   //CAN1 Receive Acceptace  Filter2 Extended Identifier high byte
 C1RXF2EIDL = 0x8C00;	//CAN1 Receive Acceptance Filter2 Extended identifier low byte

//Initializing of Acceptance Filter n Standard Identifier for CAN2

 C2RXF0SID 	= 0x0AA8;	//CAN2 Receive Acceptance Filter0 SID  
 C2RXF2SID 	= 0x1555;	//CAN2 Receive Acceptance Filter2 SID
 C2RXF2EIDH = 0x0004; 	//CAN2 Receive Acceptace  Filter2 Extended Identifier high byte
 C2RXF2EIDL = 0x8C00;	//CAN2 Receive Acceptance Filter2 Extended identifier low byte
 
 //-----------------------------------------------------------------------------------------------------------------------
						// Configure Transmit Registers Buffer 0 and Transmit Buffer 1
//-----------------------------------------------------------------------------------------------------------------------
  
 C1TX0CON = 0x0003;     // High priority
 C1TX0SID = 0x50A8;     // SID 
 C1TX0EID = 0x0000;     // EID 
 C1TX0DLC = 0x01C0;		//Select the Data word Length for CAN1 Transmit Buffer0 which is 8 byte  
 
 // Data Field 1,Data Field 2, Data Field 3, Data Field 4 // 8 bytes selected by DLC 

 C1TX0B1 = OutData0[0];
 C1TX0B2 = OutData0[1];
 C1TX0B3 = OutData0[2];
 C1TX0B4 = OutData0[3];
 
 C1TX1CON = 0x0002;             // High Intermediate priority
 C1TX1SID = 0xA855;             // SID  
 C1TX1EID = 0x0004;             // EID                   
 C1TX1DLC = 0x8DA0;				//Select the Data word Length for CAN1 Transmit Buffer1 which
								// is 4 byte

 //Data Field 1, Data Field 2 // 4 bytes selected by DLC

 C1TX1B1 = OutData1[0];
 C1TX1B2 = OutData1[1];

 
 C2TX0CON = 0x0003;             // High priority
 C2TX0SID = 0x50A8;             // SID = 01010101010 (0x2AA)
 C2TX0EID = 0x0000;             // EID = 0000000000000000000 (0x00000)
 C2TX0DLC = 0x01C0;				//Select the Data word Length for CAN2 Transmit Buffer0 which is
								// 8 byte

 //Data Field 1,Data Field 2, Data Field 3, Data Field 4 // 8 bytes selected by DLC
 C2TX0B1 = OutData2[0];
 C2TX0B2 = OutData2[1];
 C2TX0B3 = OutData2[2];
 C2TX0B4 = OutData2[3];

  //Configure Transmit registers // Transmit Buffer 0 and Transmit Buffer 1 for CAN2
 
 C2TX1CON = 0x0002;             // High Intermediate priority
 C2TX1SID = 0xA855;             // SID = 10101010101 (0x555) 
 C2TX1EID = 0x0004;             // EID = 1110000000100100011 (0x00123)                  
 C2TX1DLC = 0x8DA0;             //Select the Data word Length for CAN1 Transmit Buffer0 which is 
								//8 byte    

 //Data Field 1, Data Field 2 // 4 bytes selected by DLC
 
 C2TX1B1 = OutData3[0];
 C2TX1B2 = OutData3[1];
  
 //Change to Loopback Operation Mode from Configuration Mode

 C1CTRLbits.REQOP = 2;
 C2CTRLbits.REQOP = 2;
 while(C1CTRLbits.OPMODE != 2);//Wait for CAN1 mode change from Configuration Mode to Loopback mode 
 while(C2CTRLbits.OPMODE != 2);//Wait for CAN2 mode change from Configuration Mode to Loopback mode
 
 //Enable transmission

 C1TX0CONbits.TXREQ = 1;        
 C1TX1CONbits.TXREQ = 1;
 C2TX0CONbits.TXREQ = 1;        
 C2TX1CONbits.TXREQ = 1;

 while(1)
{


  								//ADD YOUR CODE HERE//

  			// THE CODE WILL LOOP HERE AND WHEN AN CAN INTERRUPT COMES IT WILL GO TO INTERRUPTS//

                           
}	                            //end while loop


}								//end main loop 

//--------------------------------------------------------------------------------------------------------------------------
											//Interrupt Section for CAN1
//--------------------------------------------------------------------------------------------------------------------------

void __attribute__((interrupt, no_auto_psv)) _C1Interrupt(void)
{
      
		IFS1bits.C1IF = 0;         //Clear interrupt flag

      if(C1INTFbits.TX0IF)
      {
       
		 C1INTFbits.TX0IF = 0;  //If the Interrupt is due to Transmit0 of CAN1 Clear the Interrupt

      }  
      else if(C1INTFbits.TX1IF)
      {
        
		C1INTFbits.TX1IF = 0;   //If the Interrupt is due to Transmit1 of CAN1 Clear the Interrupt 

      }  

      if(C1INTFbits.RX0IF)
      {      
        
		C1INTFbits.RX0IF = 0; 	//If the Interrupt is due to Receive0 of CAN1 Clear the Interrupt

        InData0[0] = C1RX0B1; 
        InData0[1] = C1RX0B2;  	//Move the recieve data from Buffers to InData
        InData0[2] = C1RX0B3;	
        InData0[3] = C1RX0B4;

        if ((InData0[0]==OutData0[0]) && (InData0[1]==OutData0[1]) && (InData0[2]==OutData0[2]) && (InData0[3]==OutData0[3])) 
       
           	LATDbits.LATD0 = 0;    	// If the data received is same which was transmitted 
                                  	// turn on the LED
      }

      else if(C1INTFbits.RX1IF)
      {      
        
		C1INTFbits.RX1IF = 0;  	//If the Interrupt is due to Receive1 of CAN1 Clear the Interrupt
        InData1[0] = C1RX1B1;   //Move the data received to Indata Registers
        InData1[1] = C1RX1B2;

        if ((InData1[0]==OutData1[0]) && (InData1[1]==OutData1[1])) 
       
           LATDbits.LATD1 =0;    //If the data received is same which was transmitted 
                                 //turn on the LED
      }
}


//--------------------------------------------------------------------------------------------------------------------------
											//Interrupt Section for CAN2
//--------------------------------------------------------------------------------------------------------------------------

void __attribute__((interrupt, no_auto_psv)) _C2Interrupt(void)
{
      IFS2bits.C2IF = 0;         // Clear interrupt flag

      if(C2INTFbits.TX0IF)
      
	  {
        
		C2INTFbits.TX0IF = 0;

      }  

      else if(C2INTFbits.TX1IF)

      {
        
		C2INTFbits.TX1IF = 0;  

      }  

      if(C2INTFbits.RX0IF)
      {      
       
		C2INTFbits.RX0IF = 0;

        InData2[0] = C2RX0B1;
        InData2[1] = C2RX0B2;
        InData2[2] = C2RX0B3;
        InData2[3] = C2RX0B4;

        if ((InData2[0]==OutData2[0]) && (InData2[1]==OutData2[1]) && (InData2[2]==OutData2[2]) && (InData2[3]==OutData2[3]))        
          
			 LATDbits.LATD2 = 0;

      }

      else if(C2INTFbits.RX1IF)

      {      
        
		C2INTFbits.RX1IF = 0;

        InData3[0] = C2RX1B1;
        InData3[1] = C2RX1B2;

        if ((InData3[0]==OutData3[0]) && (InData3[1]==OutData3[1]))
        
           LATDbits.LATD3 = 0;        
      }

}



