#ifndef __PQC_EEPROM_H__
#define __PQC_EEPROM_H__

extern void WriteBlock(unsigned int staraddr,unsigned int lenth,unsigned int wrdata[]);
extern void  ReadBlock(unsigned int staraddr,unsigned int lenth,unsigned int redata[]);     
extern void EEPROM_Calculate_Sum(Uint16 temp[], Uint16 num);
extern Uint16 EEPROM_Check_Sum_Right(Uint16 temp[], Uint16 num);


#endif

