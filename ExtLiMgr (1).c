#include <Rte_ExtLiMgr.h>
#define true 1
#define false 0
void ExtLiMgr_Run_ExtLightMang()
{
	// These functions can be used to access the data elements
	
	boolean DayL = Rte_IRead_Run_ExtLightMang_Rp_DayTime_ON_OFF_Indicator();
	boolean LB = Rte_IRead_Run_ExtLightMang_Rp_LowBeam_ON_OFF_Indicator();
	boolean Opt = Rte_IRead_Run_ExtLightMang_Rp_OpMode_ON_OFF_Indicator();
	
	boolean Act_LBeam = false;
	boolean Act_DayL = false;
	boolean Ind_LBeam = false;
	
	//Rte_IWrite_Run_ExtLightMang_Pp_DayTime_Out_ON_OFF_Indicator(boolean Act_DayL);
	//Rte_IWrite_Run_ExtLightMang_Pp_LowBeamInd_Out_ON_OFF_Indicator(boolean Ind_LBeam);
	//Rte_IWrite_Run_ExtLightMang_Pp_LowBeam_Out_ON_OFF_Indicator(boolean Act_LBeam);
	
	if( Opt == true)
	{
		if(LB == true)
		{
			Ind_LBeam = Act_LBeam = true;
			Rte_IWrite_Run_ExtLightMang_Pp_LowBeam_Out_ON_OFF_Indicator(Act_LBeam);
			Rte_IWrite_Run_ExtLightMang_Pp_LowBeamInd_Out_ON_OFF_Indicator(Ind_LBeam);
			
			DayL = false;
			Rte_IWrite_Run_ExtLightMang_Pp_DayTime_Out_ON_OFF_Indicator(Act_DayL);

		}
		else if (DayL == true)
		{
			Act_DayL = true;
			Rte_IWrite_Run_ExtLightMang_Pp_DayTime_Out_ON_OFF_Indicator(Act_DayL);
			
			Ind_LBeam = Act_LBeam = false;
			Rte_IWrite_Run_ExtLightMang_Pp_LowBeam_Out_ON_OFF_Indicator(Act_LBeam);
			Rte_IWrite_Run_ExtLightMang_Pp_LowBeamInd_Out_ON_OFF_Indicator(Ind_LBeam);
		}
	}
	else
	{
		Act_LBeam = false;
		Act_DayL = false;
		Ind_LBeam = false;
		
		Rte_IWrite_Run_ExtLightMang_Pp_LowBeam_Out_ON_OFF_Indicator(Act_LBeam);
		Rte_IWrite_Run_ExtLightMang_Pp_DayTime_Out_ON_OFF_Indicator(Act_DayL);
		Rte_IWrite_Run_ExtLightMang_Pp_LowBeamInd_Out_ON_OFF_Indicator(Ind_LBeam);
	}
}
