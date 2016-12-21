/*
 * SYM_Control.c
 *
 *  Created on: 2016年9月18日
 *      Author: voidman
 */

#include "DSP2833x_Device.h"
#include "SM_app.h"
#include "SYM_app.h"
#include "DSP2833x_ePwm_defines.h"

Uint16 sym_CMD_Handwith(void) ///主控制器发送命令处理
{
	if(SM_CMD.bit.Reset == 1)   ///////////复位命令处理/////////////////////
	{
		LED_ALL_OFF( );
		SM_GPIO_Init( );
		DataReset( );
		return 0;
	}

	if((SM_STATUS.ECAT_UP.SM12_fault.all)||(SM_STATUS.ECAT_UP.SM34_fault.all))   //故障状态处理
	{

		PassbyLedOff;
		InvLedOff;
		sym_MOSFETBlock( );
		ThyristorBlock( );
		return 0;
	}

	if ( (go_SYM_ECAT_DOWN_DATA.SM_CMD.bit.deblock == 1)&&(SM_STATUS.ECAT_UP.SM12_fault.all==0)  //逆变状态
			&&(SM_STATUS.ECAT_UP.SM34_fault.all == 0) )
	{
		EALLOW;
		sym_Cpu_Timer_Setup_In_Xint(); // Initialize the PRD and Counter Reg of Timer
		StartCpuTimer1();
		StartCpuTimer0();

		PassbyLedOff;
		InvLedOn;
		EDIS;
		return 1;
	}
	else
	{
		EALLOW;
		StopCpuTimer1();
		StopCpuTimer0();
		PassbyLedOff;
		InvLedOff;
		EDIS;
		sym_MOSFETBlock( );
		return 0;

	}
}


void sym_SM1SwitchOn(void)
{
	EALLOW;
   EPwm1Regs.AQCSFRC.bit.CSFA = 1;
   EPwm1Regs.AQCSFRC.bit.CSFB = 2;
	EDIS;
}

void sym_SM1SwitchOff(void)
{
   EALLOW;
   EPwm1Regs.AQCSFRC.bit.CSFA = 2;
   EPwm1Regs.AQCSFRC.bit.CSFB = 1;
   EDIS;
}

void sym_SM2SwitchOn(void)
{
	EALLOW;
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
    EPwm2Regs.AQCSFRC.bit.CSFB = 2;
	EDIS;
}

void sym_SM2SwitchOff(void)
{
   EALLOW;
   EPwm2Regs.AQCSFRC.bit.CSFA = 2;
   EPwm2Regs.AQCSFRC.bit.CSFB = 1;
   EDIS;

}

void sym_SM3SwitchOn(void)
{
	EALLOW;
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
    EPwm3Regs.AQCSFRC.bit.CSFB = 2;
	EDIS;


}

void sym_SM3SwitchOff(void)
{
	EALLOW;
	EPwm3Regs.AQCSFRC.bit.CSFA = 2;
    EPwm3Regs.AQCSFRC.bit.CSFB = 1;
	EDIS;

}

void sym_SM4SwitchOn(void)
{
	EALLOW;
	EPwm4Regs.AQCSFRC.bit.CSFA = 1;
    EPwm4Regs.AQCSFRC.bit.CSFB = 2;
	EDIS;

}

void sym_SM4SwitchOff(void)
{
	EALLOW;
	EPwm4Regs.AQCSFRC.bit.CSFA = 2;
    EPwm4Regs.AQCSFRC.bit.CSFB = 1;
	EDIS;

}

void sym_MOSFETBlock(void)
{
	EALLOW;

//	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
//	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
//	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
//	EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;

	EPwm1Regs.AQCSFRC.bit.CSFA = 0x01;//<sprug04a> P106, 0x01: force low, shutdown all MOSFETs
    EPwm1Regs.AQCSFRC.bit.CSFB = 0x01;

	EPwm2Regs.AQCSFRC.bit.CSFA = 0x01;
    EPwm2Regs.AQCSFRC.bit.CSFB = 0x01;

	EPwm3Regs.AQCSFRC.bit.CSFA = 0x01;
    EPwm3Regs.AQCSFRC.bit.CSFB = 0x01;

	EPwm4Regs.AQCSFRC.bit.CSFA = 0x01;
    EPwm4Regs.AQCSFRC.bit.CSFB = 0x01;
	EDIS;
}

void sym_Branch_Voltage_Out(int target_level)
{
	if (target_level == 0){
		// short circuit
		sym_SM1SwitchOn();
		sym_SM2SwitchOn();
		sym_SM3SwitchOn();
		sym_SM4SwitchOn();
	}
	else if (target_level == -1){
		// +Vcap
		sym_SM1SwitchOn(); // 1st H-bridge output -Vcap, 2ed SC
		sym_SM2SwitchOff();

		sym_SM3SwitchOn();
		sym_SM4SwitchOn();
	}
	else if (target_level == -2){
		// +2Vcap
		sym_SM1SwitchOn(); // Both Output -Vcap
		sym_SM2SwitchOff();
		sym_SM3SwitchOn();
		sym_SM4SwitchOff();
	}
	else if (target_level == 1){
		// -Vcap
		sym_SM1SwitchOff(); // 1st H-bridge output +Vcap, 2ed SC
		sym_SM2SwitchOn();

		sym_SM3SwitchOn();
		sym_SM4SwitchOn();
	}
	else if (target_level == 2){
		// -2Vcap
		sym_SM1SwitchOff();
		sym_SM2SwitchOn();
		sym_SM3SwitchOff();
		sym_SM4SwitchOn();
	}
	else{
		//Block
		sym_MOSFETBlock();
	}
}

void sym_Matrix_Generation(void)
{
/*
Description: This subroutine does not generate the whole matrix, but generate the specific element which
			would be used in this module.
*/
	int i = 0;
	go_SYM_MC_SVPWM_MOD.duty[0] = go_SYM_ECAT_DOWN_DATA_DECODED.duty[0];
	go_SYM_MC_SVPWM_MOD.duty[1] = go_SYM_ECAT_DOWN_DATA_DECODED.duty[1];
	go_SYM_MC_SVPWM_MOD.duty[2] = go_SYM_ECAT_DOWN_DATA_DECODED.duty[2];
	go_SYM_MC_SVPWM_MOD.duty[3] = go_SYM_ECAT_DOWN_DATA_DECODED.duty[3];
	go_SYM_MC_SVPWM_MOD.duty[4] = 1 - go_SYM_MC_SVPWM_MOD.duty[0] - go_SYM_MC_SVPWM_MOD.duty[1] - go_SYM_MC_SVPWM_MOD.duty[2] - go_SYM_MC_SVPWM_MOD.duty[3];
	if (go_SYM_MC_SVPWM_MOD.duty[4] < 0) // Actually, the 5th duty cycle need not to be calc, it could automatically realized by cpu_timerer and external interrupt
		go_SYM_MC_SVPWM_MOD.duty[4] = 0;

	for (i = 0; i < 5; i++)
	{
#ifdef UA
		if (gi_Tree[go_SYM_ECAT_DOWN_DATA_DECODED.tree[i]][0][0] == 1){// If tree do not mask this submodule
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vnum][0] - \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vnum][0];
		}
		else{
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = INF;
		}
#elif defined UB
		if (gi_Tree[go_SYM_ECAT_DOWN_DATA_DECODED.tree[i]][0][1] == 1){// If tree do not mask this submodule
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vnum][0] - \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vnum][1];
		}
		else{
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = INF;
		}
#elif defined UC
		if (gi_Tree[go_SYM_ECAT_DOWN_DATA_DECODED.tree[i]][0][2] == 1){// If tree do not mask this submodule
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vnum][0] - \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vnum][2];
		}
		else{
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = INF;
		}
#elif defined VA
		if (gi_Tree[go_SYM_ECAT_DOWN_DATA_DECODED.tree[i]][1][0] == 1){// If tree do not mask this submodule
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vnum][1] - \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vnum][0];
		}
		else{
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = INF;
		}
#elif defined VB
		if (gi_Tree[go_SYM_ECAT_DOWN_DATA_DECODED.tree[i]][1][1] == 1){// If tree do not mask this submodule
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vnum][1] - \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vnum][1];
		}
		else{
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = INF;
		}
#elif defined VC
		if (gi_Tree[go_SYM_ECAT_DOWN_DATA_DECODED.tree[i]][1][2] == 1){// If tree do not mask this submodule
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vnum][1] - \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vnum][2];
		}
		else{
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = INF;
		}
#elif defined WA
		if (gi_Tree[go_SYM_ECAT_DOWN_DATA_DECODED.tree[i]][2][0] == 1){// If tree do not mask this submodule
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vnum][2] - \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vnum][0];
		}
		else{
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = INF;
		}
#elif defined WB
		if (gi_Tree[go_SYM_ECAT_DOWN_DATA_DECODED.tree[i]][2][1] == 1){// If tree do not mask this submodule
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vnum][2] - \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vnum][1];
		}
		else{
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = INF;
		}
#elif defined WC
		if (gi_Tree[go_SYM_ECAT_DOWN_DATA_DECODED.tree[i]][2][2] == 1){// If tree do not mask this submodule
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vnum][2] - \
			gi_Vector[go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vtype - 1][go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vnum][2];
		}
		else{
			go_SYM_MC_SVPWM_MOD.voltage_out[i] = INF;
		}
#endif
	}
}

void sym_Cpu_Timer_Setup_In_Xint(void)
{
	StopCpuTimer1();

//    CpuTimer1Regs.PRD.all = 150 * gm_SWITHCING_PRD * go_SYM_MC_SVPWM_MOD.duty[gi_seq_cnt]; // Load next period's PRD
//    sym_Branch_Voltage_Out(go_SYM_MC_SVPWM_MOD.voltage_out[gi_seq_cnt]);
//
//    gi_seq_cnt ++;
//    if (gi_seq_cnt >= 5)
//    	gi_seq_cnt = 0;

	gi_seq_cnt = 1;
	CpuTimer1Regs.PRD.all = 150 * gm_SWITHCING_PRD * go_SYM_MC_SVPWM_MOD.duty[gi_seq_cnt];
	CpuTimer1Regs.TIM.all = 150 * gm_SWITHCING_PRD * go_SYM_MC_SVPWM_MOD.duty[0];
	sym_Branch_Voltage_Out(go_SYM_MC_SVPWM_MOD.voltage_out[0]);
	gi_polarity_flag = 0;
	StartCpuTimer1();
}
