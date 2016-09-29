#include "DSP2833x_Device.h"
#include "SM_app.h"
#include "DSP2833x_ePwm_defines.h"
#include "SYM_app.h"


//Uint16 i;
Uint16 gi_polarityFlag = 0;
const Uint16 gi_switching_freq = 10000; // [Hz]
Uint16 gi_switching_cycle = 1000000 / gi_switching_freq; // In micro-second, [us].


void SM_Timer_Init(void)
{
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TINT0 =  &cpu_timer0_isr;
   PieVectTable.XINT13 = &cpu_timer1_isr;
   PieVectTable.TINT2 =  &cpu_timer2_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

   InitCpuTimers();   // For this example, only initialize the Cpu Timers

   ConfigCpuTimer(&CpuTimer0, 150, gi_switching_cycle); // Used for fake Xint, debug only
   ConfigCpuTimer(&CpuTimer1, 150, gi_switching_cycle);// SYM: this macro defined in SYM_app.h
   ConfigCpuTimer(&CpuTimer2,150,1000);///1ms中断一次

// To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
// below settings must also be updated.

	StartCpuTimer0();
	StartCpuTimer1();
	StartCpuTimer2();

// Enable CPU int1 which is connected to CPU-Timer 0

   IER |= M_INT1;
   IER |= M_INT13;
   IER |= M_INT14;
// Enable TINT0 in the PIE: Group 1 interrupt 7
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

}


interrupt void cpu_timer0_isr(void)
{
//SYM: Offline test use only
//	sym_Ecat_DATA_Codec();
//	sym_Ecat_DATA_Decode();
//	sym_Matrix_Generation(); // Calc the vector and duty cycle of one switching period
//	sym_Cpu_Timer_Setup_In_Xint(); // Initialize the PRD and Counter Reg of Timer
//	SM_CMD.bit.Deblock = 1; // SYM: Debug only, mannual deblock
//	sym_CMD_Handwith();
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
//SYM: Offline test use only

////    CpuTimer0Regs.TCR.bit.TIF=1;  //SYM: write 1 to it to clear the Timer Interrupt Flag
////    CpuTimer0Regs.TCR.bit.TRB=1;
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

//	sym_Branch_Voltage_Out(gi_test_vect[gi_seq_cnt]);
//	gi_seq_cnt ++;
//	if (gi_seq_cnt >= 8)
//		gi_seq_cnt = 0;



//// ePWM software force output test code start
//	sym_Branch_Voltage_Out(gi_test_vect[gi_seq_cnt]);
//	gi_seq_cnt ++ ;
//	if (gi_seq_cnt >= 8)
//		gi_seq_cnt = 0;
//// Acknowledge this interrupt to receive more interrupts from group 1
////	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
//// ePWM software force output test code end

//	StopCpuTimer1();
//	gi_seq_cnt = 1;
//	CpuTimer1Regs.PRD.all = 150 * gm_SWITHCING_PRD * go_SYM_MC_SVPWM_MOD.duty[gi_seq_cnt];
//	CpuTimer1Regs.TIM.all = 150 * gm_SWITHCING_PRD * go_SYM_MC_SVPWM_MOD.duty[0];
//	sym_Branch_Voltage_Out(go_SYM_MC_SVPWM_MOD.voltage_out[0]);
//	gi_polarity_flag = 0;
//	StartCpuTimer1();

//// Acknowledge this interrupt to receive more interrupts from group 1
//	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


interrupt void cpu_timer1_isr(void)  // SYM: Used for Variable step
{
    CpuTimer1Regs.PRD.all = 150 * gm_SWITHCING_PRD * go_SYM_MC_SVPWM_MOD.duty[gi_seq_cnt]; // Load next period's PRD
    sym_Branch_Voltage_Out(go_SYM_MC_SVPWM_MOD.voltage_out[gi_seq_cnt]);

    gi_seq_cnt ++;
    if (gi_seq_cnt >= 5)
    	gi_seq_cnt = 0;
    CpuTimer1Regs.TCR.bit.TIF=1;  //SYM: write 1 to it to clear the Timer Interrupt Flag
//    CpuTimer1Regs.TCR.bit.TIE = 0;
//    CpuTimer1Regs.TCR.bit.TRB=1;

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




