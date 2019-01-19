#include "init.h"
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

int PTI_Timer0_flag_200 = 0;
int PTI_Timer0_flag_100 = 0;
int PTI_Timer1_flag_400 = 0;
int NondrivenWheelspeed = 0;
int LightStates = 0;
int headlight;
int Indicator_sw
int Lightvalue
int Tempval1
int data_send
int Tempval2
int Temp_data
int ECU3Isalive = 0;
int bit_10_max = 1023;
int deltaSpeed = 5, speed = 0,up=1;



/********************************************************************
 *                              main                                *
 ********************************************************************/
void main(void)
{
	
	
	
	
	
    /* board initialization */
    Init();
	
	PIT_ConfigureTimer(0, 100);
    PIT_StartTimer(0);

	
    PIT_ConfigureTimer(1, 400);
    PIT_StartTimer(1);
	

    /* turn off leds */
    LED0 = 1;
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    LED5 = 1;
    LED5 = 1;
    LED7 = 1; 

//	int8_t indicatorStatus=0;
  

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
        
		
		if(SIU.GPI[44].R == 0)   /* SW1 */
		{
			mode=0			
		}
		else {mode=1}
		

		
	 // PART 1 potentiometer functionality.
         if(PTI_Timer0_flag_100 == 1){

         	CAN_0.BUF[0].ID = 0x302;
            
			
			//Reading potentiometer value for speed level.
            NondrivenWheelspeed = ADC_0.CDR[4].B.CDATA;	
			
			NondrivenWheelspeed = (NondrivenWheelspeed/1024)*300;

			CAN_0.BUF[0].DATA.B[0] = NondrivenWheelspeed;
            CAN_0.BUF[0].DATA.B[1] = NondrivenWheelspeed>>8;
			
            CAN_0.BUF[0].CS.B.CODE = 0b1100;
		 }
		
		
		if(PTI_Timer0_flag_200!=0 && PTI_Timer0_flag_200%2==0)
		
		{
		if(ECU3Isalive != 1){
            	//blink LED.
            	LED7 = ~LED7;
            	//send error signal.
            	CAN_0.BUF[5].DATA.B[0] = 0x00;
				CAN_0.BUF[5].ID = 0x303;
            	CAN_0.BUF[5].CS.B.CODE = 0b1100;
            }
            else
            {
				ECU3Isalive = 0;
	  		}
		
		
		
		}
			
			
		
		
		

			
		
	  		//clear the flag
	  		PTI_Timer0_flag_100 = 0;
            
	  }
			
		if(PTI_Timer1_flag_400 == 1)
			{			
		//light states automatic
			if (mode == 0)
			{
					if (Lightvalue<512)
					{
						//Low beam and parking light = 1
						CAN_0.BUF[5].DATA.B[5] = Data | 0x30
					}
					else
					{
						//Low beam and parking light = 0
						CAN_0.BUF[5].DATA.B[5] = Data | 0xCF
					}
			}

			// Light states manual
			else
			{
				Tempval1 = Indicator_sw;
			}
			
			if (CAN_0.BUF[5].DATA.B[5] = 0x503)
			{
				Tempval2 = headlight;		
			}
			
			Tempval2 = Tempval2 << 3;
				
			data_send = Tempval1 | Tempval2;
			CAN_0.BUF[5].DATA.B[0] = data_send;
}
	  
		//	Dashboard speed values should come here
			


		
    }
}

/********************************************************************
 *                      Interrupt Functions                         *
 ********************************************************************/  

	void PITCHANNEL0(void)
{
	PTI_Timer0_flag_100 = 1;
    PTI_Timer0_flag_200++;
	PIT.CH[0].TFLG.B.TIF = 1;
}

void PITCHANNEL1(void)
{
	PTI_Timer1_flag_400 = 1;
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
   
   if (CAN_0.IFRL.B.BUF05I == 1){
        Switch(CAN_0.RXFIFO.ID.B.STD_ID){
            
			case 
			0x402: Indicator_sw = CAN_0.RXFIFO.DATA.B.[0];
			break
			
			case 
			0x503: headlight = CAN_0.RXFIFO.DATA.B[0];         
            break;


            case 
			0x404: ECU3Isalive = 1;
            break;
			
			case
			0x101: Lightvalue = CAN_0.BUF[5].DATA.B[5];
			break;
			
			case 
			0x101: LightStates = CAN_0.RXFIFO.DATA.B.[0];
				LightStates = LightStates | (CAN_2.RXFIFO.DATA.B[1] & 0x03)<<8;
            default :
            break;
        }
   
   
   
   
    /* end of own code! */
    /* clear flags as last step here! */
    /* don't change anything below! */
    CAN_0.IFRL.B.BUF04I = 1;
    CAN_0.IFRL.B.BUF05I = 1;
    CAN_0.IFRL.B.BUF05I = 1;
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
        case 50:
            PITCHANNEL1();
        case 58:
            CANMB0003();
            break;
        case 59:
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
