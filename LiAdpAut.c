#include <Rte_LiAdpAut.h>
#define true 1
#define false 0

void LiAdpAut_RLiAdpAut()
{
	// These functions can be used to access the data elements
	boolean Auto_po_check = Rte_IRead_RLiAdpAut_AutoPositionCheckIn_Indicator();
	uint8 Light_Value = Rte_IRead_RLiAdpAut_LightValueIn_LightValue();
	boolean LowBeam_Check = Rte_IRead_RLiAdpAut_LowBeamCheckIn_Indicator();

	boolean LB = false;
	boolean DayL = false;

//Rte_IWrite_RLiAdpAut_DayLightIndicator_Indicator(boolean parameter3);
	//Rte_IWrite_RLiAdpAut_LowBeamIndicator_Indicator(boolean parameter4);

	if( Auto_po_check == true)
	{
		if(Light_Value < 100 || LowBeam_Check == true)
		{
			LB = true;
			Rte_IWrite_RLiAdpAut_LowBeamIndicator_Indicator(LB);
			
			DayL = false;
			Rte_IWrite_RLiAdpAut_DayLightIndicator_Indicator(DayL);
		}
		else if(Light_Value >= 100 && LowBeam_Check == false)
		{
			
			LB = false;
			Rte_IWrite_RLiAdpAut_LowBeamIndicator_Indicator(LB);
			
			DayL = true;
			Rte_IWrite_RLiAdpAut_DayLightIndicator_Indicator(DayL);
		}	
	}
	else if(LowBeam_Check == true)
	{
			LB = true;
			Rte_IWrite_RLiAdpAut_LowBeamIndicator_Indicator(LB);
			
			DayL = false;
			Rte_IWrite_RLiAdpAut_DayLightIndicator_Indicator(DayL);
	}
	
	else if(LowBeam_Check== false && Auto_po_check == false)
	{
			LB = false;
			Rte_IWrite_RLiAdpAut_LowBeamIndicator_Indicator(LB);
			
			DayL = false;
			Rte_IWrite_RLiAdpAut_DayLightIndicator_Indicator(DayL);
	}
	
}
