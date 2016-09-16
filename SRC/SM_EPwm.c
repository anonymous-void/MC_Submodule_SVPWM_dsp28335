#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "DSP2833x_ePwm_defines.h" 
#include "SM_app.h"



void InitEPwm1(void)
{



 // Setup TBCLK
   EPwm1Regs.TBPRD = 3750;           // Set timer period 801 TBCLKs
   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm1Regs.TBCTR = 0x0000;                      // Clear counter
   
   // Set Compare values
   EPwm1Regs.CMPA.half.CMPA = 0;     // Set compare A value
   EPwm1Regs.CMPB = 0;               // Set Compare B value
   
   // Setup counter mode
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
//   EPwm1Regs.TBCTL.bit.PHSDIR = TB_UP;
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV4;
   EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
   EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;

   // Setup shadowing
   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // Load on Zero
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;   


   // Set actions
   EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on event A, up count
   EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;           // Clear PWM1A on event A, down count

   EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;            // Set PWM1B on event B, up count
   EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;          // Clear PWM1B on event B, down count




      // Active Low PWMs - Setup Deadband
   //EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm1Regs.DBCTL.bit.OUT_MODE = 0x3;//DB_DISABLE;
   EPwm1Regs.DBCTL.bit.POLSEL = 0x1;//DB_ACTV_HIC;
   EPwm1Regs.DBCTL.bit.IN_MODE = 0x1;//DBA_ALL;
   EPwm1Regs.DBRED = 150;
   EPwm1Regs.DBFED = 150;


//   EPwm1Regs.AQCSFRC.bit.CSFA = 0x1;
//   EPwm1Regs.AQCSFRC.bit.CSFB = 0x1;


/*

  // Interrupt where we will change the Deadband
  // EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
  // EPwm1Regs.ETSEL.bit.INTEN = 0;                // Enable INT
  // EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

*/
}


void InitEPwm2(void)
{

   
   // Setup TBCLK
	 EPwm2Regs.TBPRD = 3750;		   // Set timer period 801 TBCLKs
	 EPwm2Regs.TBPHS.half.TBPHS = 3750;			// Phase is 0
	 EPwm2Regs.TBCTR = 0x0000;						// Clear counter
	 
	 // Set Compare values
	 EPwm2Regs.CMPA.half.CMPA = 0;	 // Set compare A value
	 EPwm2Regs.CMPB = 0;				 // Set Compare B value
	 
	 // Setup counter mode
	 EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
	 EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;
	 EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;		// Disable phase loading
	 EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;		// Clock ratio to SYSCLKOUT
	 EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV4;
	 EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	 EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	 // Setup shadowing
	 EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	 EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	 EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;	// Load on Zero
	 EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;	 
   
   
	 // Set actions
	 EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR; 			// Set PWM1A on event A, up count
	 EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;			// Clear PWM1A on event A, down count
   
	 EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR; 			// Set PWM1B on event B, up count
	 EPwm2Regs.AQCTLB.bit.CBD = AQ_SET;			// Clear PWM1B on event B, down count
   
   
   
   
		// Active Low PWMs - Setup Deadband
	 //EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	 EPwm2Regs.DBCTL.bit.OUT_MODE = 0x3;
	 EPwm2Regs.DBCTL.bit.POLSEL = 0x1;
	 EPwm2Regs.DBCTL.bit.IN_MODE = 0x1;
	 EPwm2Regs.DBRED = 150;//150
	 EPwm2Regs.DBFED = 150;
   
   
//	 EPwm2Regs.AQCSFRC.bit.CSFA = 0x1;
//	 EPwm2Regs.AQCSFRC.bit.CSFB = 0x1;

   

   // Interrupt where we will modify the deadband
  // EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Select INT on Zero event
  // EPwm2Regs.ETSEL.bit.INTEN = 0;                 // Enable INT
  // EPwm2Regs.ETPS.bit.INTPRD = ET_3RD;            // Generate INT on 3rd event

}

void InitEPwm3(void)
{

   
   // Setup TBCLK
	 EPwm3Regs.TBPRD = 3750;		   // Set timer period 801 TBCLKs
	 EPwm3Regs.TBPHS.half.TBPHS = 1875;			// Phase is 0
	 EPwm3Regs.TBCTR = 0x0000;						// Clear counter
	 
	 // Set Compare values
	 EPwm3Regs.CMPA.half.CMPA = 0;	 // Set compare A value
	 EPwm3Regs.CMPB = 0;				 // Set Compare B value
	 
	 // Setup counter mode
	 EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
	 EPwm3Regs.TBCTL.bit.PHSDIR = TB_DOWN;
	 EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;		// Disable phase loading
	 EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;		// Clock ratio to SYSCLKOUT
	 EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV4;
	 EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	 EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	 // Setup shadowing
	 EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	 EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	 EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;	// Load on Zero
	 EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;	 
   
   
	 // Set actions
	 EPwm3Regs.AQCTLA.bit.CAU = AQ_SET; 			// Set PWM1A on event A, up count
	 EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;			// Clear PWM1A on event A, down count
   
	 EPwm3Regs.AQCTLB.bit.CBU = AQ_SET; 			// Set PWM1B on event B, up count
	 EPwm3Regs.AQCTLB.bit.CBD = AQ_CLEAR;			// Clear PWM1B on event B, down count
   
   
   
   
		// Active Low PWMs - Setup Deadband
	 //EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	 EPwm3Regs.DBCTL.bit.OUT_MODE = 0x3;
	 EPwm3Regs.DBCTL.bit.POLSEL = 0x1;
	 EPwm3Regs.DBCTL.bit.IN_MODE = 0x1;
	 EPwm3Regs.DBRED = 150;
	 EPwm3Regs.DBFED = 150;
   
   
//	 EPwm3Regs.AQCSFRC.bit.CSFA = 0x1;
//	 EPwm3Regs.AQCSFRC.bit.CSFB = 0x1;


   // Interrupt where we will change the deadband
  // EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;       // Select INT on Zero event
  // EPwm3Regs.ETSEL.bit.INTEN = 0;                  // Enable INT
   // EPwm3Regs.ETPS.bit.INTPRD = ET_3RD;             // Generate INT on 3rd event

}

void InitEPwm4(void)
{
   
   // Setup TBCLK
	 EPwm4Regs.TBPRD = 3750;		   // Set timer period 801 TBCLKs
	 EPwm4Regs.TBPHS.half.TBPHS = 1875;			// Phase is 0
	 EPwm4Regs.TBCTR = 0x0000;						// Clear counter
	 
	 // Set Compare values
	 EPwm4Regs.CMPA.half.CMPA = 0;	 // Set compare A value
	 EPwm4Regs.CMPB = 0;				 // Set Compare B value
	 
	 // Setup counter mode
	 EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
	 EPwm4Regs.TBCTL.bit.PHSDIR = TB_UP;
	 EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;		// Disable phase loading
	 EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;		// Clock ratio to SYSCLKOUT
	 EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV4;
	 EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	 EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   
	 // Setup shadowing
	 EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	 EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	 EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;	// Load on Zero
	 EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;	 
   
   
	 // Set actions
	 EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR; 			// Set PWM1A on event A, up count
	 EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;			// Clear PWM1A on event A, down count
   
	 EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR; 			// Set PWM1B on event B, up count
	 EPwm4Regs.AQCTLB.bit.CBD = AQ_SET;			// Clear PWM1B on event B, down count
   
   
   
   
		// Active Low PWMs - Setup Deadband
	 //EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	 EPwm4Regs.DBCTL.bit.OUT_MODE = 0x3;
	 EPwm4Regs.DBCTL.bit.POLSEL = 0x1;
	 EPwm4Regs.DBCTL.bit.IN_MODE = 0x1;
	 EPwm4Regs.DBRED = 150;
	 EPwm4Regs.DBFED = 150;
   
   
//	 EPwm4Regs.AQCSFRC.bit.CSFA = 0x1;
//	 EPwm4Regs.AQCSFRC.bit.CSFB = 0x1;

  

   // Interrupt where we will change the deadband
  // EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;       // Select INT on Zero event
  // EPwm4Regs.ETSEL.bit.INTEN = 0;                  // Enable INT
   // EPwm4Regs.ETPS.bit.INTPRD = ET_3RD;             // Generate INT on 3rd event

}

void SM_PWM_Init(void)
{
	EALLOW;
	
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;

	InitEPwm1( );
	InitEPwm2( );
	InitEPwm3( );
	InitEPwm4( );

	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;
}

void SM1SwitchOn(void)
{

	EALLOW;	
   EPwm1Regs.AQCSFRC.bit.CSFA = 1;
   EPwm1Regs.AQCSFRC.bit.CSFB = 2;
	EDIS;	
	
}

void SM1SwitchOff(void)
{
   EALLOW;
   EPwm1Regs.AQCSFRC.bit.CSFA = 2;
   EPwm1Regs.AQCSFRC.bit.CSFB = 1;
   EDIS;

	
	
}

void SM2SwitchOn(void)
{
	EALLOW;
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
    EPwm2Regs.AQCSFRC.bit.CSFB = 2;
	EDIS;	
}

void SM2SwitchOff(void)
{
   EALLOW;
   EPwm2Regs.AQCSFRC.bit.CSFA = 2;
   EPwm2Regs.AQCSFRC.bit.CSFB = 1;
   EDIS;	
	
}

void SM3SwitchOn(void)
{
	EALLOW;
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
    EPwm3Regs.AQCSFRC.bit.CSFB = 2;
	EDIS;
	
	
}

void SM3SwitchOff(void)
{
	EALLOW;
	EPwm3Regs.AQCSFRC.bit.CSFA = 2;
    EPwm3Regs.AQCSFRC.bit.CSFB = 1;
	EDIS;	
	
}

void SM4SwitchOn(void)
{
	EALLOW;
	EPwm4Regs.AQCSFRC.bit.CSFA = 1;
    EPwm4Regs.AQCSFRC.bit.CSFB = 2;
	EDIS;
	
}

void SM4SwitchOff(void)
{
	EALLOW;
	EPwm4Regs.AQCSFRC.bit.CSFA = 2;
    EPwm4Regs.AQCSFRC.bit.CSFB = 1;
	EDIS;
	
}


