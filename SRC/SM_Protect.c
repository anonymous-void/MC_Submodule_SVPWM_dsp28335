#include "DSP2833x_Device.h"
#include "SM_app.h"


void DI_Fault(void)
{
	SM_STATUS.ECAT_UP.SM12_fault.bit.SM1_DrvFault = ~SM_STATUS.DI_STATUS.bit.Drv1_STATUS;
	SM_STATUS.ECAT_UP.SM12_fault.bit.SM1_BriShortCur = ~SM_STATUS.DI_STATUS.bit.SM1_ShortCur;
	SM_STATUS.ECAT_UP.SM12_fault.bit.SM1_TempOver = ~SM_STATUS.DI_STATUS.bit.SM1_OverTemp;

	SM_STATUS.ECAT_UP.SM12_fault.bit.SM2_DrvFault = ~SM_STATUS.DI_STATUS.bit.Drv2_STATUS;
	SM_STATUS.ECAT_UP.SM12_fault.bit.SM2_BriShortCur = ~SM_STATUS.DI_STATUS.bit.SM2_ShortCur;
	SM_STATUS.ECAT_UP.SM12_fault.bit.SM2_TempOver = ~SM_STATUS.DI_STATUS.bit.SM2_OverTemp;

	SM_STATUS.ECAT_UP.SM34_fault.bit.SM3_DrvFault = ~SM_STATUS.DI_STATUS.bit.Drv3_STATUS;
	SM_STATUS.ECAT_UP.SM34_fault.bit.SM3_BriShortCur = ~SM_STATUS.DI_STATUS.bit.SM3_ShortCur;
	SM_STATUS.ECAT_UP.SM34_fault.bit.SM3_TempOver = ~SM_STATUS.DI_STATUS.bit.SM3_OverTemp;

	SM_STATUS.ECAT_UP.SM34_fault.bit.SM4_DrvFault = ~SM_STATUS.DI_STATUS.bit.Drv4_STATUS;
	SM_STATUS.ECAT_UP.SM34_fault.bit.SM4_BriShortCur = ~SM_STATUS.DI_STATUS.bit.SM4_ShortCur;
	SM_STATUS.ECAT_UP.SM34_fault.bit.SM4_TempOver = ~SM_STATUS.DI_STATUS.bit.SM4_OverTemp;

}

//////////直流电压保护判断，放在1ms一次中断的TIMER2中/////////////////////
void Vol_ProtectI(void)
{

	//////////I段过压/////////////////////
	if(SM_STATUS.ECAT_UP.SM1Udc >  ECAT_DOWNLOAD.UdcOverVol)
		{
			OverVol_I_CNT_SM1++;
			if(OverVol_I_CNT_SM1 >= OverVol_TIME)
				{
				SM_STATUS.ECAT_UP.SM12_fault.bit.SM1_UdcOverVol = 1;
				OverVol_I_CNT_SM1 = OverVol_TIME+3;
				}
		}
		else
			OverVol_I_CNT_SM1 = 0;
	
	if(SM_STATUS.ECAT_UP.SM2Udc >ECAT_DOWNLOAD.UdcOverVol)
		{
			OverVol_I_CNT_SM2++;
			if(OverVol_I_CNT_SM2 >= OverVol_TIME)
				{
				SM_STATUS.ECAT_UP.SM12_fault.bit.SM2_UdcOverVol = 1;
				OverVol_I_CNT_SM2 = OverVol_TIME+3;
				}
		}
		else
			OverVol_I_CNT_SM2 = 0;

	if(SM_STATUS.ECAT_UP.SM3Udc > ECAT_DOWNLOAD.UdcOverVol)
		{
			OverVol_I_CNT_SM3++;
			if(OverVol_I_CNT_SM3 >= OverVol_TIME)
				{
				SM_STATUS.ECAT_UP.SM34_fault.bit.SM3_UdcOverVol = 1;
				OverVol_I_CNT_SM3 = OverVol_TIME+3;
				}
		}
		else
			OverVol_I_CNT_SM3 = 0;

	if(SM_STATUS.ECAT_UP.SM4Udc >ECAT_DOWNLOAD.UdcOverVol)
		{
			OverVol_I_CNT_SM4++;
			if(OverVol_I_CNT_SM4 >= OverVol_TIME)
				{
				 SM_STATUS.ECAT_UP.SM34_fault.bit.SM4_UdcOverVol = 1;
				 OverVol_I_CNT_SM4 = OverVol_TIME+3;
				}
		}
		else
			OverVol_I_CNT_SM4 = 0;		


	////////////欠压//////////////////LYB 2013.04.15
/*
	if(SM_CMD.bit.UnderVolJudgeEn)
			{

			if(SM_STATUS.ECAT_UP.SM1Udc < ECAT_DOWNLOAD.UdcUnderVol)	
				{
					UnderVol_CNT_SM1++;
					if(UnderVol_CNT_SM1 >= ECAT_DOWNLOAD.UdcUnderVolTime)
						{
							SM_STATUS.ECAT_UP.SM12_fault.bit.SM1_UnderVol= 1;
							UnderVol_CNT_SM1 = ECAT_DOWNLOAD.UdcUnderVolTime+3;
							
						}
				}
				else UnderVol_CNT_SM1 = 0;

			
			if(SM_STATUS.ECAT_UP.SM2Udc < ECAT_DOWNLOAD.UdcUnderVol) 
				{
					UnderVol_CNT_SM2++;
					if(UnderVol_CNT_SM2 >= ECAT_DOWNLOAD.UdcUnderVolTime)
						{
							SM_STATUS.ECAT_UP.SM12_fault.bit.SM2_UnderVol = 1;
							UnderVol_CNT_SM2 = ECAT_DOWNLOAD.UdcUnderVolTime+3;
							
						}
				}
				else UnderVol_CNT_SM2 = 0;


			
			if(SM_STATUS.ECAT_UP.SM3Udc < ECAT_DOWNLOAD.UdcUnderVol) 
				{
					UnderVol_CNT_SM3++;
					if(UnderVol_CNT_SM3 >= ECAT_DOWNLOAD.UdcUnderVolTime)
						{
							SM_STATUS.ECAT_UP.SM34_fault.bit.SM3_UnderVol = 1;
							UnderVol_CNT_SM3 = ECAT_DOWNLOAD.UdcUnderVolTime+3;
							
						}
				}
				else UnderVol_CNT_SM3 = 0;


			if(SM_STATUS.ECAT_UP.SM4Udc < ECAT_DOWNLOAD.UdcUnderVol) 
				{
					UnderVol_CNT_SM4++;
					if(UnderVol_CNT_SM4 >= ECAT_DOWNLOAD.UdcUnderVolTime)
						{
							SM_STATUS.ECAT_UP.SM34_fault.bit.SM4_UnderVol = 1;
							UnderVol_CNT_SM4 = ECAT_DOWNLOAD.UdcUnderVolTime +3;
							
						}
				}
				else UnderVol_CNT_SM4 = 0;

			}

		///////////////LYB 2013.04.15///////////////////////////
*/
}

/////////////////电压过压II段过压速断,放在EXINT外部中断中

void Vol_ProtectII(void)
{
/*
	if(SM_STATUS.ECAT_UP.SM1Udc >= OverVol_TIME )
		{
			OverVol_II_CNT_SM1++;
			if( OverVol_II_CNT_SM1>= OverVol_II_SPOT)
				{
					SM_STATUS.ECAT_UP.SM12_fault.bit.SM1_UdcOverVol = 1;
					OverVol_II_CNT_SM1 = OverVol_II_SPOT+3;
				}
		}
		else OverVol_II_CNT_SM1 = 0;

	if(SM_STATUS.ECAT_UP.SM2Udc >= OverVol_II )
		{
			OverVol_II_CNT_SM2++;
			if( OverVol_II_CNT_SM2>= OverVol_II_SPOT)
				{
					SM_STATUS.ECAT_UP.SM12_fault.bit.SM2_UdcOverVol = 1;
					OverVol_II_CNT_SM2 = OverVol_II_SPOT+3;
				}
		}
		else OverVol_II_CNT_SM2 = 0;		

	if(SM_STATUS.ECAT_UP.SM3Udc >= OverVol_II )
		{
			OverVol_II_CNT_SM3++;
			if( OverVol_II_CNT_SM3>= OverVol_II_SPOT)
				{
					SM_STATUS.ECAT_UP.SM34_fault.bit.SM3_UdcOverVol = 1;
					OverVol_II_CNT_SM3 = OverVol_II_SPOT+3;
				}
		}
		else OverVol_II_CNT_SM3 = 0;	

	if(SM_STATUS.ECAT_UP.SM4Udc >= OverVol_II )
		{
			OverVol_II_CNT_SM4++;
			if( OverVol_II_CNT_SM4>= OverVol_II_SPOT)
				{
					SM_STATUS.ECAT_UP.SM34_fault.bit.SM4_UdcOverVol = 1;
					OverVol_II_CNT_SM4 = OverVol_II_SPOT+3;
				}
		}
		else OverVol_II_CNT_SM4 = 0;

*/
}

void Cur_Protect(void)
{
	if(SM_STATUS.ECAT_UP.SM_Cur >= ECAT_DOWNLOAD.OverCur)
		{
			OverCur_CNT++;
			if(OverCur_CNT>=OverCur_TIME)
				{
					SM_STATUS.ECAT_UP.SM12_fault.bit.SM1_OverCur = 1;
					SM_STATUS.ECAT_UP.SM12_fault.bit.SM2_OverCur = 1;
					SM_STATUS.ECAT_UP.SM34_fault.bit.SM3_OverCur = 1;
					SM_STATUS.ECAT_UP.SM34_fault.bit.SM4_OverCur = 1;
					OverCur_CNT = OverCur_TIME+3;
					
				}
		}
		else OverCur_CNT=0;

}

void Cur_ProtectSD(void)
{
	/*
	if(abs(SM_STATUS.ECAT_UP.SM_Cur) >= ECAT_DOWNLOAD.OverCurSD )
	{
		OverCurSD_CNT++;
		if(OverCurSD_CNT>=OverCurSD_SPOT)
			{
				SM_STATUS.ECAT_UP.SM12_fault.bit.SM1_OverCurSD= 1;
				SM_STATUS.ECAT_UP.SM12_fault.bit.SM2_OverCurSD = 1;
				SM_STATUS.ECAT_UP.SM34_fault.bit.SM3_OverCurSD = 1;
				SM_STATUS.ECAT_UP.SM34_fault.bit.SM4_OverCurSD = 1;
				OverCurSD_CNT = OverCurSD_SPOT+3;
				
			}
	}
	else OverCurSD_CNT=0;
*/
}


void COMM_Fault(void)
{
	SM_STATUS.ECAT_UP.SM12_fault.bit.SM1_CommFault = 1;
	SM_STATUS.ECAT_UP.SM12_fault.bit.SM2_CommFault = 1;
	SM_STATUS.ECAT_UP.SM34_fault.bit.SM3_CommFault = 1;
	SM_STATUS.ECAT_UP.SM34_fault.bit.SM4_CommFault = 1;

}



