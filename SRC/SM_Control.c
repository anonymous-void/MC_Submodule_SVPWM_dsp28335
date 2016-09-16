#include "DSP2833x_Device.h"
#include "SM_app.h"
#include "DSP2833x_ePwm_defines.h"



Uint16 CMD_Handwith(void) ///主控制器发送命令处理
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
			MOSFETBlock( );
			ThyristorBlock( );
			return 0;
		}

	
	if ( (SM_CMD.bit.Deblock == 1)&&(SM_STATUS.ECAT_UP.SM12_fault.all==0)  //逆变状态
			&&(SM_STATUS.ECAT_UP.SM34_fault.all == 0) )
		{
			ThyristorBlock( );
			EALLOW;
			EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm1Regs.AQCSFRC.bit.CSFA = 0x0;
			EPwm1Regs.AQCSFRC.bit.CSFB = 0x0;
	    	EPwm2Regs.AQCSFRC.bit.CSFA = 0x0;
            EPwm2Regs.AQCSFRC.bit.CSFB = 0x0;
	    	EPwm3Regs.AQCSFRC.bit.CSFA = 0x0;
            EPwm3Regs.AQCSFRC.bit.CSFB = 0x0;
	    	EPwm4Regs.AQCSFRC.bit.CSFA = 0x0;
	        EPwm4Regs.AQCSFRC.bit.CSFB = 0x0;
			PassbyLedOff;
			InvLedOn;
			EDIS;
			return 1;	
		}
	else
		{
			EALLOW;
			PassbyLedOff;
			InvLedOff;
			EDIS;
			MOSFETBlock( );
			ThyristorBlock( );
			return 0;

		}
	return 0;
}



