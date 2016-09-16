#include "DSP2833x_Device.h"
#include "SM_app.h"
#include "DSP2833x_ePwm_defines.h"

void SM_Timer_Init(void)
{
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
//   PieVectTable.TINT0 =  &cpu_timer0_isr;
   PieVectTable.TINT2 =  &cpu_timer2_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

   InitCpuTimers();   // For this example, only initialize the Cpu Timers


//   ConfigCpuTimer(&CpuTimer0, 150, 156);//5个点中断一次
   ConfigCpuTimer(&CpuTimer2,150,1000);///1ms中断一次

// To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
// below settings must also be updated.

//   CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
   CpuTimer2Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0	
// Enable CPU int1 which is connected to CPU-Timer 0
//   IER |= M_INT1;
   IER |= M_INT14;
// Enable TINT0 in the PIE: Group 1 interrupt 7
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

}


interrupt void cpu_timer0_isr(void)  //////5个外部中断的时间产生一次定时器0中断//////////////
{  

	int Temp_IR;

//	ServiceDog();
	

//	ADC_Sample( );
/*
			EALLOW;
			PassbyLedOff;
			InvLedOn;
			EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
		    SM_CMD.bit.SM4_Switch=~SM_CMD.bit.SM4_Switch;
			if(SM_CMD.bit.SM1_Switch) SM1SwitchOn( );
				else SM1SwitchOff( );
			if(SM_CMD.bit.SM2_Switch) SM2SwitchOn( );
				else SM2SwitchOff( );
			if(SM_CMD.bit.SM3_Switch) SM3SwitchOn( );
				else SM3SwitchOff( );
			if(SM_CMD.bit.SM4_Switch) SM4SwitchOn( );
				else SM4SwitchOff( );
			EDIS;
*/

/*
	EcatSatusRead();//LYB 20130128////////
    Ecat_DATA_Get();
	Ecat_CMD_Re( );
	ECatWrite( );	
*/
	/*
	if(COMM_CNT>4)
		{
			COMM_Fault();
			COMM_Fault_Flag = 1;
			COMM_CNT = 10;
			EcatInit( );
			if(ECat_int_clr==0)
			{
			*(Uint16 *)0x00004102 = 0xFF00;//0x204-0x205 AL IRQ Event Mask 
			*(Uint16 *)0x00004103 = 0x00FF;//0x206-0x207 AL IRQ Event Mask
			Temp_IR = *(Uint16 *)0x00004800;清中断 diya
			ECat_int_clr=1;
			}
		}
		else
			COMM_CNT++;
//     Acknowledge this interrupt to receive more interrupts from group 1
 *
 */
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

interrupt void cpu_timer2_isr(void)  ///////1ms产生一次定时器中断//////////////////////
{

	if(FaultLED_CNT >= 500)
	  {
		EALLOW;
		Timer2Twinkle;
		///LYB 2013.04.19///
     	if((SM_STATUS.ECAT_UP.SM12_fault.all & 0x00ff)!=0) SM1FaultLedTwinkle;	//模块1故障
		if((SM_STATUS.ECAT_UP.SM12_fault.all & 0xff00)!=0) SM2FaultLedTwinkle;	//模块2故障
		if((SM_STATUS.ECAT_UP.SM34_fault.all & 0x00ff)!=0) SM3FaultLedTwinkle;	//模块3故障
		if((SM_STATUS.ECAT_UP.SM34_fault.all & 0xff00)!=0) SM4FaultLedTwinkle;	//模块4故障
		////LYB 2013.04.19///////
		EDIS;
		FaultLED_CNT = 0;
	  }
		else FaultLED_CNT++;
//	SM_CMD.bit.SM1_Switch=~SM_CMD.bit.SM1_Switch;
//	SM_CMD.bit.SM2_Switch=~SM_CMD.bit.SM1_Switch;
//	SM_CMD.bit.SM3_Switch=~SM_CMD.bit.SM1_Switch;
//	SM_CMD.bit.SM4_Switch=~SM_CMD.bit.SM1_Switch;
/*
			EALLOW;
			PassbyLedOff;
			InvLedOn;
			EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
		
			if(SM_CMD.bit.SM1_Switch) SM1SwitchOn( );
				else SM1SwitchOff( );
			if(SM_CMD.bit.SM2_Switch) SM2SwitchOn( );
				else SM2SwitchOff( );
			if(SM_CMD.bit.SM3_Switch) SM3SwitchOn( );
				else SM3SwitchOff( );
			if(SM_CMD.bit.SM4_Switch) SM4SwitchOn( );
				else SM4SwitchOff( );
			EDIS;	
		*/	
//////////////test///////////////////////////////
	if(ProJudgeEn)
	{
		Vol_ProtectI( );
		if(CurSampleEn) Cur_Protect( ); //test///
	}
    // Acknowledge this interrupt to receive more interrupts from group 1
    PieCtrlRegs.PIEACK.all = 0x1000;

}




