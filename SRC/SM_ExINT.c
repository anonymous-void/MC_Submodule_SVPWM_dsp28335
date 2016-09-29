#include "DSP2833x_Device.h"
#include "SM_app.h"
#include "SYM_app.h"


int IN=1;
int N=0;
interrupt void Xint3_isr(void)
{

	if(ProDelayCNT>=10)
		{
			ProDelayCNT=20;
			ProJudgeEn=1;
		}
		else 
			ProJudgeEn++;
	if(!COMM_Fault_Flag) COMM_CNT = 0;
	//EcatSatusRead();//LYB 20130128////////
//    Ecat_DATA_Get(); // SYM: Disable for SVPWM, function prefixed with sym_ implemented
//	Ecat_CMD_Re();

	sym_Ecat_DATA_Get(); // Copy data from FPGA COM board to 28335's ram
	sym_Ecat_DATA_Decode(); // Decode all the downloaded info according to protocol
	sym_Matrix_Generation(); // Calc the vector and duty cycle of one switching period

	sym_CMD_Handwith();

	DIUpData( );
	if(ProJudgeEn) DI_Fault();
	 ADC_Sample();

/*
	if(ProJudgeEn)
	{
	 Vol_ProtectII( );  ///////test////////////
	 if(CurSampleEn) Cur_ProtectSD( );  
	}
*/
//	CMD_Handwith();  // SYM: Disable for SVPWM, function prefixed with sym_ implemented


	SMGpioDataSet(28,GPIO_OUT_DOWN);
	ECatWrite();
	SMGpioDataSet(28,GPIO_OUT_UP);
/*
	int angel;
	float A,B,C;
	A = ((float)ECAT_DOWNLOAD.UdcOverVol)/100;
	B = ((float)ECAT_DOWNLOAD.UdcOverVolTime)/100.0;
	C = A*sin(6.283185*B);
	angel=(int)(1875+1500*C);
*/
//	EALLOW;
//	EPwm1Regs.CMPA.half.CMPA = MC_Modulation;
//	EPwm1Regs.CMPB = MC_Modulation;
//	EPwm2Regs.CMPA.half.CMPA = MC_Modulation;
//	EPwm2Regs.CMPB = MC_Modulation;
//	EPwm3Regs.CMPA.half.CMPA = MC_Modulation;
//	EPwm3Regs.CMPB = MC_Modulation;
//	EPwm4Regs.CMPA.half.CMPA = MC_Modulation;
//	EPwm4Regs.CMPB = MC_Modulation;
//
//	EDIS;
 //   EcatInit( );
	// Acknowledge this interrupt to get more from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}






void SM_ExInt3_Init(void)
{
	EALLOW; 
	PieVectTable.XINT3 = &Xint3_isr;
	PieCtrlRegs.PIEIER12.bit.INTx1 = 1;
	IER |= M_INT12;
	EDIS;
	*(Uint16 *)0x100102 = 0xFF00;//0x204-0x205 AL IRQ Event Mask
	*(Uint16 *)0x100103 = 0x00FF;//0x206-0x207 AL IRQ Event Mask

	// GPIO0 and GPIO1 are inputs
	EALLOW;
	GpioCtrlRegs.GPBPUD.bit.GPIO36 = 0;

	GpioCtrlRegs.GPBMUX1.bit.GPIO36= 0;         // GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO36 = 0;          // input
	GpioCtrlRegs.GPBQSEL1.bit.GPIO36=3;

	GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL =  36;

	EDIS;

// Configure XINT1
//0-Falling  1-Rising edge
// Falling edge interrupt 2-Falling edge 3-Falling or Rising edge
// Rising edge interrupt

	XIntruptRegs.XINT3CR.bit.POLARITY = 1;      // Rising edge interrupt

	// Enable XINT1 and XINT2
	XIntruptRegs.XINT3CR.bit.ENABLE = 1;
}




Uint16  U_lvBo_SM1(float32 U_k)
{

	float32 U_lvBo_k = 0.0;
	Uint16 U_LPF = 0;
////////////10Hz//////////////////////////////
#if LPF_10Hz
    float32  b0= 2.392902190306856e-005;
	float32  b1= 4.785804380680325e-005;
	float32  b2= 2.392902190262447e-005;
	float32  a1= -1.986116323049015e+000;
	float32  a2= 9.862120391366274e-001;

///////////1k Hz/////////////////////////////
#else
	float32  b0= 1.245155117982038e-001;  
	float32  b1= 2.490310235964069e-001;
	float32  b2= 1.245155117982038e-001;
	float32  a1= -7.844765327331030e-001;
	float32  a2= 2.825385799259176e-001;

#endif
	U_lvBo_k = b0 *U_k + b1*Udc1_Filter_buf[0] +b2*Udc1_Filter_buf[1] \
		        -a1*Udc1_Filter_buf[2] - a2*Udc1_Filter_buf[3];


	Udc1_Filter_buf[1] = Udc1_Filter_buf[0];  //U(K-2)=U(K-1)
	Udc1_Filter_buf[0] = U_k;    //U(K-1)=U(K)

    Udc1_Filter_buf[3] = Udc1_Filter_buf[2]; //U(K-2)=U(K-1) 滤波后
	Udc1_Filter_buf[2] = U_lvBo_k;   //U(K-1)=U(K)   滤波后

	U_LPF = (Uint16)(U_lvBo_k*10.0);

	return U_LPF;

	
}


Uint16  U_lvBo_SM2(float32 U_k)
{

	float32 U_lvBo_k = 0;
	Uint16 U_LPF = 0;
////////////10Hz//////////////////////////////
#if LPF_10Hz
    float32  b0= 2.392902190306856e-005;
	float32  b1= 4.785804380680325e-005;
	float32  b2= 2.392902190262447e-005;
	float32  a1= -1.986116323049015e+000;
	float32  a2= 9.862120391366274e-001;

///////////1k Hz/////////////////////////////
#else
	float32  b0= 1.245155117982038e-001;  
	float32  b1= 2.490310235964069e-001;
	float32  b2= 1.245155117982038e-001;
	float32  a1= -7.844765327331030e-001;
	float32  a2= 2.825385799259176e-001;

#endif
	U_lvBo_k = b0 *U_k + b1*Udc2_Filter_buf[0] +b2*Udc2_Filter_buf[1] \
		        -a1*Udc2_Filter_buf[2] - a2*Udc2_Filter_buf[3];


	Udc2_Filter_buf[1] = Udc2_Filter_buf[0];  //U(K-2)=U(K-1)
	Udc2_Filter_buf[0] = U_k;    //U(K-1)=U(K)

    Udc2_Filter_buf[3] = Udc2_Filter_buf[2]; //U(K-2)=U(K-1) 滤波后
	Udc2_Filter_buf[2] = U_lvBo_k;   //U(K-1)=U(K)   滤波后

	U_LPF = (Uint16)(U_lvBo_k*10.0);

	return U_LPF;

	
}

Uint16  U_lvBo_SM3(float32 U_k)
{

	float32 U_lvBo_k = 0.0;
	Uint16 U_LPF = 0;
////////////10Hz//////////////////////////////
#if LPF_10Hz
    float32  b0= 2.392902190306856e-005;
	float32  b1= 4.785804380680325e-005;
	float32  b2= 2.392902190262447e-005;
	float32  a1= -1.986116323049015e+000;
	float32  a2= 9.862120391366274e-001;

///////////1k Hz/////////////////////////////
#else
	float32  b0= 1.245155117982038e-001;  
	float32  b1= 2.490310235964069e-001;
	float32  b2= 1.245155117982038e-001;
	float32  a1= -7.844765327331030e-001;
	float32  a2= 2.825385799259176e-001;

#endif
	U_lvBo_k = b0 *U_k + b1*Udc3_Filter_buf[0] +b2*Udc3_Filter_buf[1] \
		        -a1*Udc3_Filter_buf[2] - a2*Udc3_Filter_buf[3];


	Udc3_Filter_buf[1] = Udc3_Filter_buf[0];  //U(K-2)=U(K-1)
	Udc3_Filter_buf[0] = U_k;    //U(K-1)=U(K)

    Udc3_Filter_buf[3] = Udc3_Filter_buf[2]; //U(K-2)=U(K-1) 滤波后
	Udc3_Filter_buf[2] = U_lvBo_k;   //U(K-1)=U(K)   滤波后

	U_LPF = (Uint16)(U_lvBo_k * 10.0);

	return U_LPF;

	
}

Uint16  U_lvBo_SM4(float32 U_k)
{

	float32 U_lvBo_k = 0.0;
	Uint16 U_LPF = 0;	
////////////10Hz//////////////////////////////
#if LPF_10Hz
    float32  b0= 2.392902190306856e-005;
	float32  b1= 4.785804380680325e-005;
	float32  b2= 2.392902190262447e-005;
	float32  a1= -1.986116323049015e+000;
	float32  a2= 9.862120391366274e-001;

///////////1k Hz/////////////////////////////
#else
	float32  b0= 1.245155117982038e-001;  
	float32  b1= 2.490310235964069e-001;
	float32  b2= 1.245155117982038e-001;
	float32  a1= -7.844765327331030e-001;
	float32  a2= 2.825385799259176e-001;

#endif
	U_lvBo_k = b0 *U_k + b1*Udc4_Filter_buf[0] +b2*Udc4_Filter_buf[1] \
		        -a1*Udc4_Filter_buf[2] - a2*Udc4_Filter_buf[3];


	Udc4_Filter_buf[1] = Udc4_Filter_buf[0];  //U(K-2)=U(K-1)
	Udc4_Filter_buf[0] = U_k;    //U(K-1)=U(K)

    Udc4_Filter_buf[3] = Udc4_Filter_buf[2]; //U(K-2)=U(K-1) 滤波后
	Udc4_Filter_buf[2] = U_lvBo_k;   //U(K-1)=U(K)   滤波后

	U_LPF = (Uint16)(U_lvBo_k*10.0);

	return U_LPF;
	
}


void ADC_Sample(void)
{
	float32 AD_temp=0.0;
	
	
	while (AdcRegs.ADCST.bit.INT_SEQ1== 0) {}  //如果INT_SEQ1=0表明采集还没成功

	SM_Sample[0] = ((AdcRegs.ADCRESULT0>>4) );
	SM_Sample[1] = ((AdcRegs.ADCRESULT1>>4) );
	SM_Sample[2] = ((AdcRegs.ADCRESULT2>>4) );
	SM_Sample[3] = ((AdcRegs.ADCRESULT3>>4) );
	SM_Sample[4] = ((AdcRegs.ADCRESULT4>>4) );


	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;  //清除AD标记，这个是必须的

#if AD_Test
	AD_temp = SM_Sample[0]*Udc1_test_K + Udc1_test_B;
	SM_STATUS.ECAT_UP.SM1Udc = U_lvBo_SM1(AD_temp);
	AD_temp = SM_Sample[1]*Udc2_test_K + Udc2_test_B;
	SM_STATUS.ECAT_UP.SM2Udc = U_lvBo_SM2(AD_temp);
	AD_temp = SM_Sample[2]*Udc3_test_K + Udc3_test_B;
	SM_STATUS.ECAT_UP.SM3Udc = U_lvBo_SM3(AD_temp);
	AD_temp = SM_Sample[3]*Udc4_test_K + Udc4_test_B;
	SM_STATUS.ECAT_UP.SM4Udc = U_lvBo_SM4(AD_temp);
	AD_temp = (int16)(SM_Sample[4]-AD_Bias)*Cur_test_K + Cur_test_B;
	SM_STATUS.Sm_Cur_Ins = AD_temp * CTRatio;
	SM_STATUS.ECAT_UP.SM_Cur = (int16) SM_STATUS.Sm_Cur_Ins;
#else 
	AD_temp = SM_Sample[0]*Udc1_K + Udc1_B;
	SM_STATUS.ECAT_UP.SM1Udc = U_lvBo_SM1(AD_temp);
	AD_temp = SM_Sample[1]*Udc2_K + Udc2_B;
	SM_STATUS.ECAT_UP.SM2Udc = U_lvBo_SM2(AD_temp);
	AD_temp = SM_Sample[2]*Udc3_K + Udc3_B;
	SM_STATUS.ECAT_UP.SM3Udc = U_lvBo_SM3(AD_temp);
	AD_temp = SM_Sample[3]*Udc4_K + Udc4_B;
	SM_STATUS.ECAT_UP.SM4Udc = U_lvBo_SM4(AD_temp);
	AD_temp = (int16)(SM_Sample[4]-AD_Bias)*Cur_K + Cur_B;
	SM_STATUS.Sm_Cur_Ins = AD_temp * CTRatio;
	SM_STATUS.ECAT_UP.SM_Cur = (int16) SM_STATUS.Sm_Cur_Ins;
#endif
	 

	 Cur_Sample[SampleSpot++] = SM_STATUS.Sm_Cur_Ins;

	 if((SampleSpot==200)||(SampleSpot==400))
	 	{
			PeriodFlag = 1;
			if(SampleSpot>=400) SampleSpot = 0;
	 	}

}




