// TI File $Revision: /main/5 $
// Checkin $Date: October 23, 2007   13:34:09 $
//###########################################################################
//
// FILE:	DSP2833x_Adc.c
//
// TITLE:	DSP2833x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "SM_app.h"

#define ADC_usDELAY  5000L


// Determine when the shift to right justify the data takes place
// Only one of these should be defined as 1.
// The other two should be defined as 0.
#define POST_SHIFT   0  // Shift results after the entire sample table is full
#define INLINE_SHIFT 1  // Shift results as the data is taken from the results regsiter
#define NO_SHIFT     0  // Do not shift the results

// ADC start parameters
#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
  #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
#endif
#if (CPU_FRQ_100MHZ)
  #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
#endif
#define ADC_CKPS   0x0   // ADC module clock = HSPCLK/1      = 25.5MHz/(1)   = 25.0 MHz
#define ADC_SHCLK  0x1   // S/H width in ADC module periods                  = 2 ADC cycle
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   1024  // Sample buffer size
#define MAX_AD_CHANEL 8
#define SM_ACQ_PS 2

//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);


    // *IMPORTANT*
	// The ADC_cal function, which  copies the ADC calibration values from TI reserved
	// OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
	// Boot ROM. If the boot ROM code is bypassed during the debug process, the
	// following function MUST be called for the ADC to function according
	// to specification. The clocks to the ADC MUST be enabled before calling this
	// function.
	// See the device data manual and/or the ADC Reference
	// Manual for more information.

	    EALLOW;

	   SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/ADC_MODCLK
 
		SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
		ADC_cal();
		EDIS;
	
    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
	// after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
	// CPU_RATE define statement in the DSP2833x_Examples.h file must
	// contain the correct CPU clock period in nanoseconds.

    AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels

	    EALLOW;

   // Specific ADC setup for this example:
   AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = MAX_AD_CHANEL;
   AdcRegs.ADCTRL1.bit.ACQ_PS = SM_ACQ_PS;
   AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
   AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode

   
   AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
   AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
   AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
   AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
   AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
   AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
   AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
   AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;
   
   AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // Setup continuous run
   AdcRegs.ADCTRL2.all = 0x2000;

    EDIS;
	
}

void SM_ADC_DATA_Init(void)
{
	Uint16 test;
	
	while (AdcRegs.ADCST.bit.INT_SEQ1== 0) {};

	test = ((AdcRegs.ADCRESULT0>>4) );
    test = ((AdcRegs.ADCRESULT1>>4) );
    test = ((AdcRegs.ADCRESULT2>>4) );
    test = ((AdcRegs.ADCRESULT3>>4) );
    test = ((AdcRegs.ADCRESULT4>>4) );
    test = ((AdcRegs.ADCRESULT5>>4) );
    test = ((AdcRegs.ADCRESULT6>>4) );
    test = ((AdcRegs.ADCRESULT7>>4) );

}


//===========================================================================
// End of file.
//===========================================================================
