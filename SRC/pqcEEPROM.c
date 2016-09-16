/******************************************************************************
 Copyright (C), 2008-2009, CEPRI Co., Ltd.
 File name:  EtherCAT相关的变量
 Author:     蔡林海编写     
 Version:            
 Date: 2009.6.10
 Description:0x00-0x800可写                    
 Others:   
 Function List:   
 History:
*******************************************************************************/

/*本文件定义与EtherCAT相关的变量*/
#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_Examples.h"   // Examples Include File
  
/***************定义全局变量*******************************************/

/***************定义子函数*******************************************************/
void Set_SCL_1(void);   /*PC0 IS AT24C16'S SCL */
void Clr_SCL_0(void);   /*PC0 IS AT24C16'S SCL */
void Set_SDA_1(void);   /*PC1 IS AT24C16'S SDA */
void Clr_SDA_0(void);   /*PC1 IS AT24C16'S SDA */
int  Get_SDA(void);     /*PC1 IS AT24C16'S SDA  */

void Start(void);   
void Stop(void); 
void Ack(void);
void NAck(void);        

void WriteByte(unsigned int value);  /* shift out*/
void Write24C16(unsigned int addr,unsigned int value);  /* 0=<addr<=2047 ,0=<value<=255 */ 
unsigned int ReadByte(void);  /*shift in */
unsigned int Read_Random_24C16(unsigned int addr);     
unsigned int Read_Current_24C16(unsigned int addr);
void WriteBlock(unsigned int staraddr,unsigned int lenth,unsigned int wrdata[]);
extern void ServiceDog();        /*看门狗程序*/ 
void  ReadBlock(unsigned int staraddr,unsigned int lenth,unsigned int redata[]);     

/***************定义子函数结束************************************************/


//计算低八位校验和。 num为数组大小，数组的最后一个元素
//用于存放前面的校验和
void EEPROM_Calculate_Sum(Uint16 temp[], Uint16 num)
{
	Uint16 i,sum;
	for(i = 0, sum = 0; i < (num - 1); i++)
		{
		sum += temp[i];
		}
	temp[i] = (sum - 1) & 0xFF;
}

//检查校验和是否为存放的值
Uint16 EEPROM_Check_Sum_Right(Uint16 temp[], Uint16 num)
{
	Uint16 i,sum;
	for(i = 0, sum = 0; i < (num - 1); i++)
		{
		sum += temp[i];
		}
	if(temp[12] == ((sum - 1) & 0xFF))
		return 1;
	else
		return 0;
}




/*以下均为I2C 函数*/
/*CPU :GPIO30 EPCLK; GPIO33 EPDAT*/

void SET_APORT_ISIO(void) /*PC0 EPCLK; PC1 EPDAT*/
{                         /*GPIO63 EPCLK; GPIO62 EPDAT*/
 	//MCRB &= 0x0FFFC; /*PC0,PC1配制成普通IO口*/
	EALLOW;
	GpioCtrlRegs.GPBMUX1.bit.GPIO33=0; /*GPIO33,GPIO30配制成普通IO口*/ 
	GpioCtrlRegs.GPAMUX2.bit.GPIO30=0; /*GPIO33,GPIO30配制成普通IO口*/
	EDIS;
}           

void Delay1(void)
{    
    volatile unsigned int dei;
	ServiceDog();/*复位看门狗*/
	dei=0;
	do 
	{/*复位看门狗*/
	   
	   dei++;
	}while (dei<0x150);
	ServiceDog();
}  

void delay0(void)
{    
    volatile  unsigned int dli;
	dli=0;
	ServiceDog();/*复位看门狗*/
	do 
	{
	   dli++;
	}while (dli<0x20);
	ServiceDog();
}  
 

  
void Set_SCL_1(void) /*PC0 GPIO63 IS AT24C16'S SCL */
{             
	//PCDATDIR=PCDATDIR | 0x0101;/*PC0 out 1*/

	 EALLOW;
     GpioCtrlRegs.GPADIR.bit.GPIO30=1;/*GPIO30 out */
	 EDIS;
	 GpioDataRegs.GPADAT.bit.GPIO30=1;/*GPIO30 out 1 */
}

void Clr_SCL_0(void) /*PC0 GPIO63 IS AT24C16'S SCL */ 
{ 
	//PCDATDIR=PCDATDIR | 0x0100; 
	//PCDATDIR=PCDATDIR & 0xfffe;

	 EALLOW;
	 GpioCtrlRegs.GPADIR.bit.GPIO30=1;/*GPIO30 out */ 
	 EDIS;
	 delay0();	
	 GpioDataRegs.GPADAT.bit.GPIO30=0;/*GPIO30 out 0 */
}   

void Set_SDA_1(void) /*PC1 GPIO62 IS AT24C16'S SDA */
{             
	//PCDATDIR=PCDATDIR | 0x0202;/*PC1 out 1*/
	 EALLOW;
	 GpioCtrlRegs.GPBDIR.bit.GPIO33=1;/*GPIO62 out */  
	 EDIS;
	 GpioDataRegs.GPBDAT.bit.GPIO33=1;/*GPIO62 out 1 */
}

void Clr_SDA_0(void) /*PC1 GPIO62 IS AT24C16'S SDA */ 
{        
	//PCDATDIR=PCDATDIR | 0x0200;
	//PCDATDIR=PCDATDIR & 0xfffd;

	 EALLOW;
	 GpioCtrlRegs.GPBDIR.bit.GPIO33=1;/*GPIO62 out */
	 EDIS; 
	 delay0();	 
	 GpioDataRegs.GPBDAT.bit.GPIO33=0;/*GPIO62 out 0 */
} 
         
int  Get_SDA(void)/*PC1 GPIO62 IS AT24C16'S SDA */
{     
	int PA4_value;   
	//PA4_value= PCDATDIR;
	 PA4_value= GpioDataRegs.GPBDAT.bit.GPIO33;
	delay0();
	//PA4_value = PA4_value & 0x02;
	if(PA4_value==0)         
		return 0;
	else 
	 	return 1;
}  
               
void Start(void)
{
	delay0();
	Set_SCL_1();      
	delay0();
	Set_SDA_1();
	Delay1();
	Clr_SDA_0();
	Delay1();
	Clr_SCL_0();
}

void Stop(void)
{      
	delay0();
	Clr_SDA_0();
	Delay1();
	Set_SCL_1();
	Delay1();
	Set_SDA_1();
}
    
void Ack(void)
{   
	delay0();
	Clr_SDA_0();
	Delay1(); 
	Set_SCL_1();
	Delay1();
	Clr_SCL_0();
}  

void NAck(void)
{    
	delay0();
	Set_SDA_1();
	Delay1();
	Set_SCL_1();
	Delay1();
	Clr_SCL_0();
}

void WriteByte(unsigned int val)
{    
	unsigned int dyi; 
	unsigned int shtmp;
	shtmp=0x80;
	for(dyi=0;dyi<8;dyi++)
	{
		Delay1();
		if((val & shtmp)==0 ) 
			Clr_SDA_0();
		else
		Set_SDA_1();
		delay0();
		Set_SCL_1();
		delay0();
		Clr_SCL_0();  
		
		shtmp=(shtmp>>1);	
	}     
	
	Delay1();
	
	//PCDATDIR=PCDATDIR & 0xfdff;  /*Set PC1(SDA) is input port*/
	  
	 EALLOW;
	 GpioCtrlRegs.GPBDIR.bit.GPIO33=0;  /*Set GPIO33(SDA) is input port*/ 
	 EDIS; 

	delay0(); 
	Set_SCL_1();
	delay0(); 
	Clr_SCL_0();
}

unsigned int ReadByte(void)
{              
	int i;   
	unsigned int Readata=0;   
		
	//PCDATDIR=PCDATDIR & 0xfdff;  /*Set PC1(SDA) is input port*/  
	 EALLOW;
	 GpioCtrlRegs.GPBDIR.bit.GPIO33=0;  /*Set GPIO33(SDA) is input port*/    
	 EDIS; 
	Delay1();
	for(i=0;i<8;i++){
		Delay1();
		Set_SCL_1();
		Delay1();
		Readata=Readata+Get_SDA();   
		if(i<7)
			Readata=Readata<<1;	  
		Clr_SCL_0();
		
	}
    return Readata; 
}


void WriteBlock(unsigned int staraddr,unsigned int lenth,unsigned int wrdata[])
{
  	    int addrtmp; 
  	    unsigned int WBi;       
    	/*设置EEPROM*/
    	SET_APORT_ISIO();  /*PC0,PC1配制成普通IO口*/
    	delay0();
  		Set_SDA_1();  /*IOPC1 输出高电平, PC1 IS AT24C16'S SDA */
    	delay0();
  		Set_SCL_1();
    	delay0();    /*IOPC0 输出高电平, PC0 IS AT24C16'S SCL */
		addrtmp = (staraddr/256)<<1;
		addrtmp &= 0x0e;
		addrtmp |= 0xa0; 
		
	 	Start();  /*向EEPROM 发写数指令*/       
 	
	 	WriteByte( addrtmp); /*把addrtmp中的值逐位写入EEPROM*/
    	delay0();
	 	WriteByte( staraddr % 256);
	 	delay0();
	 
	 	/*写数*/
	 	for(WBi=0;WBi<lenth;WBi++)
	 	{
 			WriteByte(wrdata[WBi]);
 			/*复位看门狗*/
	        ServiceDog();
 		}
 		Stop();

 	return; 	
}




void  ReadBlock(unsigned int staraddr,unsigned int lenth,unsigned int redata[])
{
     int addrtmp;       /*定义局部变量*/
     unsigned rdai;
     /*设置EEPROM*/
     SET_APORT_ISIO();/*PC0,PC1配制成普通IO口*/
  	 Set_SDA_1(); 
  	 Set_SCL_1();
	 Delay1();
     addrtmp = (staraddr/256)<<1;
	 addrtmp = addrtmp & 0x0e;
	 addrtmp = 0xa0+ addrtmp;
	 Delay1(); 
	 Start();             
	
	 WriteByte( addrtmp);
	 Delay1(); 
	 WriteByte( staraddr % 256);
		 
	 addrtmp = 0x01+ addrtmp;   
	 Start();                               
	 WriteByte( addrtmp ); 
	 /*读数据*/
	 for(rdai=0;rdai<lenth;rdai++)
	 { 
	 	redata[rdai] = ReadByte();
	 	if( rdai<(lenth-1) )
	 		Ack();
	 	else
	 		NAck();	
	 }
	 Stop(); 
 	 return;
}


