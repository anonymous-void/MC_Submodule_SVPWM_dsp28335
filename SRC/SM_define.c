#include "SM_app.h"

float32 Udc1_test_K;
float32 Udc1_test_B;
float32 Udc2_test_K;
float32 Udc2_test_B;
float32 Udc3_test_K;
float32 Udc3_test_B;
float32 Udc4_test_K;
float32 Udc4_test_B;
float32 Cur_test_K;
float32 Cur_test_B;
Uint16 ModuleCommTest[8];
Uint16 FlgModuleCommTest;
 int MC_Modulation;

//#pragma DATA_SECTION(ECAT_DOWNLOAD,"from28335");
struct EcatDownData ECAT_DOWNLOAD;
//#pragma DATA_SECTION(ECat_UP_Buf,"to28335");
Uint16 ECat_UP_Buf[ECAT_UP_DATA_LENGTH];
Uint16 ECat_Download_Buf[ECAT_DOWN_DATA_LENGTH];

union SM_CMD_ALL SM_CMD;
struct SM_STATUS_DATA SM_STATUS;
struct DI_CHECK_ALL DI_CHECK;

Uint16 SM_Sample[5];
float32 Cur_Sample[256];
Uint16 SampleSpot;
Uint16 PeriodFlag;

float32 Udc1_Filter_buf[4];
float32 Udc2_Filter_buf[4];
float32 Udc3_Filter_buf[4];
float32 Udc4_Filter_buf[4];

Uint16 SampleSpot;
Uint16 CurSampleEn;

Uint16 OverVol_I_CNT_SM1;
Uint16 OverVol_I_CNT_SM2;
Uint16 OverVol_I_CNT_SM3;
Uint16 OverVol_I_CNT_SM4;
Uint16 OverVol_II_CNT_SM1;
Uint16 OverVol_II_CNT_SM2;
Uint16 OverVol_II_CNT_SM3;
Uint16 OverVol_II_CNT_SM4;
Uint16 UnderVol_CNT_SM1;
Uint16 UnderVol_CNT_SM2;
Uint16 UnderVol_CNT_SM3;
Uint16 UnderVol_CNT_SM4;
Uint16 OverCur_CNT;
Uint16 OverCurSD_CNT;

Uint16 FaultLED_CNT;

Uint16 COMM_CNT;
Uint16 COMM_Fault_Flag;

Uint16 ProDelayCNT;
Uint16 ProJudgeEn;
Uint16 ECat_int_clr;

//TEST
Uint16 INV_TEST_CNT;


void DataReset(void)
{
	Uint16 i=0;
	
	COMM_CNT=0;
	COMM_Fault_Flag=0;
	memset(&ECAT_DOWNLOAD, 0, sizeof(ECAT_DOWNLOAD));
	memset(&SM_CMD,0,sizeof(SM_CMD));
	memset(&SM_STATUS,0,sizeof(SM_STATUS));
	memset(&DI_CHECK,0,sizeof(DI_CHECK));
	memset(&Cur_Sample,0,sizeof(Cur_Sample));
	memset(&Udc1_Filter_buf,0,sizeof(Udc1_Filter_buf));
	memset(&Udc2_Filter_buf,0,sizeof(Udc2_Filter_buf));
	memset(&Udc3_Filter_buf,0,sizeof(Udc3_Filter_buf));
	memset(&Udc4_Filter_buf,0,sizeof(Udc4_Filter_buf));

	FlgModuleCommTest=1;

	
	
	for(i=0;i<8;i++)ModuleCommTest[i]=0;
	for(i=0;i<=4;i++)
		{
			SM_Sample[i] = 0;
			Udc1_Filter_buf[i] = 0.0;
			Udc2_Filter_buf[i] = 0.0;
			Udc3_Filter_buf[i] = 0.0;
			Udc4_Filter_buf[i] = 0.0;
		}

	for(i=0;i<ECAT_DOWN_DATA_LENGTH;i++) ECat_Download_Buf[i]=0;
	for(i=0;i<ECAT_UP_DATA_LENGTH;i++) ECat_UP_Buf[i] = 0;

	SampleSpot = 0;
	PeriodFlag = 0;

	OverVol_I_CNT_SM1 = 0;
	OverVol_I_CNT_SM2 = 0;
	OverVol_I_CNT_SM3 = 0;
	OverVol_I_CNT_SM4 = 0;
	OverVol_II_CNT_SM1 = 0;
	OverVol_II_CNT_SM2 = 0;
	OverVol_II_CNT_SM3 = 0;
	OverVol_II_CNT_SM4 = 0;
	UnderVol_CNT_SM1 = 0;
	UnderVol_CNT_SM2 = 0;
	UnderVol_CNT_SM3 = 0;
	UnderVol_CNT_SM4 = 0;
	OverCur_CNT = 0;
	OverCurSD_CNT = 0;

	FaultLED_CNT = 0;

	ProDelayCNT = 0;
	ProJudgeEn = 0;
	ECat_int_clr = 0;

	 Udc1_test_K = 1;
     Udc1_test_B = 0.0;
     Udc2_test_K = 1;
     Udc2_test_B = 0.0;
     Udc3_test_K = 1;
     Udc3_test_B = 0.0;
     Udc4_test_K = 1;
     Udc4_test_B = 0.0;
     Cur_test_K = 1;
     Cur_test_B = 0.0;
     MC_Modulation = 0;;

//TEST
     INV_TEST_CNT=0;
/*
	 Udc1_test_K = Udc1_K;
     Udc1_test_B = Udc1_B;
     Udc2_test_K = Udc2_K;
     Udc2_test_B = Udc2_B;
     Udc3_test_K = Udc3_K;
     Udc3_test_B = Udc3_B;
     Udc4_test_K = Udc4_K;
     Udc4_test_B = Udc4_B;
     Cur_test_K = Cur_K;
     Cur_test_B = Cur_B;
*/

}

void DataInit(void)
{
	DataReset();
	if((PowerModule_Index&0x00FF)==0x00)
		{
			CurSampleEn = 1;
			
		}
	else CurSampleEn=0;
}





