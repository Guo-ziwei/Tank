#include "joypad.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��Ϸ�ֱ����� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
//#define JOYPAD_CLK PBout(7)  	//ʱ��		PB7   
//#define JOYPAD_LAT PAout(8)  	//����     	PB6
//#define JOYPAD_DAT PAin(11)	 	//����     	PB5  

//��ʼ���ֱ��ӿ�.	 
void JOYPAD_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB,PD�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
 	GPIO_SetBits(GPIOB,GPIO_Pin_7);	//����

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
 	GPIO_SetBits(GPIOB,GPIO_Pin_6);	//����
	
 	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
 	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��GPIO
	GPIO_SetBits(GPIOA,GPIO_Pin_11);	//����

}

void JOYPAD2_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB,PD�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //blue
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��GPIO
 	GPIO_SetBits(GPIOA,GPIO_Pin_7);	//����

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //p
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��GPIO
 	GPIO_SetBits(GPIOA,GPIO_Pin_5);	//����
	
	
 	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//g
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
 	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��GPIO
	GPIO_SetBits(GPIOA,GPIO_Pin_4);	//����

}


//�ֱ��ӳٺ���
//t:Ҫ�ӳٵ�ʱ��
void JOYPAD_Delay(u16 t)
{
	while(t--);
}
//��ȡ�ֱ�����ֵ.
//FC�ֱ����������ʽ:
//ÿ��һ������,���һλ����,���˳��:
//A->B->SELECT->START->UP->DOWN->LEFT->RIGHT.
//�ܹ�8λ,������C��ť���ֱ�,����C��ʵ�͵���A+Bͬʱ����.
//������1,�ɿ���0.
//����ֵ:
//[7]:��
//[6]:��
//[5]:��
//[4]:��
//[3]:Start
//[2]:Select
//[1]:B
//[0]:A
u8 JOYPAD_Read(void)
{
	vu8 temp=0;
 	u8 t;
	JOYPAD_LAT=1;	//���浱ǰ״̬
 	JOYPAD_Delay(80);
	JOYPAD_LAT=0; 
	for(t=0;t<8;t++)
	{
		temp>>=1;	 
		if(JOYPAD_DAT==0)temp|=0x80;//LOAD֮�󣬾͵õ���һ������
		JOYPAD_CLK=1;			   	//ÿ��һ�����壬�յ�һ������
		JOYPAD_Delay(80);
		JOYPAD_CLK=0;	
		JOYPAD_Delay(80); 
	}
	return temp;
}

u8 JOYPAD2_Read(void)
{
	vu8 temp=0;
 	u8 t;
	JOYPAD2_LAT=1;	//���浱ǰ״̬
 	JOYPAD_Delay(80);
	JOYPAD2_LAT=0; 
	for(t=0;t<8;t++)
	{
		temp>>=1;	 
		if(JOYPAD2_DAT==0)temp|=0x80;//LOAD֮�󣬾͵õ���һ������
		JOYPAD2_CLK=1;			   	//ÿ��һ�����壬�յ�һ������
		JOYPAD_Delay(80);
		JOYPAD2_CLK=0;	
		JOYPAD_Delay(80); 
	}
	return temp;
}
