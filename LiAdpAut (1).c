#include <Rte_LiAdpAut.h>
#define true 1
#define false 0

void LiAdpAut_Run_AutoLight()
{
	// These functions can be used to access the data elements
	
	uint8 Light_Value = Rte_IRead_Run_AutoLight_Rp_LightValue_LightSensor_Data();
	boolean Auto_po_check = Rte_IRead_Run_AutoLight_Rp_SW_Auto_ON_OFF_Indicator();
	boolean LowBeam_Check = Rte_IRead_Run_AutoLight_Rp_SW_Low_ON_OFF_Indicator();
	
	boolean LB = false;
	boolean DayL = false;
	
	//Rte_IWrite_Run_AutoLight_Pp_DayTime_ON_OFF_Indicator(boolean DayL);
	//Rte_IWrite_Run_AutoLight_Pp_LowBeam_ON_OFF_Indicator(boolean LB);
	
	if(Auto_po_check == true)
	{	
		if(Light_Value < 100 || LowBeam_Check == true)
		{
			LB = true;
			Rte_IWrite_Run_AutoLight_Pp_LowBeam_ON_OFF_Indicator(LB);
			
			DayL = false;
			Rte_IWrite_Run_AutoLight_Pp_DayTime_ON_OFF_Indicator(DayL);
		}
		else if(Light_Value >= 100 && LowBeam_Check == false)
		{
			
			LB = false;
			Rte_IWrite_Run_AutoLight_Pp_LowBeam_ON_OFF_Indicator(LB);
			
			DayL = true;
			Rte_IWrite_Run_AutoLight_Pp_DayTime_ON_OFF_Indicator(DayL);
		}	
	}
	else if(LowBeam_Check == true)
	{
			LB = true;
			Rte_IWrite_Run_AutoLight_Pp_LowBeam_ON_OFF_Indicator(LB);
			
			DayL = false;
			Rte_IWrite_Run_AutoLight_Pp_DayTime_ON_OFF_Indicator(DayL);
	}
	
	else if(LowBeam_Check== false && Auto_po_check == false)
	{
			LB = false;
			Rte_IWrite_Run_AutoLight_Pp_LowBeam_ON_OFF_Indicator(LB);
			
			DayL = false;
			Rte_IWrite_Run_AutoLight_Pp_DayTime_ON_OFF_Indicator(DayL);
	}
}
