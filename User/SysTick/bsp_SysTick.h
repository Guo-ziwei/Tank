#ifndef __SYSTICK_H
#define __SYSTICK_H


#include "stm32f10x.h"


void SysTick_Init(void);
void Delay_us(__IO u32 nTime);         // ��λ1us

void SysTick_Delay_Ms( __IO uint32_t ms);

#define Delay_ms(x) Delay_us(1000*x)	 //��λms


#endif /* __SYSTICK_H */
