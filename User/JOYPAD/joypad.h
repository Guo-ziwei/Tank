#ifndef __JOYPAD_H
#define __JOYPAD_H	 

#include "stm32f10x.h"
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//��Ϸ�ֱ����� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//�ֱ���������
#define JOYPAD_CLK PBout(7)  	//ʱ��		PB7   
#define JOYPAD_LAT PBout(6)  	//����     	PB6
#define JOYPAD_DAT PAin(11)	 	//����     	PA11  

#define JOYPAD2_CLK PAout(7)  	//ʱ��		PB7   
#define JOYPAD2_LAT PAout(5)  	//����     	PB6
#define JOYPAD2_DAT PAin(4)	 	//����     	PA11  

void JOYPAD_Init(void);			//��ʼ��	
void JOYPAD_Delay(u16 t);		//��ʱ
u8 JOYPAD_Read(void);			//��ȡ��ֵ	 			

void JOYPAD2_Init(void);			//��ʼ��	
u8 JOYPAD2_Read(void);			//��ȡ��ֵ	 
#endif
















