#include "jdp.h"

void SIU_Init(void) {
  /***************************************************************************
   *                                  Task 1                                 *
   *    Please enter the PCR register numbers and initialitation code here   *
   ***************************************************************************/
  /* LEDs */
  
   SIU.PCR[9].R =  0x0200 ;    /* LED0 */
   SIU.PCR[42].R = 0x0200 ;    /* LED1 */
   SIU.PCR[13].R = 0x0200 ;    /* LED2 */
   SIU.PCR[12].R = 0x0200 ;    /* LED3 */
   SIU.PCR[62].R = 0x0200 ;    /* LED4 */
   SIU.PCR[61].R = 0x0200 ;    /* LED5 */
   SIU.PCR[59].R = 0x0200 ;    /* LED6 */
   SIU.PCR[11].R = 0x0200 ;    /* LED7 */

  /* ... */

  /***************************************************************************
   *                                  Task 2                                 *
   *                       Analog inputs configuration                       *
   ***************************************************************************/  
  /* SIU.PCR[].R = ; */

/* using AN1  for the light sensor */ 
   SIU.PCR[33].R = 0x2500 ;
  /* using POT  for the potentiometer */ 
   SIU.PCR[65].R = 0x2500 ;

  /* ... */

  /***************************************************************************
   *                                  Task 3                                 *
   *                            Buttons & switches                           *
   ***************************************************************************/    
  /* SIU.PCR[].R = ; */   /* BT5 */

 
SIU.PCR[0].R = 0x0100 ;    /* BT5 */
SIU.PCR[1].R = 0x0100 ;    /* BT6 */

  /* ... */



}