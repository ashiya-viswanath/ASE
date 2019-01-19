#include "init.h"
typedef struct{
    int standardId;
    unsigned double data; //4 bytes of data is supported 
    int dataLength;
}msgPacket;

/********************************************************************
*                          global variables                         *
********************************************************************/

/********************************************************************
*                    _____  ___  ___   ___                          *
*                   |_   _|/ _ \|   \ / _ \                         *
*                     | | | (_) | |) | (_) |                        *
*                     |_|  \___/|___/ \___/                         *
*                                                                   *
* If you need global variables define them here!                    *
********************************************************************/  
unsigned char isErrorDoor=1;//initially ECU3_Door is not found
unsigned char Alive=1;
unsigned char interruptCounter=0;


msgPacket NDWSpeedPacket;
msgPacket displayPacket;
msgPacket lightPacket;
msgPacket indicatorPacket;
msgPacket headlightPacket;
msgPacket alivePacket;
msgPacket errorPacket;

#define NDWSPEEDBUF 0
#define DISPLAYBUF 1
#define ALIVEBUF 4
#define ERRORBUF 5

#define LIGHTVALUEID 0x101
#define INDICATORID 0x402
#define HEADLIGHTID 0x503
#define LIGHT_THRESH 512
#define ECU3_ALIVE 0x402


/********************************************************************
 *                              main                                *
 ********************************************************************/
void main(void)
{
    /* board initialization */
    Init();
    PIT_ConfigureTimer(0,100);
    PIT_StartTimer(0);


    NDWSpeedPacket.standardId=0x302; 
    NDWSpeedPacket.dataLength=2;

    displayPacket.standardId=0x301; 
    displayPacket.dataLength=1;

    alivePacket.standardId=0x303; 
    alivePacket.dataLength=0;
    alivePacket.data=0;
    
    errorPacket.standardId=0x304; 
    errorPacket.dataLength=0;
    errorPacket.data=0;


    /* turn off leds */
    LED0 = 1;
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    LED5 = 1;
    LED6 = 1;
    LED7 = 1; 

    /********************************************************************
    *                    _____  ___  ___   ___                          *
    *                   |_   _|/ _ \|   \ / _ \                         *
    *                     | | | (_) | |) | (_) |                        *
    *                     |_|  \___/|___/ \___/                         *
    *                                                                   *
    * Some configuration/initialisation must                            *
    * be done outside of the for-loop....(!)                            *
    ********************************************************************/  

    /* forever */
    for(;;)
    {
        /********************************************************************
        *                    _____  ___  ___   ___                          *
        *                   |_   _|/ _ \|   \ / _ \                         *
        *                     | | | (_) | |) | (_) |                        *
        *                     |_|  \___/|___/ \___/                         *
        *                                                                   *
        * Write down your logic here.                                       *
        ********************************************************************/  
    }
}

/********************************************************************
 *                      Interrupt Functions                         *
 ********************************************************************/  

void PITCHANNEL0(void)
{
	NDWSpeedPacket.data = POT1;
	CAN_Write(NDWSPEEDBUF ,NDWSpeedPacket);
	interruptCounter++;
	
	if(interruptCounter%2==0){
		if(isErrorDoor){CAN_Write(ERRORBUF,errorPacket); 			LED=~LED7;
		}
		if(Alive) CAN_Write(ALIVEBUF,alivePacket);    
	}
	if(interruptCounter%4==0){
		displayPacket.data = 0;
		displayPacket.data = indicatorPacket.data & 0x07;
		headlightPacket.data &= 0x07;
		displayPacket.data  |= headlightPacket.data << 3;
		if(SW1==0){
			if(lightPacket.data > LIGHT_THRESH ){
				displayPacket.data |= 0x30;
		}	
		CAN_Write(DISPLAYBUF,displayPacket);
		isError = 1;


    PIT.CH[0].TFLG.B.TIF = 1;
}

void PITCHANNEL1(void)
{
    /* your own code above! */
    PIT.CH[1].TFLG.B.TIF = 1;
}

void CANMB0003(void)
{
/* No modifications needed here */
/* Receive interrupts are being cleared here */
    CAN_0.IFRL.B.BUF00I = 1;
    CAN_0.IFRL.B.BUF01I = 1;
    CAN_0.IFRL.B.BUF02I = 1;
    CAN_0.IFRL.B.BUF03I = 1;
}

void onMessageReceived(msgPacket inMsgPacket){
//use the inMsgPacket to do the intended function with the packet

    switch(inMsgPacket.standardId){
        case LIGHTVALUEID :
            lightPacket.data = inMsgPacket.data
        break;
        case INDICATORID :
            indicatorPacket.data = inMsgPacket.data
        break;
	  case HEADLIGHTID :
            headlightPacket.data = inMsgPacket.data
        break;

        case ECU3_ALIVE:
            isError=0;
        break;

    }
}


void CANMB0407(void)
{
    /********************************************************************
    *                    _____  ___  ___   ___                          *
    *                   |_   _|/ _ \|   \ / _ \                         *
    *                     | | | (_) | |) | (_) |                        *
    *                     |_|  \___/|___/ \___/                         *
    *                                                                   *
    * CAN reception is handled here                                     *
    * The following buffers are important:                              *
    * CAN_0.RXFIFO.ID.B.STD_ID: ID of received message                  *
    * CAN_0.RXFIFO.DATA.B[i]: value of data byte 'i'                    *
    * IMPORTANT: check for the flag in CAN_0.IFRL.B.BUF05I first!       *
    ********************************************************************/  
if(CAN_0.IFRL.B.BUF05I==1){
         LED5=~LED5;
        //read the fifo from this interrupt 
        msgPacket inputMsgPacket;
        inputMsgPacket.data=0;//init
        inputMsgPacket.standardId=CAN_0.RXFIFO.ID.B.STD_ID;
        inputMsgPacket.dataLength=CAN_0.RXFIFO.CS.B.LENGTH;
        for(int i=inputMsgPacket.dataLength; i>0;i--){
            //doesnt enter if dataLength is zero
            inputMsgPacket.data|=(CAN_0.BUF[messageBufferNo].DATA.B[i-1]);
            inputMsgPacket.data=inputMsgPacket.data<<8;
        }
        onMessageReceived(inputMsgPacket);
    }
    LED6=~LED6;

   
    /* end of own code! */
    /* clear flags as last step here! */
    /* don't change anything below! */
    CAN_0.IFRL.B.BUF04I = 1;
    CAN_0.IFRL.B.BUF05I = 1;
    CAN_0.IFRL.B.BUF06I = 1;
    CAN_0.IFRL.B.BUF07I = 1;
}

void CANMB0811(void)
{
/* No modifications needed here */
/* transmit interrupts are being cleared here */

    CAN_0.IFRL.B.BUF08I = 1;
    CAN_0.IFRL.B.BUF09I = 1;
    CAN_0.IFRL.B.BUF10I = 1;
    CAN_0.IFRL.B.BUF11I = 1;
}

void CANMB1215(void)
{
/* No modifications needed here */
/* transmit interrupts are being cleared here */
    CAN_0.IFRL.B.BUF12I = 1;
    CAN_0.IFRL.B.BUF13I = 1;
    CAN_0.IFRL.B.BUF14I = 1;
    CAN_0.IFRL.B.BUF15I = 1;
}



/********************************************************************
 *                   Interrupt Vector Table                         *
 ********************************************************************/
#pragma interrupt Ext_Isr
#pragma section IrqSect RX address=0x040
#pragma use_section IrqSect Ext_Isr

void Ext_Isr() {
    switch(INTC.IACKR.B.INTVEC)
    {
        case 59:
            PITCHANNEL0();
            break;
        case 60:
            PITCHANNEL1();
        case 68:
            CANMB0003();
            break;
        case 69:
            CANMB0407();
            break;
        case 70:
            CANMB0811();
            break;
        case 71:
            CANMB1215();
            break;        
        default:
            break;
    }
    /* End of Interrupt Request */
    INTC.EOIR.R = 0x00000000;
}
