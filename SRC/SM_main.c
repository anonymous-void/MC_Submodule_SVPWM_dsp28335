//###########################################################################
//
// Original source by: S.S.
//
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "SM_app.h"


Uint16 Fake_Download_Buf[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int i = 0;

main()
{
//	int Temp_IR;
	i=999;//xyf
	for (i = 0; i < 14; i++){
		Fake_Download_Buf[i] = 0xAAAA;
	}
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
	InitSysCtrl();
//	InitGpio();  // Skipped for this example
	InitXintf();
//	InitFlash();
// Specific clock setting for this example:


// Step 2. Initialize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.


// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
   InitPieVectTable();
	SM_GPIO_Init();
    SMGpioSet(28,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);// SYM: Comment for debugging
	InitEPwm1Gpio();// SYM: Comment for debugging
	InitEPwm2Gpio();// SYM: Comment for debugging
	InitEPwm3Gpio( );// SYM: Comment for debugging
	InitEPwm4Gpio( );// SYM: Comment for debugging
	DataInit();// SYM: Comment for debugging
	EcatDataInit();// SYM: Comment for debugging
	SM_PWM_Init();// SYM: Comment for debugging
//	LED_ALL_ON();
//	DELAY_US(300L);
//	LED_ALL_OFF( );

    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);  // SYM: Comment for debugging

 	InitFlash();  // SYM: Comment for debugging

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
 //  InitPeripherals(); // Not required for this example
    InitAdc();         // For this example, init the ADC // SYM: Comment for debugging
// Step 5. User specific code, enable interrupts:
	SM_Timer_Init();  // SYM: Comment for debugging
	SM_ExInt3_Init(); // SYM: FUCK! This shit block my timers 2016-09-19
//	SM_ADC_DATA_Init();
// Reset the watchdog counter
   ServiceDog(); // SYM: comment for debugging

// Enable the watchdog
   EALLOW;
   SysCtrlRegs.WDCR = 0x0028;
   EDIS;

// Enable global Interrupts and higher priority real-time debug events:
   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM

   EcatInit(); // SYM: Comment for debugging

//while(1);
//////LYB 2013.05.02////////////
//	*(Uint16 *)0x100102 = 0xFF00;//0x204-0x205 AL IRQ Event Mask
//	*(Uint16 *)0x100103 = 0x00FF;//0x206-0x207 AL IRQ Event Mask

//	Temp_IR = *(Uint16 *)0x00004800;/*清中断 diya*/	//
//////LYB 2013.05.02////////////
//	LED_ALL_OFF();
  for(;;)
   {  // Take ADC data and log them in SampleTable array

     // Initalize the array index.  This points to the current
     // location within the SampleTable

	ServiceDog(); // SYM: comment for debugging
	 if(PeriodFlag)
	 	{
			if(CurSampleEn)
				{
					SM_STATUS.SM_Cur_RMS = RMS_N_Fun(Cur_Sample,128,SampleSpot);
				}
			PeriodFlag = 0;
	 	}

	}
}


float32 RMS_N_Fun(float32 *pData, Uint16 N, Uint16 current)
{
	Uint16  ii=0;
	Uint16  jj=0;
	Uint16  kk=0;
	float32 shiBu = 0;
	float32 xuBu = 0;
	float32 rmsRet = 0;


    if(((current>0)||(current == 0)) && (current<N))
    {
        jj= N;
	}
	else
	{
        jj = 0;
	}


    for (ii=jj;ii<(jj+N);ii++)
    {
    	shiBu +=sin((kk*1.0/N)*2*PI)*pData[ii]; //temp bug 256.0应该用N代替
		xuBu  +=cos((kk*1.0/N)*2*PI)*pData[ii];
		kk++;
	}
	rmsRet = (sqrt(2)/N) * sqrt(shiBu*shiBu + xuBu*xuBu);

	return rmsRet;
}



//===========================================================================
// No more.
//===========================================================================


