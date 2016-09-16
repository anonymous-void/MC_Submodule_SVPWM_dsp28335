#include "DSP2833x_Device.h"
#include "SM_app.h"
#include "DSP2833x_ePwm_defines.h"

void  SMGpioSet(Uint16 ioNum, Uint16 fun, Uint16 upOrDown, Uint16 driect, Uint16 qsel)
{
    EALLOW;

    

    switch(ioNum)
    {
        case 0:
            GpioCtrlRegs.GPAMUX1.bit.GPIO0 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO0 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO0 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = qsel;			
		    break;
		case 1:
			GpioCtrlRegs.GPAMUX1.bit.GPIO1 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO1 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO1 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = qsel;
			break;
		case 2:
			GpioCtrlRegs.GPAMUX1.bit.GPIO2 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO2 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO2 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO2 = qsel;
			break;
	    case 3:
			GpioCtrlRegs.GPAMUX1.bit.GPIO3 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO3 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO3 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = qsel;
			break;
		case 4:
			GpioCtrlRegs.GPAMUX1.bit.GPIO4 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO4 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO4 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO4 = qsel;
			break;
		case 5:
            GpioCtrlRegs.GPAMUX1.bit.GPIO5 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO5 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO5 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = qsel;
			break;
		case 6:
            GpioCtrlRegs.GPAMUX1.bit.GPIO6 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO6 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO6 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = qsel;
			break;	
        case 7:
            GpioCtrlRegs.GPAMUX1.bit.GPIO7 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO7 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO7 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = qsel;
			break;	
        case 8:
            GpioCtrlRegs.GPAMUX1.bit.GPIO8 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO8 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO8 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO8 = qsel;
			break;	
		case 9:
            GpioCtrlRegs.GPAMUX1.bit.GPIO9 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO9 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO9 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = qsel;
			break;	
        case 10:
            GpioCtrlRegs.GPAMUX1.bit.GPIO10 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO10 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO10 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO10 = qsel;
			break;	
		case 11:
            GpioCtrlRegs.GPAMUX1.bit.GPIO11 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO11 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO11 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = qsel;
			break;	
         case 12:
            GpioCtrlRegs.GPAMUX1.bit.GPIO12 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO12 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO12 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = qsel;
			break;	
		case 13:
            GpioCtrlRegs.GPAMUX1.bit.GPIO13 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO13 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO13 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = qsel;
			break;
		case 14:
			GpioCtrlRegs.GPAMUX1.bit.GPIO14=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO14 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO14 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = qsel;
			break;
		case 15:
			GpioCtrlRegs.GPAMUX1.bit.GPIO15=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO15 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO15 = driect;
			GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = qsel;
			break;
        case 16:
            GpioCtrlRegs.GPAMUX2.bit.GPIO16 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO16 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO16 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = qsel;
			break;	
		case 17:
            GpioCtrlRegs.GPAMUX2.bit.GPIO17 =  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO17 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO17 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = qsel;
			break;
	    case 18:
			GpioCtrlRegs.GPAMUX2.bit.GPIO18=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO18= upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO18 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO18= qsel;
			break;
		case 19:
			GpioCtrlRegs.GPAMUX2.bit.GPIO19=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO19 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO19 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = qsel;
			break;
        case 20:
			GpioCtrlRegs.GPAMUX2.bit.GPIO20=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO20= upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO20 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO20= qsel;
			break;
		case 21:
			GpioCtrlRegs.GPAMUX2.bit.GPIO21=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO21 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO21 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = qsel;
			break;

		case 24:
			GpioCtrlRegs.GPAMUX2.bit.GPIO24=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO24 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO24 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = qsel;
			break;
		case 25:
			GpioCtrlRegs.GPAMUX2.bit.GPIO25=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO25 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO25 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = qsel;
			break;
		case 26:
			GpioCtrlRegs.GPAMUX2.bit.GPIO26=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO26 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO26 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = qsel;
			break;
		case 27:
			GpioCtrlRegs.GPAMUX2.bit.GPIO27=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO27 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO27 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = qsel;
			break;
		case 29:
			GpioCtrlRegs.GPAMUX2.bit.GPIO29=  fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO29 = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO29 = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = qsel;
			break;
			

		case 30:
			GpioCtrlRegs.GPAMUX2.bit.GPIO30  = fun;
			GpioCtrlRegs.GPAPUD.bit.GPIO30   = upOrDown;
			GpioCtrlRegs.GPADIR.bit.GPIO30   = driect;
			GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = qsel;

		case 32:
			GpioCtrlRegs.GPBMUX1.bit.GPIO32  = fun;
			GpioCtrlRegs.GPBPUD.bit.GPIO32   = upOrDown;
			GpioCtrlRegs.GPBDIR.bit.GPIO32   = driect;
			GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = qsel;
			break;
		case 33:
			GpioCtrlRegs.GPBMUX1.bit.GPIO33  = fun;
			GpioCtrlRegs.GPBPUD.bit.GPIO33   = upOrDown;
			GpioCtrlRegs.GPBDIR.bit.GPIO33   = driect;
			GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = qsel;
			break;


		case 48:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO48= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO48 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO48 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO48 = qsel;
		   break;

		case 49:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO49= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO49 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO49 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO49 = qsel;
		   break;

	     case 50:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO50 = fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO50 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO50 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO50 = qsel;
		   break;
	     case 51:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO51 = fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO51 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO51 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO51 = qsel;
		   break;

		case 52:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO52 = fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO52 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO52 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = qsel;
		   break;
	    case 53:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO53 = fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO53 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO53 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO53 = qsel;
		   break;
		case 54:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO54 = fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO54 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO54 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = qsel;
		   break;
		 case 55:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO55= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO55 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO55 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = qsel;
		   break;
		 case 56:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO56= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO56 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO56 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = qsel;
		   break;
		 case 57:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO57= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO57 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO57 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = qsel;
		   break;
		 case 58:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO58= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO58 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO58 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = qsel;
		   break;
		 case 59:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO59= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO59 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO59 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO59 = qsel;
		   break;
		 case 60:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO60= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO60 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO60 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO60 = qsel;
		   break;
		 case 61:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO61= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO61 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO61 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO61 = qsel;
		   break;
		 case 62:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO62= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO62 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO62 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = qsel;
		   break;
		 case 63:
		   GpioCtrlRegs.GPBMUX2.bit.GPIO63= fun;
		   GpioCtrlRegs.GPBPUD.bit.GPIO63 = upOrDown;
		   GpioCtrlRegs.GPBDIR.bit.GPIO63 = driect;
		   GpioCtrlRegs.GPBQSEL2.bit.GPIO63 = qsel;
		   break;

        default:
			break;

	}

    EDIS;
}

//GPIO输出ioNum--IO口 highOrlOw --输出高或者低
void SMGpioDataSet(Uint16 ioNum, Uint16 highOrlOw)
{
    EALLOW;
    switch(ioNum)
    {
        case 0:
			GpioDataRegs.GPADAT.bit.GPIO0 = highOrlOw;
			break;
		case 1:
            GpioDataRegs.GPADAT.bit.GPIO1 = highOrlOw;
		    break;
	    case 2:
            GpioDataRegs.GPADAT.bit.GPIO2 = highOrlOw;
		    break;
	    case 3:
            GpioDataRegs.GPADAT.bit.GPIO3 = highOrlOw;
		    break;
        case 4:
            GpioDataRegs.GPADAT.bit.GPIO4 = highOrlOw;
			break;
        case 5:
            GpioDataRegs.GPADAT.bit.GPIO5 = highOrlOw;
			break;
        case 6:
            GpioDataRegs.GPADAT.bit.GPIO6 = highOrlOw;
			break;
        case 7:
            GpioDataRegs.GPADAT.bit.GPIO7 = highOrlOw;
			break;
        case 8:
            GpioDataRegs.GPADAT.bit.GPIO8 = highOrlOw;
			break;
        case 9:
            GpioDataRegs.GPADAT.bit.GPIO9 = highOrlOw;
			break;
        case 10:
            GpioDataRegs.GPADAT.bit.GPIO10 = highOrlOw;
			break;
        case 11:
            GpioDataRegs.GPADAT.bit.GPIO11 = highOrlOw;
			break;
		case 12:
			GpioDataRegs.GPADAT.bit.GPIO12 = highOrlOw;
			break;
		case 13:
			GpioDataRegs.GPADAT.bit.GPIO13 = highOrlOw;
			break;
		case 14:
			GpioDataRegs.GPADAT.bit.GPIO14 = highOrlOw;
			break;
		case 15:
			GpioDataRegs.GPADAT.bit.GPIO15 = highOrlOw;
			break;
		case 16:
			GpioDataRegs.GPADAT.bit.GPIO16 = highOrlOw;
			break;
		case 17:
			GpioDataRegs.GPADAT.bit.GPIO17 = highOrlOw;
			break;

		case 24:
            GpioDataRegs.GPADAT.bit.GPIO24 = highOrlOw;
			break;
		case 25:
            GpioDataRegs.GPADAT.bit.GPIO25 = highOrlOw;
			break;
		case 26:
            GpioDataRegs.GPADAT.bit.GPIO26 = highOrlOw;
			break;
		case 27:
            GpioDataRegs.GPADAT.bit.GPIO27 = highOrlOw;
			break;

		case 29:
            GpioDataRegs.GPADAT.bit.GPIO29 = highOrlOw;
			break;			

			
        default:
			break; 
			
	}
	EDIS;
}

//GPIO读
Uint16 SMGpioDataRead(Uint16 ioNum)
{

    Uint16 ret = 100;
	EALLOW;
	switch(ioNum)
    {
        case 24:
			ret = GpioDataRegs.GPADAT.bit.GPIO24;
			break;
        case 25:
			ret = GpioDataRegs.GPADAT.bit.GPIO25;
			break;
        case 26:
			ret = GpioDataRegs.GPADAT.bit.GPIO26;
			break;
        case 27:
			ret = GpioDataRegs.GPADAT.bit.GPIO27;
			break;
        case 29:
			ret = GpioDataRegs.GPADAT.bit.GPIO29;
			break;
	
    	case 48:
			ret = GpioDataRegs.GPBDAT.bit.GPIO48;
			break;
		case 49:
			ret = GpioDataRegs.GPBDAT.bit.GPIO49;
			break;
		case 50:
			ret = GpioDataRegs.GPBDAT.bit.GPIO50;
			break;
		case 51:
			ret = GpioDataRegs.GPBDAT.bit.GPIO51;
			break;
		case 52:
			ret = GpioDataRegs.GPBDAT.bit.GPIO52;
			break;
		case 53:
			ret = GpioDataRegs.GPBDAT.bit.GPIO53;
			break;
		case 54:
			ret = GpioDataRegs.GPBDAT.bit.GPIO54;
			break;
		case 55:
			ret = GpioDataRegs.GPBDAT.bit.GPIO55;
			break;

		case 56:
			ret = GpioDataRegs.GPBDAT.bit.GPIO56;
			break;
		case 57:
			ret = GpioDataRegs.GPBDAT.bit.GPIO57;
			break;
		case 58:
			ret = GpioDataRegs.GPBDAT.bit.GPIO58;
			break;
		case 59:
			ret = GpioDataRegs.GPBDAT.bit.GPIO59;
			break;
		case 60:
			ret = GpioDataRegs.GPBDAT.bit.GPIO60;
			break;
		case 61:
			ret = GpioDataRegs.GPBDAT.bit.GPIO61;
			break;
		case 62:
			ret = GpioDataRegs.GPBDAT.bit.GPIO62;
			break;
		case 63:
			ret = GpioDataRegs.GPBDAT.bit.GPIO63;
			break;
		
        default:
			break; 
			
	}
	EDIS;
	return ret;

}

void MOSFETBlock(void)
{
	EALLOW;

	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	
	EPwm1Regs.AQCSFRC.bit.CSFA = 0x1;
    EPwm1Regs.AQCSFRC.bit.CSFB = 0x1;

	EPwm2Regs.AQCSFRC.bit.CSFA = 0x1;
    EPwm2Regs.AQCSFRC.bit.CSFB = 0x1;

	EPwm3Regs.AQCSFRC.bit.CSFA = 0x1;
    EPwm3Regs.AQCSFRC.bit.CSFB = 0x1;

	EPwm4Regs.AQCSFRC.bit.CSFA = 0x1;
    EPwm4Regs.AQCSFRC.bit.CSFB = 0x1;
	EDIS;	
}

void ThyristorBlock(void)
{
	

	
	SMGpioDataSet(8,GPIO_OUT_DOWN);
	SMGpioDataSet(9,GPIO_OUT_DOWN);
	SMGpioDataSet(10,GPIO_OUT_DOWN);
	SMGpioDataSet(11,GPIO_OUT_DOWN);
	
}

void ThyristorPassBy(void)
{
	
	MOSFETBlock( );
	
	SMGpioDataSet(8,GPIO_OUT_UP);
	SMGpioDataSet(9,GPIO_OUT_UP);
	SMGpioDataSet(10,GPIO_OUT_UP);
	SMGpioDataSet(11,GPIO_OUT_UP);
	
	

	
	
}

void Mosfet_Drv_Reset(void)
{
	Uint16 Drv_i=0;
	
	SMGpioDataSet(24,GPIO_OUT_DOWN);
	SMGpioDataSet(25,GPIO_OUT_DOWN);
	SMGpioDataSet(26,GPIO_OUT_DOWN);
	SMGpioDataSet(27,GPIO_OUT_DOWN);
	ServiceDog( );
	for(Drv_i=0;Drv_i<350;Drv_i++)
		{
			asm("NOP");
		}
	SMGpioDataSet(24,GPIO_OUT_UP);
	SMGpioDataSet(25,GPIO_OUT_UP);
	SMGpioDataSet(26,GPIO_OUT_UP);
	SMGpioDataSet(27,GPIO_OUT_UP);
	ServiceDog( );
	
}

void LED_ALL_ON(void)
{
	SMGpioDataSet(29,GPIO_OUT_DOWN);	
	SMGpioDataSet(12,GPIO_OUT_DOWN);
	SMGpioDataSet(13,GPIO_OUT_DOWN);
	SMGpioDataSet(14,GPIO_OUT_DOWN);
	SMGpioDataSet(15,GPIO_OUT_DOWN);
	SMGpioDataSet(16,GPIO_OUT_DOWN);
	SMGpioDataSet(17,GPIO_OUT_DOWN);
}

void LED_ALL_OFF(void)
{
	SMGpioDataSet(29,GPIO_OUT_UP);	
	SMGpioDataSet(12,GPIO_OUT_UP);
	SMGpioDataSet(13,GPIO_OUT_UP);
	SMGpioDataSet(14,GPIO_OUT_UP);
	SMGpioDataSet(15,GPIO_OUT_UP);
	SMGpioDataSet(16,GPIO_OUT_UP);
	SMGpioDataSet(17,GPIO_OUT_UP);
}


void SM_GPIO_Init(void)
{


	/////////MOSFET SM1~4//////////////

	MOSFETBlock( );

	////////Thyristor1~4//////////////////
	SMGpioSet(8,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);
	SMGpioSet(9,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);
	SMGpioSet(10,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);
	SMGpioSet(11,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);
	ThyristorBlock( );
	///////Mosfet Driver1~4 reset////////////////
	SMGpioSet(24,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);
	SMGpioSet(25,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);
	SMGpioSet(26,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);
	SMGpioSet(27,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);
	Mosfet_Drv_Reset( );
	//////LED OUTPUT/////////////////////////////
	SMGpioSet(29,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);//LED1
	SMGpioSet(12,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);//LED2
	SMGpioSet(13,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);//LED3
	SMGpioSet(14,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);//LED4
	SMGpioSet(15,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);//LED5
	SMGpioSet(16,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);//LED6
	SMGpioSet(17,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);//LED7
//	LED_ALL_ON( );
	//////////STATUS  INPUT/////////////////////
	SMGpioSet(48,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,3);//SM1_Driver_Status: 1-OK  0-fault
	SMGpioSet(49,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,3);//SM2_Driver_Status: 1-OK  0-fault
	SMGpioSet(50,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,3);//SM3_Driver_Status: 1-OK  0-fault
	SMGpioSet(51,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,3);//SM4_Driver_Status: 1-OK  0-fault
	
	SMGpioSet(52,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,3);//SM1_ShortCur_Status: 1-OK 0-ShortCurrent
	SMGpioSet(53,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,3);//SM2_ShortCur_Status: 1-OK 0-ShortCurrent
	SMGpioSet(54,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,3);//SM3_ShortCur_Status: 1-OK 0-ShortCurrent
	SMGpioSet(55,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,3);//SM4_ShortCur_Status: 1-OK 0-ShortCurrent
	
	SMGpioSet(56,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,10);//SM1_OverTemp: 1-OverTemp  0-OK
	SMGpioSet(57,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,10);//SM2_OverTemp: 1-OverTemp  0-OK
	SMGpioSet(58,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,10);//SM3_OverTemp: 1-OverTemp  0-OK
	SMGpioSet(59,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_IN,10);//SM4_OverTemp: 1-OverTemp  0-OK

	///////////EEPROM OUTPUT////////////////////////////////////////////////////////////

	SMGpioSet(30,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);
	SMGpioSet(33,GPIO_FUN_00,GPIO_R_UP,GPIO_DIR_OUT,3);	

//////////////////////////////////////////////////////////////////////////////////////////////

	


}


void GPIOtoDI(void)
{
	DI_CHECK.DI_NEW.bit.Drv1_STATUS = SMGpioDataRead(48);
	DI_CHECK.DI_NEW.bit.Drv2_STATUS = SMGpioDataRead(49);
	DI_CHECK.DI_NEW.bit.Drv3_STATUS = SMGpioDataRead(50);
	DI_CHECK.DI_NEW.bit.Drv4_STATUS = SMGpioDataRead(51);

	DI_CHECK.DI_NEW.bit.SM1_ShortCur = SMGpioDataRead(52);
	DI_CHECK.DI_NEW.bit.SM2_ShortCur = SMGpioDataRead(53);
	DI_CHECK.DI_NEW.bit.SM3_ShortCur = SMGpioDataRead(54);
	DI_CHECK.DI_NEW.bit.SM4_ShortCur = SMGpioDataRead(55);

	DI_CHECK.DI_NEW.bit.SM1_OverTemp = SMGpioDataRead(56);
	DI_CHECK.DI_NEW.bit.SM2_OverTemp = SMGpioDataRead(57);
	DI_CHECK.DI_NEW.bit.SM3_OverTemp = SMGpioDataRead(58);
	DI_CHECK.DI_NEW.bit.SM4_OverTemp = SMGpioDataRead(59);
	

}

void DIUpData(void)
{

	GPIOtoDI( );

	//////////
	if( SM_STATUS.DI_STATUS.bit.Drv1_STATUS != DI_CHECK.DI_NEW.bit.Drv1_STATUS )                                    //发生变化后
		{
		DI_CHECK.Drv1_CNT++;
		if( DI_CHECK.Drv1_CNT >= XiaodouTime )                                   
			{
			SM_STATUS.DI_STATUS.bit.Drv1_STATUS = DI_CHECK.DI_NEW.bit.Drv1_STATUS ;                                  //设置为新值                               
			DI_CHECK.Drv1_CNT = 0;
			}
		}
	else
		DI_CHECK.Drv1_CNT = 0;
	/////////////
	if( SM_STATUS.DI_STATUS.bit.Drv2_STATUS != DI_CHECK.DI_NEW.bit.Drv2_STATUS )                                    //发生变化后
		{
		DI_CHECK.Drv2_CNT++;
		if( DI_CHECK.Drv2_CNT >= XiaodouTime )                                   
			{
			SM_STATUS.DI_STATUS.bit.Drv2_STATUS = DI_CHECK.DI_NEW.bit.Drv2_STATUS ;                                  //设置为新值                               
			DI_CHECK.Drv2_CNT = 0;
			}
		}
	else
		DI_CHECK.Drv2_CNT = 0;
	////////////////////
	if( SM_STATUS.DI_STATUS.bit.Drv3_STATUS != DI_CHECK.DI_NEW.bit.Drv3_STATUS )                                    //发生变化后
		{
		DI_CHECK.Drv3_CNT++;
		if( DI_CHECK.Drv3_CNT >= XiaodouTime )                                   
			{
			SM_STATUS.DI_STATUS.bit.Drv3_STATUS = DI_CHECK.DI_NEW.bit.Drv3_STATUS ;                                  //设置为新值                               
			DI_CHECK.Drv3_CNT = 0;
			}
		}
	else
		DI_CHECK.Drv3_CNT = 0;
	/////////////////////////
	if( SM_STATUS.DI_STATUS.bit.Drv4_STATUS != DI_CHECK.DI_NEW.bit.Drv4_STATUS )                                    //发生变化后
		{
		DI_CHECK.Drv4_CNT++;
		if( DI_CHECK.Drv4_CNT >= XiaodouTime )                                   
			{
			SM_STATUS.DI_STATUS.bit.Drv4_STATUS = DI_CHECK.DI_NEW.bit.Drv4_STATUS ;                                  //设置为新值                               
			DI_CHECK.Drv4_CNT = 0;
			}
		}
	else
		DI_CHECK.Drv4_CNT = 0;
	///////////////////////////
	if(SM_STATUS.DI_STATUS.bit.SM1_ShortCur != DI_CHECK.DI_NEW.bit.SM1_ShortCur)
		{
		DI_CHECK.SM1_ShortCur_CNT++;
		if(DI_CHECK.SM1_ShortCur_CNT >= XiaodouTime)
			{
				SM_STATUS.DI_STATUS.bit.SM1_ShortCur = DI_CHECK.DI_NEW.bit.SM1_ShortCur;
				DI_CHECK.SM1_ShortCur_CNT=0;
			}
		}
	else 
		DI_CHECK.SM1_ShortCur_CNT = 0;
	///////////////////////////
	if(SM_STATUS.DI_STATUS.bit.SM2_ShortCur != DI_CHECK.DI_NEW.bit.SM2_ShortCur)
		{
		DI_CHECK.SM2_ShortCur_CNT++;
		if(DI_CHECK.SM2_ShortCur_CNT >= XiaodouTime)
			{
				SM_STATUS.DI_STATUS.bit.SM2_ShortCur = DI_CHECK.DI_NEW.bit.SM2_ShortCur;
				DI_CHECK.SM2_ShortCur_CNT=0;
			}
		}
	else 
		DI_CHECK.SM2_ShortCur_CNT = 0;
	///////////////////////////
	if(SM_STATUS.DI_STATUS.bit.SM3_ShortCur != DI_CHECK.DI_NEW.bit.SM3_ShortCur)
		{
		DI_CHECK.SM3_ShortCur_CNT++;
		if(DI_CHECK.SM3_ShortCur_CNT >= XiaodouTime)
			{
				SM_STATUS.DI_STATUS.bit.SM3_ShortCur = DI_CHECK.DI_NEW.bit.SM3_ShortCur;
				DI_CHECK.SM3_ShortCur_CNT=0;
			}
		}
	else 
		DI_CHECK.SM3_ShortCur_CNT = 0;

	///////////////////////////
	if(SM_STATUS.DI_STATUS.bit.SM4_ShortCur != DI_CHECK.DI_NEW.bit.SM4_ShortCur)
		{
		DI_CHECK.SM4_ShortCur_CNT++;
		if(DI_CHECK.SM4_ShortCur_CNT >= XiaodouTime)
			{
				SM_STATUS.DI_STATUS.bit.SM4_ShortCur = DI_CHECK.DI_NEW.bit.SM4_ShortCur;
				DI_CHECK.SM4_ShortCur_CNT=0;
			}
		}
	else 
		DI_CHECK.SM4_ShortCur_CNT = 0;	
	///////////////////////////
	if(SM_STATUS.DI_STATUS.bit.SM1_OverTemp != DI_CHECK.DI_NEW.bit.SM1_OverTemp)
		{
			DI_CHECK.SM1_OverTemp_CNT++;
			if(DI_CHECK.SM1_OverTemp_CNT >= XiaodouTime)
				{
					SM_STATUS.DI_STATUS.bit.SM1_OverTemp = DI_CHECK.DI_NEW.bit.SM1_OverTemp;
					DI_CHECK.SM1_OverTemp_CNT = 0;
				}
		}
	else
		DI_CHECK.SM1_OverTemp_CNT = 0;
	////////////////////////////
	if(SM_STATUS.DI_STATUS.bit.SM2_OverTemp != DI_CHECK.DI_NEW.bit.SM2_OverTemp)
		{
			DI_CHECK.SM2_OverTemp_CNT++;
			if(DI_CHECK.SM2_OverTemp_CNT >= XiaodouTime)
				{
					SM_STATUS.DI_STATUS.bit.SM2_OverTemp = DI_CHECK.DI_NEW.bit.SM2_OverTemp;
					DI_CHECK.SM2_OverTemp_CNT = 0;
				}
		}
	else
		DI_CHECK.SM2_OverTemp_CNT = 0;
	////////////////////////////
	if(SM_STATUS.DI_STATUS.bit.SM3_OverTemp != DI_CHECK.DI_NEW.bit.SM3_OverTemp)
		{
			DI_CHECK.SM3_OverTemp_CNT++;
			if(DI_CHECK.SM3_OverTemp_CNT >= XiaodouTime)
				{
					SM_STATUS.DI_STATUS.bit.SM3_OverTemp = DI_CHECK.DI_NEW.bit.SM3_OverTemp;
					DI_CHECK.SM3_OverTemp_CNT = 0;
				}
		}
	else
		DI_CHECK.SM3_OverTemp_CNT = 0;
	////////////////////////////
	if(SM_STATUS.DI_STATUS.bit.SM4_OverTemp != DI_CHECK.DI_NEW.bit.SM4_OverTemp)
		{
			DI_CHECK.SM4_OverTemp_CNT++;
			if(DI_CHECK.SM4_OverTemp_CNT >= XiaodouTime)
				{
					SM_STATUS.DI_STATUS.bit.SM4_OverTemp = DI_CHECK.DI_NEW.bit.SM4_OverTemp;
					DI_CHECK.SM4_OverTemp_CNT = 0;
				}
		}
	else
		DI_CHECK.SM4_OverTemp_CNT = 0;

	
}




