#include "init.h"

void showData(int value);

/********************************************************************
 *                              main                                *
 ********************************************************************/
void main(void)
{
    /* board initialization */
    Init();
/* we have to configure timer and here we have only one one timer so we will configur the channel timer 0 only no need to channel 1 */

PIT_ConfigureTimer(0,1000);

    /* forever */
    for(;;)
    {
/********************************************************************
 *                           Main Loop                              *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                  Write down your logic here.                     *
 ********************************************************************/  
/*-------------------------------------------/* task 2 _ 1 */-------------------*/ 
/* show the data for the analoge sensor and make crossponding led indecator for level for the sensor reading*/
//showData( ADC_0.CDR[2].BCDATA );   

/*------------------------------------------/* task 2 _ 2 */-----------------*/ 
/* show the data for the pototiometer  and make crossponding led indecator for level for the sensor reading*/
//showData( ADC_0.CDR[4].BCDATA );  


/*-----------------------------------------/* task 3_1 */------------------*/
/* switch LED 6 and LED 5 upon the value of BT5 and BT6 */
/* BT5 control LED 5 */ 
if (SIU.GPDI[1].R==0)
    SIU.GPDO[61].R=0;
else 
    SIU.GPDO[61].R=1; 

/* BT6 control LED 6 */
if (SIU.GPDI[0].R==0)
    SIU.GPDO[59].R=0;
else 
    SIU.GPDO[59].R=1;

/*-----------------------------------------/* task 3_2 */------------------*/
/*toggel LED 7 by 1000ms, but using sw 1 ( PCR 44 ) */

if (SIU.GPDI[44].R==0)
   PIT_StartTimer(0);
else 
   PIT_StartTimer(0);
 }
}

/*-------------------------------------/* task 2 _ 3 */--------------*/
void showData(int value)
/* we have to choose with which analog input to active this function with AN1 sensor or with potentiometer */
{
/********************************************************************
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 ********************************************************************/  
  if(value <= 200)
  { 
    /* LED0 - on, LED1 - off, LED2 - off, LED3 - off , LED - off  */   
   SIU.GPDO[9].R =  0 ;    /* LED0 */
   SIU.GPDO[42].R = 1 ;    /* LED1 */
   SIU.GPDO[13].R = 1 ;    /* LED2 */
   SIU.GPDO[12].R = 1 ;    /* LED3 */
   SIU.GPDO[62].R = 1 ;    /* LED4 */
     

  }
   /* LED0 - on, LED1 - on, LED2 - off, LED3 - off , LED4-off */
  else if(value > 200 && value <= 400)
{ 
   SIU.GPDO[9].R =  0 ;    /* LED0 */
   SIU.GPDO[42].R = 0 ;    /* LED1 */
   SIU.GPDO[13].R = 1 ;    /* LED2 */
   SIU.GPDO[12].R = 1 ;    /* LED3 */
   SIU.GPDO[62].R = 1 ;    /* LED4 */

  }

  else if(value > 400 && value <= 600)
/* LED0 - on, LED1 - on, LED2 - on, LED3 - off , LED4-off */
  {  
   SIU.GPDO[9].R =  0 ;    /* LED0 */
   SIU.GPDO[42].R = 0 ;    /* LED1 */
   SIU.GPDO[13].R = 0 ;    /* LED2 */
   SIU.GPDO[12].R = 1 ;    /* LED3 */
   SIU.GPDO[62].R = 1 ;    /* LED4 */
  }  
else if(value > 600 && value <= 800)
{
/* LED0 - on, LED1 - on, LED2 - on, LED3 - on , LED4-off */
  
   SIU.GPDO[9].R =  0 ;    /* LED0 */
   SIU.GPDO[42].R = 0 ;    /* LED1 */
   SIU.GPDO[13].R = 0 ;    /* LED2 */
   SIU.GPDO[12].R = 0;    /* LED3 */
   SIU.GPDO[62].R = 1 ;    /* LED4 */
}  
  else
  {  
/* LED0 - on, LED1 - on, LED2 - on, LED3 - on, LED4-on */
   SIU.GPDO[9].R =  0 ;    /* LED0 */
   SIU.GPDO[42].R = 0 ;    /* LED1 */
   SIU.GPDO[13].R = 0 ;    /* LED2 */
   SIU.GPDO[12].R = 0 ;    /* LED3 */
   SIU.GPDO[62].R = 0 ;    /* LED4 */
  }     
}

/********************************************************************
 *                      Interrupt Functions                         *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                Interrupts can be handled below.                  *
 ********************************************************************/  
void PITCHANNEL0() {

/*-----------------------------------------/* task 3_2 */------------------*/
/*toggel LED 7 by 1000ms,LED7 PCR (11) */

SIU.GPDO[11].R=~SIU.GPDO[11].R;

    /* clear flag */
    PIT.CH[0].TFLG.B.TIF = 1;
}

void PITCHANNEL1() {
    /* clear flag */
    PIT.CH[1].TFLG.B.TIF = 1;
}

/********************************************************************
 *                   Interrupt Vector Table                         *
 *                                                                  *
 *                 Don't touch anything below!                      *
 ********************************************************************/
#pragma interrupt Ext_Isr
#pragma section IrqSect RX address=0x040
#pragma use_section IrqSect Ext_Isr

void Ext_Isr() {
    switch(INTC.IACKR.B.INTVEC)
    {
        case 59:
            /* Timer Interrupt */
            PITCHANNEL0();
            break;
        case 60:
            /* Timer Interrupt */
            PITCHANNEL1();
            break;            
        default:
            break;
    }
    /* End of Interrupt Request */
    INTC.EOIR.R = 0x00000000;
}
