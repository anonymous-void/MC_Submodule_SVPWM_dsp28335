#include "DSP2833x_Device.h"
#include "SM_app.h"

//int S=0;
//int max=0;
int old;
//int erro=0;
//int maxerro=0;
int In=0;
Uint16 EcatSatusRead(void)
{
    Uint16 ret = 100;
	
    ret  = *(ECAT_START_ADDR+0x800);

    return ret;
}


Uint16 ReadEcatAddr(void)
{
    Uint16 ret = 100;
	
    ret  = *(ECAT_START_ADDR+0x09);

    return ret;

}


void EcatInit(void)
{
	Uint16 i=0;
	Uint16 ret=0;
	Uint16 *pRead;
	pRead =  ECAT_START_ADDR+0x980;//ECAT_DOWNLOAD_DATA_OFFSET
	for(i=0; i<=ECAT_UP_DATA_LENGTH; i++)
	{
		ret = *(pRead++);
		ret = ret;
	}
	ret=0;
	 pRead = ECAT_START_ADDR+0x900;
	for(i=0; i<=ECAT_DOWN_DATA_LENGTH; i++)
		{
			*(pRead++) = ret;
			ret = ret;
		}
		
}

void EcatDataInit(void) 
{
	Uint16 i=0;
	Uint16 ret;
	Uint16 *pRead;

	
	pRead = ECAT_START_ADDR + ECAT_DOWNLOAD_DATA_OFFSET;
	for(i=0;i<=ECAT_DOWN_DATA_LENGTH;i++) 
		//ret = *(pRead++);
		*(pRead++) = 0;
	pRead = ECAT_START_ADDR + ECAT_UP_DATA_OFFSET;
	
	for(i=0;i<=ECAT_UP_DATA_LENGTH;i++) 
	//	ret = *(pRead++);
		*(pRead++) = 0;
	
}

void EcatRead(Uint16 *pEtherCatReBuf)
{
	Uint16 i=0;
	Uint16 ret=0;
	Uint16 *pRead;

	pRead =  ECAT_START_ADDR+ECAT_DOWNLOAD_DATA_OFFSET;

	for(i = 0; i <ECAT_DOWN_DATA_LENGTH; i++)  //从0读到46
		{
			ret = *(pRead++);
			*(pEtherCatReBuf++) = ret;
		}
}



void ECatWrite(void)
{
	Uint16 *pWrite;
	Uint16 i=0;
	Uint16 ret=0;
    int temp=0,j;

		ECat_UP_Buf[0] = SM_STATUS.ECAT_UP.SM1Udc;
		ECat_UP_Buf[1] = SM_STATUS.ECAT_UP.SM2Udc;
		ECat_UP_Buf[2] = SM_STATUS.ECAT_UP.SM3Udc;
		ECat_UP_Buf[3] = SM_STATUS.ECAT_UP.SM4Udc;
		ECat_UP_Buf[4] = SM_STATUS.ECAT_UP.SM_Cur;
		ECat_UP_Buf[5] = SM_STATUS.ECAT_UP.SM12_fault.all;
		ECat_UP_Buf[6] = SM_STATUS.ECAT_UP.SM34_fault.all;

	for(j=0;j<7;j++)
	{
		temp+=ECat_UP_Buf[j];
	}
	ECat_UP_Buf[7] =temp;// SM_STATUS.ECAT_UP.CommIndex++;

	pWrite = ECAT_START_ADDR+ECAT_UP_DATA_OFFSET;

	for(i=0; i<ECAT_UP_DATA_LENGTH; i++)
		{
			ret =ECat_UP_Buf[i];
			*(pWrite++) = ret;
		}

}

void Ecat_DATA_Get(void)
{

	unsigned int i,temp=0;//,N=0;

	   EcatRead(ECat_Download_Buf);

	   for(i=0;i<13;i++)
	   {
		   temp+=ECat_Download_Buf[i];
	   }

	if(temp == ECat_Download_Buf[13])//(N<200)
	{
	ECAT_DOWNLOAD.SM_CMD.all = ECat_Download_Buf[0];
	ECAT_DOWNLOAD.AU_M = ECat_Download_Buf[1];
	ECAT_DOWNLOAD.AV_M = ECat_Download_Buf[2];
	ECAT_DOWNLOAD.AW_M = ECat_Download_Buf[3];
	ECAT_DOWNLOAD.BU_M = ECat_Download_Buf[4];
	ECAT_DOWNLOAD.BV_M = ECat_Download_Buf[5];
	ECAT_DOWNLOAD.BW_M = ECat_Download_Buf[6];
	ECAT_DOWNLOAD.CU_M = ECat_Download_Buf[7];
	ECAT_DOWNLOAD.CV_M = ECat_Download_Buf[8];
	ECAT_DOWNLOAD.CW_M = ECat_Download_Buf[9];
	ECAT_DOWNLOAD.UdcOverVol = ECat_Download_Buf[10];
	ECAT_DOWNLOAD.OverCur = ECat_Download_Buf[11];


    }

}

void Ecat_CMD_Re(void)
{

	SM_CMD.bit.Reset = ECAT_DOWNLOAD.SM_CMD.bit.Reset ;
	SM_CMD.bit.Deblock = ECAT_DOWNLOAD.SM_CMD.bit.deblock;

	if((PowerModule_Index & 0xFF00) == 0xA100)
		{
			MC_Modulation= ECAT_DOWNLOAD.AU_M;
		}
	if((PowerModule_Index & 0xFF00) == 0xA200)
		{
			MC_Modulation= ECAT_DOWNLOAD.AV_M;
		}
	if((PowerModule_Index & 0xFF00) == 0xA300)
		{
			MC_Modulation= ECAT_DOWNLOAD.AW_M;
		}
	if((PowerModule_Index & 0xFF00) == 0xB100)
		{
			MC_Modulation= ECAT_DOWNLOAD.BU_M;
		}
	if((PowerModule_Index & 0xFF00) == 0xB200)
		{
			MC_Modulation= ECAT_DOWNLOAD.BV_M;
		}
	if((PowerModule_Index & 0xFF00) == 0xB300)
		{
			MC_Modulation= ECAT_DOWNLOAD.BW_M;
		}
	if((PowerModule_Index & 0xFF00) == 0xC100)
		{
			MC_Modulation= ECAT_DOWNLOAD.CU_M;
		}
	if((PowerModule_Index & 0xFF00) == 0xC200)
		{
			MC_Modulation= ECAT_DOWNLOAD.CV_M;
		}
	if((PowerModule_Index & 0xFF00) == 0xC300)
		{
			MC_Modulation= ECAT_DOWNLOAD.CW_M;
		}
}

	/*
	if (((PowerModule_Index & 0xFF00) == 0xA100) || ((PowerModule_Index & 0xFF00) == 0xA300))//////并联A相或者串联A相上桥臂
		{
			SM_CMD.bit.PM_CMD_STATUS = ECAT_DOWNLOAD.CMD_VAR.bit.A_UP_Leg;
			
			if((PowerModule_Index & 0x00FF) == 0x0000 )   //////A相上桥臂第一个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM0;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM1;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM2;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM3;
				}
			if((PowerModule_Index & 0x00FF) == 0x0001 )   //////A相上桥臂第二个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM4;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM5;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM6;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM7;
				}
			if((PowerModule_Index & 0x00FF) == 0x0002 )   //////A相上桥臂第三个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM8;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM9;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM10;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.A_UP_LEG_CMD.bit.SM11;
				}

		}/////并联或串联A相上桥臂
	
	if (((PowerModule_Index & 0xFF00) == 0xA200) || ((PowerModule_Index & 0xFF00) == 0xA400))//////并联A相或者串联A相下桥臂
		{
			SM_CMD.bit.PM_CMD_STATUS = ECAT_DOWNLOAD.CMD_VAR.bit.A_DOWN_Leg;
			
			if((PowerModule_Index & 0x00FF) == 0x0000 )   //////A相下桥臂第一个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM0;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM1;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM2;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM3;
				}
			if((PowerModule_Index & 0x00FF) == 0x0001 )   //////A相下桥臂第二个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM4;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM5;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM6;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM7;
				}
			if((PowerModule_Index & 0x00FF) == 0x0002 )   //////A相下桥臂第三个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM8;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM9;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM10;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.A_DOWN_LEG_CMD.bit.SM11;
				}

		}////并联或串联A相下桥臂

	if (((PowerModule_Index & 0xFF00) == 0xB100) || ((PowerModule_Index & 0xFF00) == 0xB300))//////并联B相或者串联B相上桥臂
		{
			SM_CMD.bit.PM_CMD_STATUS = ECAT_DOWNLOAD.CMD_VAR.bit.B_UP_Leg;
			
			if((PowerModule_Index & 0x00FF) == 0x0000 )   //////B相上桥臂第一个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM0;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM1;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM2;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM3;
				}
			if((PowerModule_Index & 0x00FF) == 0x0001 )   //////B相上桥臂第二个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM4;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM5;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM6;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM7;
				}
			if((PowerModule_Index & 0x00FF) == 0x0002 )   //////B相上桥臂第三个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM8;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM9;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM10;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.B_UP_LEG_CMD.bit.SM11;
				}

		}/////并联或串联B相上桥臂
		
	if (((PowerModule_Index & 0xFF00) == 0xB200) || ((PowerModule_Index & 0xFF00) == 0xB400))//////并联B相或者串联B相下桥臂
		{
			SM_CMD.bit.PM_CMD_STATUS = ECAT_DOWNLOAD.CMD_VAR.bit.B_DOWN_Leg;
			
			if((PowerModule_Index & 0x00FF) == 0x0000 )   //////B相下桥臂第一个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM0;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM1;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM2;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM3;
				}
			if((PowerModule_Index & 0x00FF) == 0x0001 )   //////B相下桥臂第二个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM4;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM5;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM6;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM7;
				}
			if((PowerModule_Index & 0x00FF) == 0x0002 )   //////B相下桥臂第三个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM8;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM9;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM10;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.B_DOWN_LEG_CMD.bit.SM11;
				}

		}////并联或串联B相下桥臂

	if (((PowerModule_Index & 0xFF00) == 0xC100) || ((PowerModule_Index & 0xFF00) == 0xC300))//////并联C相或者串联C相上桥臂
		{
			SM_CMD.bit.PM_CMD_STATUS = ECAT_DOWNLOAD.CMD_VAR.bit.C_UP_Leg;
			
			if((PowerModule_Index & 0x00FF) == 0x0000 )   //////C相上桥臂第一个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM0;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM1;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM2;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM3;
				}
			if((PowerModule_Index & 0x00FF) == 0x0001 )   //////C相上桥臂第二个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM4;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM5;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM6;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM7;
				}
			if((PowerModule_Index & 0x00FF) == 0x0002 )   //////C相上桥臂第三个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM8;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM9;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM10;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.C_UP_LEG_CMD.bit.SM11;
				}

		}/////并联或串联C相上桥臂
		
	if (((PowerModule_Index & 0xFF00) == 0xC200) || ((PowerModule_Index & 0xFF00) == 0xC400))//////并联C相或者串联C相下桥臂
		{
			SM_CMD.bit.PM_CMD_STATUS = ECAT_DOWNLOAD.CMD_VAR.bit.C_DOWN_Leg;
			
			if((PowerModule_Index & 0x00FF) == 0x0000 )   //////C嘞虑疟鄣谝桓瞿？�
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM0;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM1;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM2;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM3;
				}
			if((PowerModule_Index & 0x00FF) == 0x0001 )   //////C相下桥臂第二个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM4;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM5;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM6;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM7;
				}
			if((PowerModule_Index & 0x00FF) == 0x0002 )   //////C相下桥臂第三个模块
				{
					SM_CMD.bit.SM1_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM8;
					SM_CMD.bit.SM2_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM9;
					SM_CMD.bit.SM3_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM10;
					SM_CMD.bit.SM4_Switch = ECAT_DOWNLOAD.C_DOWN_LEG_CMD.bit.SM11;
				}
	
		}////并联或串联C相下桥臂

*/





