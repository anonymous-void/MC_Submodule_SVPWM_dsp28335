#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"
#include <stdio.h>
#include <string.h>
#include"pqcEEPROM.h"

#define LPF_10Hz 1
#define AD_Test 0
#define PowerModule_Index 0xA100



///////////////////////0xA100///////////////////////////
/*
#define Udc1_K 0.071664039
#define Udc1_B -0.329654579
#define Udc2_K 0.071408169
#define Udc2_B -1.06398172
#define Udc3_K 0.069920291
#define Udc3_B -0.99286813
#define Udc4_K 0.070952178
#define Udc4_B -1.092663545
#define Cur_K 0.083470364
#define Cur_B 0.051860137
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
///////////////////////////////////////////////////////////
///////////////////////0xA200///////////////////////////
/*
#define Udc1_K 0.0717566
#define Udc1_B -0.25832
#define Udc2_K 0.07150007
#define Udc2_B -0.429
#define Udc3_K 0.07215007
#define Udc3_B -0.74315
#define Udc4_K 0.07263923
#define Udc4_B -0.86199
#define Cur_K 0.08479451
#define Cur_B -0.35035
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
///////////////////////////////////////////////////////////


///////////////////////0xA400///////////////////////////
/*
#define Udc1_K 0.070861678
#define Udc1_B 0.162981859
#define Udc2_K 0.072077267
#define Udc2_B -0.771226755
#define Udc3_K 0.07057163
#define Udc3_B -0.30345801
#define Udc4_K 0.074382624
#define Udc4_B -0.98185064
#define Cur_K 0.083892505	
#define Cur_B -0.262373809
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
//////////////////////////////////////////////////////////

///////////////////////0xA402///////////////////////////

#define Udc1_K 0.071123755
#define Udc1_B -0.27027027
#define Udc2_K 0.071510297
#define Udc2_B -0.929633867
#define Udc3_K 0.072181319
#define Udc3_B -0.404215389
#define Udc4_K 0.072421784
#define Udc4_B -0.919756663
#define Cur_K 0.083892505	
#define Cur_B -0.262373809
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 

/////////////////////////////////////////////////////////

///////////////////////0xB100///////////////////////////
/*
#define Udc1_K 0.071715433
#define Udc1_B -0.466150316
#define Udc2_K 0.072748436
#define Udc2_B -1.171249818
#define Udc3_K 0.072611095
#define Udc3_B -1.183560848
#define Udc4_K 0.071500072
#define Udc4_B -1.65165
#define Cur_K 0.08288982
#define Cur_B 0.0
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
/////////////////////////////////////////////////////////
///////////////////////0xB400///////////////////////////
/*
#define Udc1_K 0.070992475
#define Udc1_B 0.305267642
#define Udc2_K 0.07115412
#define Udc2_B -0.284616479
#define Udc3_K 0.072223025
#define Udc3_B -0.173335259
#define Udc4_K 0.072223025
#define Udc4_B -0.310559006

#define Cur_K 0.083017231
#define Cur_B -0.013614826
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
/////////////////////////////////////////////////////////

///////////////////////0xC100///////////////////////////
/*
#define Udc1_K 0.071357214
#define Udc1_B 0.264021693
#define Udc2_K 0.071032817
#define Udc2_B -0.483023157
#define Udc3_K 0.072066878
#define Udc3_B -0.583741712
#define Udc4_K 0.072390329
#define Udc4_B -1.071376864
#define Cur_K 0.083883272
#define Cur_B -0.41801551
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
/////////////////////////////////////////////////////////
///////////////////////0xC200///////////////////////////
/*
#define Udc1_K 0.071245369
#define Udc1_B 0.363351382
#define Udc2_K 0.071592211
#define Udc2_B -0.357961054
#define Udc3_K 0.071520526
#define Udc3_B -0.193105421
#define Udc4_K 0.071551231
#define Udc4_B -0.35060103
#define Cur_K 0.0839796406
#define Cur_B -0.357963218
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
/////////////////////////////////////////////////////////

///////////////////////0xC400///////////////////////////
/*
#define Udc1_K 0.075598488
#define Udc1_B -2.132717346
#define Udc2_K 0.070761393
#define Udc2_B -0.389187659
#define Udc3_K 0.071164247
#define Udc3_B -0.24195844
#define Udc4_K 0.071787509
#define Udc4_B -0.48097631
#define Cur_K 0.083376244
#define Cur_B -0.016241692
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
/////////////////////////////////////////////////////////

///////////////////////0xA201///////////////////////////
/*
#define Udc1_K 0.070841598
#define Udc1_B -0.368376311
#define Udc2_K 0.071571715
#define Udc2_B -0.994846837
#define Udc3_K 0.070932047
#define Udc3_B -0.85827777
#define Udc4_K 0.071285999
#define Udc4_B -1.147704591
#define Cur_K 0.08357682
#define Cur_B -0.259096501
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
/////////////////////////////////////////////////////////

///////////////////////0xA301///////////////////////////
/*
#define Udc1_K 0.07111364
#define Udc1_B -0.369790926
#define Udc2_K 0.072495288
#define Udc2_B -1.297665652
#define Udc3_K 0.074471254
#define Udc3_B -1.102174561
#define Udc4_K 0.071500072
#define Udc4_B -1.287001287
#define Cur_K 0.083520252
#define Cur_B -0.283593014
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
/////////////////////////////////////////////////////////

///////////////////////0xB300///////////////////////////
/*
#define Udc1_K 0.070721358
#define Udc1_B -0.544554455
#define Udc2_K 0.071133874
#define Udc2_B -1.152368758
#define Udc3_K 0.071459197
#define Udc3_B -1.136201229
#define Udc4_K 0.072337963
#define Udc4_B -1.193576389
#define Cur_K 0.083557546
#define Cur_B -0.194613881
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
///////////////////////////////////////////////////////////

///////////////////////0xA300///////////////////////////
/*
#define Udc1_K 0.071510297
#define Udc1_B 0.629290618
#define Udc2_K 0.069560378
#define Udc2_B 0.041736227
#define Udc3_K 0.073757191
#define Udc3_B -0.022127157
#define Udc4_K 0.073637703
#define Udc4_B -0.176730486
#define Cur_K 0.0843748
#define Cur_B -0.396139684
#define CTRatio	1.0 
#define AD_Bias 1638  //1.2VÆ«ÖÃµçÑ¹  4096*(1.2/3) = 1638 
*/
///////////////////////////////////////////////////////////



//#define OverVol_II 2000
#define OverVol_II 2300   //ËÙ¶ÏµçÑ¹---TSET
#define OverVol_II_SPOT  3
//#define OverCurSD 2300   //ËÙ¶ÏµçÁ÷¶¯×÷ÏÞÖÆ 1.414*88*2 = 248.87 A
#define OverCurSD_SPOT 3

#define PI 3.1415926

#define OverVol_TIME 100
#define OverCur_TIME 100

#define ECAT_START_ADDR (Uint16 *)0x100000 
#define ECAT_UP_DATA_OFFSET 0x900  //0x900
#define ECAT_DOWNLOAD_DATA_OFFSET 0x980 //0x980
#define ECAT_STATUS_OFFSET 0x800
#define ECAT_UP_DATA_LENGTH 8
#define ECAT_DOWN_DATA_LENGTH 14
extern Uint16 ECat_UP_Buf[ECAT_UP_DATA_LENGTH];
extern Uint16 ECat_Download_Buf[ECAT_DOWN_DATA_LENGTH];



#define GPIO_FUN_00 0
#define GPIO_FUN_01 1
#define GPIO_FUN_10 2
#define GPIO_FUN_11 3
#define GPIO_R_UP    0
#define GPIO_R_DOWN  1
#define GPIO_OUT_UP      1
#define GPIO_OUT_DOWN    0
#define GPIO_DIR_OUT   1
#define GPIO_DIR_IN    0

#define EPWM_DB 0x0004

#define XiaodouTime 10

#define Timer2LedOn GpioDataRegs.GPADAT.bit.GPIO29 = 0
#define Timer2LedOff GpioDataRegs.GPADAT.bit.GPIO29 = 1
#define Timer2Twinkle GpioDataRegs.GPATOGGLE.bit.GPIO29 = 1
#define InvLedOn GpioDataRegs.GPADAT.bit.GPIO12 = 0
#define InvLedOff GpioDataRegs.GPADAT.bit.GPIO12 = 1
#define InvLedTwinkle GpioDataRegs.GPATOGGLE.bit.GPIO12 = 1
#define PassbyLedOn GpioDataRegs.GPADAT.bit.GPIO13 = 0
#define PassbyLedOff GpioDataRegs.GPADAT.bit.GPIO13 = 1
#define PassbyLedTwinkle GpioDataRegs.GPATOGGLE.bit.GPIO13 = 1
#define SM1FaultLedOn GpioDataRegs.GPADAT.bit.GPIO14 = 0
#define SM1FaultLedOff GpioDataRegs.GPADAT.bit.GPIO14 = 1
#define SM1FaultLedTwinkle GpioDataRegs.GPATOGGLE.bit.GPIO14 = 1
#define SM2FaultLedOn GpioDataRegs.GPADAT.bit.GPIO15 = 0
#define SM2FaultLedOff GpioDataRegs.GPADAT.bit.GPIO15 = 1
#define SM2FaultLedTwinkle GpioDataRegs.GPATOGGLE.bit.GPIO15 = 1
#define SM3FaultLedOn GpioDataRegs.GPADAT.bit.GPIO16 = 0
#define SM3FaultLedOff GpioDataRegs.GPADAT.bit.GPIO16 = 1
#define SM3FaultLedTwinkle GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1
#define SM4FaultLedOn GpioDataRegs.GPADAT.bit.GPIO17 = 0
#define SM4FaultLedOff GpioDataRegs.GPADAT.bit.GPIO17 = 1
#define SM4FaultLedTwinkle GpioDataRegs.GPATOGGLE.bit.GPIO17 = 1






void InitAdc(void);
void SM_ADC_DATA_Init(void);


void  SMGpioSet(Uint16 ioNum, Uint16 fun, Uint16 upOrDown, Uint16 driect, Uint16 qsel);
void SMGpioDataSet(Uint16 ioNum, Uint16 highOrlOw);
Uint16 SMGpioDataRead(Uint16 ioNum);
void MOSFETBlock(void);
void ThyristorBlock(void);
void ThyristorPassBy(void);
void Mosfet_Drv_Reset(void);
void LED_ALL_ON(void);
void LED_ALL_OFF(void);
void SM_GPIO_Init(void);

Uint16 EcatSatusRead(void);
Uint16 ReadEcatAddr(void);
void EcatInit(void);
void EcatRead(Uint16 *pEtherCatReBuf);
void ECatWrite(void);
void EcatDataInit(void);
void Ecat_CMD_Re(void);


void SM_ExInt3_Init(void);
interrupt void Xint3_isr(void);

void SM_Timer_Init(void);
interrupt void cpu_timer0_isr(void);
interrupt void cpu_timer1_isr(void);
interrupt void cpu_timer2_isr(void);


void DisableDog(void);
void InitPll(Uint16 val, Uint16 divsel);
void InitPeripheralClocks(void);
void InitXintf16Gpio(void);

void InitEPwm1to4Gpio(void);
void InitEPwm1Gpio(void);
void InitEPwm2Gpio(void);
void InitEPwm3Gpio(void);
void InitEPwm4Gpio(void);
void InitEPwm1(void);
void InitEPwm2(void);
void InitEPwm3(void);
void InitEPwm4(void);
void SM_PWM_Init(void);
void SM1SwitchOn(void);
void SM1SwitchOff(void);
void SM2SwitchOn(void);
void SM2SwitchOff(void);
void SM3SwitchOn(void);
void SM3SwitchOff(void);
void SM4SwitchOn(void);
void SM4SwitchOff(void);

void  SMGpioInit(Uint16 ioNum, Uint16 fun, Uint16 upOrDown, Uint16 driect, Uint16 qsel);
void SMGpioDataSet(Uint16 ioNum, Uint16 highOrlOw);
Uint16 SMGpioDataRead(Uint16 ioNum);
void SM_GPIO_Init(void);
void DIUpData(void);
void DataInit(void);
void InitXintf(void);
void DataReset(void);
void DI_Fault(void);

void InitPieCtrl(void);
void InitPieVectTable(void);
void InitSysCtrl(void);
void ServiceDog(void);
void ADC_cal (void);

void ADC_Sample(void);
Uint16  U_lvBo_SM1(float32 U_k);
Uint16  U_lvBo_SM2(float32 U_k);
Uint16  U_lvBo_SM3(float32 U_k);
Uint16  U_lvBo_SM4(float32 U_k);

float32 RMS_N_Fun(float32 *pData, Uint16 N, Uint16 current);

Uint16  CMD_Handwith(void);

void Vol_ProtectI(void);
void Vol_ProtectII(void);
void Cur_Protect(void);
void Cur_ProtectSD(void);

void COMM_Fault(void);


extern Uint16 CurSampleEn;

extern Uint16 SM_Sample[5];
extern float32 Cur_Sample[256];
extern Uint16 SampleSpot;
extern Uint16 PeriodFlag;


extern float32 Udc1_Filter_buf[4];
extern float32 Udc2_Filter_buf[4];
extern float32 Udc3_Filter_buf[4];
extern float32 Udc4_Filter_buf[4];

extern Uint16 OverVol_I_CNT_SM1;
extern Uint16 OverVol_I_CNT_SM2;
extern Uint16 OverVol_I_CNT_SM3;
extern Uint16 OverVol_I_CNT_SM4;
extern Uint16 OverVol_II_CNT_SM1;
extern Uint16 OverVol_II_CNT_SM2;
extern Uint16 OverVol_II_CNT_SM3;
extern Uint16 OverVol_II_CNT_SM4;
extern Uint16 UnderVol_CNT_SM1;
extern Uint16 UnderVol_CNT_SM2;
extern Uint16 UnderVol_CNT_SM3;
extern Uint16 UnderVol_CNT_SM4;
extern Uint16 OverCur_CNT;
extern Uint16 OverCurSD_CNT;

extern Uint16 FaultLED_CNT;

extern float32 Udc1_test_K;
extern float32 Udc1_test_B;
extern float32 Udc2_test_K;
extern float32 Udc2_test_B;
extern float32 Udc3_test_K;
extern float32 Udc3_test_B;
extern float32 Udc4_test_K;
extern float32 Udc4_test_B;
extern float32 Cur_test_K;
extern float32 Cur_test_B;

extern Uint16 COMM_CNT;
extern Uint16 COMM_Fault_Flag;

extern Uint16 ProDelayCNT;
extern Uint16 ProJudgeEn;
extern Uint16 ECat_int_clr;

extern Uint16 ModuleCommTest[8];
extern Uint16 FlgModuleCommTest;
extern int MC_Modulation;

struct SM_CMD_BIT
{
	Uint16 Deblock:1;  //00or01-block, 11-invert, 10-pass
	Uint16 Reset:1;			//00-disable,11-reset
	Uint16 rsvd:14;
};

union SM_CMD_ALL
{
	Uint16 all;
	struct SM_CMD_BIT bit;
};


struct ECAT_receive_CMD_BIT
{
	Uint16 Reset:1;
	Uint16 deblock:1;
	Uint16 rsvd:14;
};


union ECAT_REC_CMD_ALL
{
	Uint16 all;
	struct ECAT_receive_CMD_BIT bit;
};

struct EcatDownData
{
	union ECAT_REC_CMD_ALL SM_CMD;
	int AU_M;
	int AV_M;
	int AW_M;
	int BU_M;
	int BV_M;
	int BW_M;
	int CU_M;
	int CV_M;
	int CW_M;
	Uint16 UdcOverVol;
	Uint16 OverCur;
};

struct SM_FaultStatus1_BIT
{
	Uint16 SM1_CommFault:1;
	Uint16 SM1_UdcOverVol:1;
	Uint16 SM1_UnderVol:1;
	Uint16 SM1_OverCur:1;
	Uint16 SM1_OverCurSD:1;
	Uint16 SM1_DrvFault:1;
	Uint16 SM1_BriShortCur:1;
	Uint16 SM1_TempOver:1;
	Uint16 SM2_CommFault:1;
	Uint16 SM2_UdcOverVol:1;
	Uint16 SM2_UnderVol:1;
	Uint16 SM2_OverCur:1;
	Uint16 SM2_OverCurSD:1;
	Uint16 SM2_DrvFault:1;
	Uint16 SM2_BriShortCur:1;
	Uint16 SM2_TempOver:1;

};

union SM_FaultStatus1
{
	Uint16 all;
	struct SM_FaultStatus1_BIT bit;
};

struct SM_FaultStatus2_BIT
{
	Uint16 SM3_CommFault:1;
	Uint16 SM3_UdcOverVol:1;
	Uint16 SM3_UnderVol:1;
	Uint16 SM3_OverCur:1;
	Uint16 SM3_OverCurSD:1;
	Uint16 SM3_DrvFault:1;
	Uint16 SM3_BriShortCur:1;
	Uint16 SM3_TempOver:1;
	Uint16 SM4_CommFault:1;
	Uint16 SM4_UdcOverVol:1;
	Uint16 SM4_UnderVol:1;
	Uint16 SM4_OverCur:1;
	Uint16 SM4_OverCurSD:1;
	Uint16 SM4_DrvFault:1;
	Uint16 SM4_BriShortCur:1;
	Uint16 SM4_TempOver:1;

};

union SM_FaultStatus2
{
	Uint16 all;
	struct SM_FaultStatus2_BIT bit;
};


struct EcatUpData
{
	Uint16 SM1Udc;
	Uint16 SM2Udc;
	Uint16 SM3Udc;
	Uint16 SM4Udc;
	int16 SM_Cur;
	union SM_FaultStatus1 SM12_fault;
	union SM_FaultStatus2 SM34_fault;
	Uint16 CommIndex;

};

struct SM_DI_STATUS_BIT
{
	Uint16 Drv1_STATUS:1;
	Uint16 Drv2_STATUS:1;
	Uint16 Drv3_STATUS:1;
	Uint16 Drv4_STATUS:1;
	Uint16 SM1_ShortCur:1;
	Uint16 SM2_ShortCur:1;
	Uint16 SM3_ShortCur:1;
	Uint16 SM4_ShortCur:1;
	Uint16 SM1_OverTemp:1;
	Uint16 SM2_OverTemp:1;
	Uint16 SM3_OverTemp:1;
	Uint16 SM4_OverTemp:1;
	Uint16 rsvd:4;
	
};

union DI_STATUS_ALL
{
	Uint16 all;
	struct SM_DI_STATUS_BIT bit;
};

struct DI_CHECK_ALL
{
	union DI_STATUS_ALL DI_NEW;
	Uint16 Drv1_CNT;
	Uint16 Drv2_CNT;
	Uint16 Drv3_CNT;
	Uint16 Drv4_CNT;
	Uint16 SM1_ShortCur_CNT;
	Uint16 SM2_ShortCur_CNT;
	Uint16 SM3_ShortCur_CNT;
	Uint16 SM4_ShortCur_CNT;
	Uint16 SM1_OverTemp_CNT;
	Uint16 SM2_OverTemp_CNT;
	Uint16 SM3_OverTemp_CNT;
	Uint16 SM4_OverTemp_CNT;
	
};

struct SM_STATUS_DATA
{
	struct EcatUpData ECAT_UP;
	union DI_STATUS_ALL DI_STATUS;
	float32 SM_Cur_RMS;
	float32 Sm_Cur_Ins;
};

extern union SM_CMD_ALL SM_CMD;
extern struct EcatDownData ECAT_DOWNLOAD;
extern struct SM_STATUS_DATA SM_STATUS;
extern struct DI_CHECK_ALL DI_CHECK;














