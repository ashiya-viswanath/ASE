#include <Rte_ExtLiMgr.h>
#define true 1
#define false 0

void ExtLiMgr_RExtLiMgr()
{
	// These functions can be used to access the data elements
	boolean DayL = Rte_IRead_RExtLiMgr_DayLightIn_Indicator();
	boolean LB = Rte_IRead_RExtLiMgr_LowBeamIn_Indicator();
	boolean Opt = Rte_IRead_RExtLiMgr_OperationIn_Indicator();

	boolean Act_LBeam = false;
	boolean Act_DayL = false;
	boolean Ind_LBeam = false;

	//Rte_IWrite_RExtLiMgr_ActDayLight_Indicator(boolean parameter3);
	//Rte_IWrite_RExtLiMgr_ActLowBeam_Indicator(boolean parameter4);
	//Rte_IWrite_RExtLiMgr_IndLowBeam_Indicator(boolean parameter5);
	if( Opt == true)
	{
		if(LB == true)
		{
			Ind_LBeam = true;
			Act_LBeam = true;
			Rte_IWrite_RExtLiMgr_ActLowBeam_Indicator(Act_LBeam);
			Rte_IWrite_RExtLiMgr_IndLowBeam_Indicator(Ind_LBeam);
			
			DayL = false;
			Rte_IWrite_RExtLiMgr_ActDayLight_Indicator(Act_DayL);

		}
		else if (DayL == true)
		{
			Act_DayL = true;
			Rte_IWrite_RExtLiMgr_ActDayLight_Indicator(Act_DayL);
			
			Ind_LBeam = false;
			Act_LBeam = false;
			Rte_IWrite_RExtLiMgr_ActLowBeam_Indicator(Act_LBeam);
			Rte_IWrite_RExtLiMgr_IndLowBeam_Indicator(Ind_LBeam);
		}
	}
	else
	{
		Act_LBeam = false;
		Act_DayL = false;
		Ind_LBeam = false;
		
		Rte_IWrite_RExtLiMgr_ActLowBeam_Indicator(Act_LBeam);
		Rte_IWrite_RExtLiMgr_ActDayLight_Indicator(Act_DayL);
		Rte_IWrite_RExtLiMgr_IndLowBeam_Indicator(Ind_LBeam);
	}
}
