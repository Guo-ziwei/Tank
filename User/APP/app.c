/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : EHS
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>
#include <string.h>
#include "./lcd/bsp_ili9341_lcd.h"
#include "joypad.h"
#include "stm32f10x.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./led/bsp_led.h"   
#include "ff.h"
#include <stdio.h>
#include "bsp_tpad.h"
#include "element.h"
#include "Bullet.h"
#include "bsp_usart.h" 
#include "map.h"
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

//OS_MEM  mem;                    //�����ڴ�������
//uint8_t ucArray [ 3 ] [ 20 ];   //�����ڴ������С


Tank tankA;
Tank tankB;
Tank RandomA;
Tank RandomB;

Bullet bullet[80];
Bullet bulletA;
Bullet bulletB;	
Package packX;

int newbullet_N=0;
int j;
int i;

u8 deadA=0,deadB=0;
/*
*********************************************************************************************************
*                                                 TCB
*********************************************************************************************************
*/

static  OS_TCB   AppTaskStartTCB;    //������ƿ�
static  OS_TCB   AppTaskStartGameTCB;    //������ƿ�

static  OS_TCB   AppTaskPad1TCB;
static  OS_TCB   AppTaskPad2TCB;

static  OS_TCB   AppTaskBulletTCB;

static  OS_TCB   AppTaskPackageTCB;

static  OS_TCB   AppTaskAstarTCB;
static  OS_TCB   AppTaskAstar_BTCB;

static  OS_TCB   AppTaskDeadTCB;
/*
*********************************************************************************************************
*                                                STACKS
*********************************************************************************************************
*/

static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];       //�����ջ
static  CPU_STK  AppTaskStartGameStk[APP_TASK_STARTGAME_STK_SIZE];       //�����ջ
static  CPU_STK  AppTaskPad1Stk [ APP_TASK_PAD1_STK_SIZE ];
static  CPU_STK  AppTaskPad2Stk [ APP_TASK_PAD2_STK_SIZE ];
static  CPU_STK  AppTaskBulletStk [ APP_TASK_BULLET_STK_SIZE ];

static  CPU_STK  AppTaskPackageStk [ APP_TASK_PACKAGE_STK_SIZE ];
static  CPU_STK  AppTaskAstarStk [ APP_TASK_ASTAR_STK_SIZE ];
static  CPU_STK  AppTaskAstar_BStk [ APP_TASK_ASTAR_B_STK_SIZE ];

static  CPU_STK  AppTaskDeadStk [ APP_TASK_DEAD_STK_SIZE ];
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart  (void *p_arg);               //����������
static  void  AppTaskStartGame  (void *p_arg);               //����������
static  void  AppTaskPad1  ( void * p_arg );
static  void  AppTaskPad2  ( void * p_arg );
static  void  AppTaskBullet  ( void * p_arg );

static  void  AppTaskPackage  ( void * p_arg );
static  void  AppTaskAstar  ( void * p_arg );
static  void  AppTaskAstar_B  ( void * p_arg );

static  void  AppTaskDead  ( void * p_arg );
/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR  err;
		 
	  JOYPAD_Init();			//�ֱ���ʼ��
    JOYPAD2_Init();			//�ֱ���ʼ��
		ILI9341_Init ();         //LCD ��ʼ��
	
		LCD_SetFont(&Font8x16);
		LCD_SetColors(RED,BLACK);
		ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
		ILI9341_GramScan ( 6 );
	
		tankA.No = 1;
		tankA.blood = 10;
		tankA.direction = 1;
		tankA.x = 13;
		tankA.y = 225;
		tankA.speed=4;
	
		tankB.No = 2;
		tankB.blood = 10;
		tankB.direction = 1;
		tankB.x = 307;
		tankB.y = 25;
		tankB.speed=4;
	
		RandomA.No = 3;
		RandomA.blood = 1;
		RandomA.direction = 3;
		RandomA.x = 13;
		RandomA.y = 10;	
		
		RandomB.No = 4;
		RandomB.blood = 1;
		RandomB.direction = 1;
		RandomB.x = 307;
		RandomB.y = 230;	
		
    creat_package(&packX);
		map_start();
    OSInit(&err);                                                           //��ʼ�� uC/OS-III

	  /* ������ʼ���� */
    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                            //������ƿ��ַ
                 (CPU_CHAR   *)"App Task Start",                            //��������
                 (OS_TASK_PTR ) AppTaskStart,                               //������
                 (void       *) 0,                                          //���ݸ����������β�p_arg����ʵ��
                 (OS_PRIO     ) APP_TASK_START_PRIO,                        //��������ȼ�
                 (CPU_STK    *)&AppTaskStartStk[0],                         //�����ջ�Ļ���ַ
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,               //�����ջ�ռ�ʣ��1/10ʱ����������
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,                    //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
                 (OS_MSG_QTY  ) 5u,                                         //����ɽ��յ������Ϣ��
                 (OS_TICK     ) 0u,                                         //�����ʱ��Ƭ��������0��Ĭ��ֵOSCfg_TickRate_Hz/10��
                 (void       *) 0,                                          //������չ��0����չ��
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //����ѡ��
                 (OS_ERR     *)&err);                                       //���ش�������

    OSStart(&err);                                                          //�����������������uC/OS-III���ƣ�

}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    OS_ERR      err;


    (void)p_arg;

    CPU_Init();                                                 //��ʼ�� CPU �����ʱ��������ж�ʱ���������������

    
	cpu_clk_freq = BSP_CPU_ClkFreq();                           //��ȡ CPU �ں�ʱ��Ƶ�ʣ�SysTick ����ʱ�ӣ�
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        //�����û��趨��ʱ�ӽ���Ƶ�ʼ��� SysTick ��ʱ���ļ���ֵ
    OS_CPU_SysTickInit(cnts);                                   //���� SysTick ��ʼ�����������ö�ʱ������ֵ��������ʱ��

    Mem_Init();                                                 //��ʼ���ڴ������������ڴ�غ��ڴ�ر�

#if OS_CFG_STAT_TASK_EN > 0u                                    //���ʹ�ܣ�Ĭ��ʹ�ܣ���ͳ������
    OSStatTaskCPUUsageInit(&err);                               //����û��Ӧ������ֻ�п�����������ʱ CPU �ģ����
#endif                                                          //���������� OS_Stat_IdleCtrMax ��ֵ��Ϊ������� CPU 
                                                                //ʹ����ʹ�ã���
    CPU_IntDisMeasMaxCurReset();                                //��λ�����㣩��ǰ�����ж�ʱ��

    
    /* ����ʱ��Ƭ��ת���� */		
    OSSchedRoundRobinCfg((CPU_BOOLEAN   )DEF_ENABLED,          //ʹ��ʱ��Ƭ��ת����
		                     (OS_TICK       )0,                    //�� OSCfg_TickRate_Hz / 10 ��ΪĬ��ʱ��Ƭֵ
												 (OS_ERR       *)&err );               //���ش�������
    OSStart(&err);                                                          //�����������������uC/OS-III���ƣ�
	  
		/* ���� StartGame ���� */
    OSTaskCreate((OS_TCB     *)&AppTaskStartGameTCB,                            //������ƿ��ַ
                 (CPU_CHAR   *)"App Task StartGame",                            //��������
                 (OS_TASK_PTR ) AppTaskStartGame,                               //������
                 (void       *) 0,                                          //���ݸ����������β�p_arg����ʵ��
                 (OS_PRIO     ) APP_TASK_STARTGAME_PRIO,                        //��������ȼ�
                 (CPU_STK    *)&AppTaskStartGameStk[0],                         //�����ջ�Ļ���ַ
                 (CPU_STK_SIZE) APP_TASK_STARTGAME_STK_SIZE / 10,               //�����ջ�ռ�ʣ��1/10ʱ����������
                 (CPU_STK_SIZE) APP_TASK_STARTGAME_STK_SIZE,                    //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
                 (OS_MSG_QTY  ) 5u,                                         //����ɽ��յ������Ϣ��
                 (OS_TICK     ) 0u,                                         //�����ʱ��Ƭ��������0��Ĭ��ֵOSCfg_TickRate_Hz/10��
                 (void       *) 0,                                          //������չ��0����չ��
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //����ѡ��
                 (OS_ERR     *)&err);                                       //���ش�������
		OSTaskDel ( 0, & err );                     //ɾ����ʼ������������������
		
		
}

/*
*********************************************************************************************************
*                                          StartGame TASK
*********************************************************************************************************
*/

static  void  AppTaskStartGame ( void * p_arg )
{
	OS_ERR      err;
	u8 key;
	(void)p_arg;
	while (DEF_TRUE) {	                      //�����壬ͨ��д��һ����ѭ��
		
		key=JOYPAD_Read();
		if(key==8)
		{
		map();
	  ILI9341_GramScan ( 7 );
		/* ���� PAD1 ���� */
    OSTaskCreate((OS_TCB     *)&AppTaskPad1TCB,                             //������ƿ��ַ
                 (CPU_CHAR   *)"App Task Pad1",                             //��������
                 (OS_TASK_PTR ) AppTaskPad1,                                //������
                 (void       *) 0,                                          //���ݸ����������β�p_arg����ʵ��
                 (OS_PRIO     ) APP_TASK_PAD1_PRIO,                         //��������ȼ�
                 (CPU_STK    *)&AppTaskPad1Stk[0],                          //�����ջ�Ļ���ַ
                 (CPU_STK_SIZE) APP_TASK_PAD1_STK_SIZE / 10,                //�����ջ�ռ�ʣ��1/10ʱ����������
                 (CPU_STK_SIZE) APP_TASK_PAD1_STK_SIZE,                     //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
                 (OS_MSG_QTY  ) 5u,                                         //����ɽ��յ������Ϣ��
                 (OS_TICK     ) 0u,                                         //�����ʱ��Ƭ��������0��Ĭ��ֵ��
                 (void       *) 0,                                          //������չ��0����չ��
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //����ѡ��
                 (OS_ERR     *)&err);                                       //���ش�������
		
		/* ���� PAD2 ���� */
    OSTaskCreate((OS_TCB     *)&AppTaskPad2TCB,                             //������ƿ��ַ
                 (CPU_CHAR   *)"App Task Pad2",                             //��������
                 (OS_TASK_PTR ) AppTaskPad2,                                //������
                 (void       *) 0,                                          //���ݸ����������β�p_arg����ʵ��
                 (OS_PRIO     ) APP_TASK_PAD2_PRIO,                         //��������ȼ�
                 (CPU_STK    *)&AppTaskPad2Stk[0],                          //�����ջ�Ļ���ַ
                 (CPU_STK_SIZE) APP_TASK_PAD2_STK_SIZE / 10,                //�����ջ�ռ�ʣ��1/10ʱ����������
                 (CPU_STK_SIZE) APP_TASK_PAD2_STK_SIZE,                     //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
                 (OS_MSG_QTY  ) 5u,                                         //����ɽ��յ������Ϣ��
                 (OS_TICK     ) 0u,                                         //�����ʱ��Ƭ��������0��Ĭ��ֵ��
                 (void       *) 0,                                          //������չ��0����չ��
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //����ѡ��
                 (OS_ERR     *)&err);                                       //���ش�������								 

		/* ���� BULLET ���� */
    OSTaskCreate((OS_TCB     *)&AppTaskBulletTCB,                             //������ƿ��ַ
                 (CPU_CHAR   *)"App Task Bullet",                             //��������
                 (OS_TASK_PTR ) AppTaskBullet,                                //������
                 (void       *) 0,                                          //���ݸ����������β�p_arg����ʵ��
                 (OS_PRIO     ) APP_TASK_BULLET_PRIO,                         //��������ȼ�
                 (CPU_STK    *)&AppTaskBulletStk[0],                          //�����ջ�Ļ���ַ
                 (CPU_STK_SIZE) APP_TASK_BULLET_STK_SIZE / 10,                //�����ջ�ռ�ʣ��1/10ʱ����������
                 (CPU_STK_SIZE) APP_TASK_BULLET_STK_SIZE,                     //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
                 (OS_MSG_QTY  ) 5u,                                         //����ɽ��յ������Ϣ��
                 (OS_TICK     ) 0u,                                         //�����ʱ��Ƭ��������0��Ĭ��ֵ��
                 (void       *) 0,                                          //������չ��0����չ��
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //����ѡ��
                 (OS_ERR     *)&err);                                       //���ش�������
		/* ���� DEAD ���� */
    OSTaskCreate((OS_TCB     *)&AppTaskDeadTCB,                             //������ƿ��ַ
                 (CPU_CHAR   *)"App Task Dead",                             //��������
                 (OS_TASK_PTR ) AppTaskDead,                                //������
                 (void       *) 0,                                          //���ݸ����������β�p_arg����ʵ��
                 (OS_PRIO     ) APP_TASK_DEAD_PRIO,                         //��������ȼ�
                 (CPU_STK    *)&AppTaskDeadStk[0],                          //�����ջ�Ļ���ַ
                 (CPU_STK_SIZE) APP_TASK_DEAD_STK_SIZE / 10,                //�����ջ�ռ�ʣ��1/10ʱ����������
                 (CPU_STK_SIZE) APP_TASK_DEAD_STK_SIZE,                     //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
                 (OS_MSG_QTY  ) 5u,                                         //����ɽ��յ������Ϣ��
                 (OS_TICK     ) 0u,                                         //�����ʱ��Ƭ��������0��Ĭ��ֵ��
                 (void       *) 0,                                          //������չ��0����չ��
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //����ѡ��
                 (OS_ERR     *)&err);                                       //���ش�������
		/* ���� ASTAR ���� */
    OSTaskCreate((OS_TCB     *)&AppTaskAstarTCB,                             //������ƿ��ַ
                 (CPU_CHAR   *)"App Task Astar",                             //��������
                 (OS_TASK_PTR ) AppTaskAstar,                                //������
                 (void       *) 0,                                          //���ݸ����������β�p_arg����ʵ��
                 (OS_PRIO     ) APP_TASK_ASTAR_PRIO,                         //��������ȼ�
                 (CPU_STK    *)&AppTaskAstarStk[0],                          //�����ջ�Ļ���ַ
                 (CPU_STK_SIZE) APP_TASK_ASTAR_STK_SIZE / 10,                //�����ջ�ռ�ʣ��1/10ʱ����������
                 (CPU_STK_SIZE) APP_TASK_ASTAR_STK_SIZE,                     //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
                 (OS_MSG_QTY  ) 5u,                                         //����ɽ��յ������Ϣ��
                 (OS_TICK     ) 0u,                                         //�����ʱ��Ƭ��������0��Ĭ��ֵ��
                 (void       *) 0,                                          //������չ��0����չ��
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //����ѡ��
                 (OS_ERR     *)&err);                                       //���ش�������
   
								 OSTaskCreate((OS_TCB     *)&AppTaskAstar_BTCB,                             //������ƿ��ַ
                 (CPU_CHAR   *)"App Task Astar_B",                             //��������
                 (OS_TASK_PTR ) AppTaskAstar_B,                                //������
                 (void       *) 0,                                          //���ݸ����������β�p_arg����ʵ��
                 (OS_PRIO     ) APP_TASK_ASTAR_B_PRIO,                         //��������ȼ�
                 (CPU_STK    *)&AppTaskAstar_BStk[0],                          //�����ջ�Ļ���ַ
                 (CPU_STK_SIZE) APP_TASK_ASTAR_B_STK_SIZE / 10,                //�����ջ�ռ�ʣ��1/10ʱ����������
                 (CPU_STK_SIZE) APP_TASK_ASTAR_B_STK_SIZE,                     //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
                 (OS_MSG_QTY  ) 5u,                                         //����ɽ��յ������Ϣ��
                 (OS_TICK     ) 0u,                                         //�����ʱ��Ƭ��������0��Ĭ��ֵ��
                 (void       *) 0,                                          //������չ��0����չ��
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //����ѡ��
                 (OS_ERR     *)&err);                                       //���ش�������
//	
//		/* ���� PACKAGE ���� */
    OSTaskCreate((OS_TCB     *)&AppTaskPackageTCB,                             //������ƿ��ַ
                 (CPU_CHAR   *)"App Task Package",                             //��������
                 (OS_TASK_PTR ) AppTaskPackage,                                //������
                 (void       *) 0,                                          //���ݸ����������β�p_arg����ʵ��
                 (OS_PRIO     ) APP_TASK_PACKAGE_PRIO,                         //��������ȼ�
                 (CPU_STK    *)&AppTaskPackageStk[0],                          //�����ջ�Ļ���ַ
                 (CPU_STK_SIZE) APP_TASK_PACKAGE_STK_SIZE / 10,                //�����ջ�ռ�ʣ��1/10ʱ����������
                 (CPU_STK_SIZE) APP_TASK_PACKAGE_STK_SIZE,                     //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
                 (OS_MSG_QTY  ) 5u,                                         //����ɽ��յ������Ϣ��
                 (OS_TICK     ) 0u,                                         //�����ʱ��Ƭ��������0��Ĭ��ֵ��
                 (void       *) 0,                                          //������չ��0����չ��
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //����ѡ��
                 (OS_ERR     *)&err);                                       //���ش�������

					OSTaskDel ( 0, & err );                     //ɾ����ʼ������������������
					}
				  OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );        //�������ʱ1000��ʱ�ӽ��ģ�1s��
	}
}
/*
*********************************************************************************************************
*                                          PAD1 TASK
*********************************************************************************************************
*/

static  void  AppTaskPad1 ( void * p_arg )
{
	OS_ERR      err;
//	OS_REG      value;	
	u8 key; 
	u8 flag=0;
	(void)p_arg;

	while (DEF_TRUE) {                                   //�����壬ͨ��д��һ����ѭ��
		key=JOYPAD_Read();
		
		switch(key)
		{
			case 2:
					if(flag==0)
					{
							Bullet_load(&bullet[newbullet_N++],&tankA);
							flag=1;
					}
					break;
			case 16: 
					Tank_turn(&tankA,1);
					Tank_move(&tankA);
					draw_Tank(&tankA);
					flag=0;
					break;
			case 32: 
					Tank_turn(&tankA,3);
					Tank_move(&tankA);
					draw_Tank(&tankA);
					flag=0;
					break;
			case 64: 
					Tank_turn(&tankA,2);
					Tank_move(&tankA);
					draw_Tank(&tankA);
			    flag=0;
					break;
			case 128: 
					Tank_turn(&tankA,0);
					Tank_move(&tankA);
					draw_Tank(&tankA);
			    flag=0;
					break;	
			
			case 18: 
					Tank_turn(&tankA,1);
					Tank_move(&tankA);
					draw_Tank(&tankA);
					if(flag==0)
					{
							Bullet_load(&bullet[newbullet_N++],&tankA);
							flag=1;
					}
					break;
			case 34: 
					Tank_turn(&tankA,3);
					Tank_move(&tankA);
					draw_Tank(&tankA);
					if(flag==0)
					{
							Bullet_load(&bullet[newbullet_N++],&tankA);
							flag=1;
					}
					break;
			case 66: 
					Tank_turn(&tankA,2);
					Tank_move(&tankA);
					draw_Tank(&tankA);
					if(flag==0)
					{
							Bullet_load(&bullet[newbullet_N++],&tankA);
							flag=1;
					}
					break;
			case 130: 
					Tank_turn(&tankA,0);
					Tank_move(&tankA);
					draw_Tank(&tankA);
					if(flag==0)
					{
							Bullet_load(&bullet[newbullet_N++],&tankA);
							flag=1;
					}
					break;			
			default:
				  flag=0;
					break;
		}
   if(tankA.speed==8)
			OSTimeDly ( 50, OS_OPT_TIME_DLY, & err );        //�������ʱ1000��ʱ�ӽ��ģ�1s��
	 else
		  OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );        //�������ʱ1000��ʱ�ӽ��ģ�1s��
		
	}
		
		
}


/*
*********************************************************************************************************
*                                          PAD2 TASK
*********************************************************************************************************
*/

static  void  AppTaskPad2 ( void * p_arg )
{
	OS_ERR      err;
//	OS_REG      value;
	u8 key2; 
	u8 flag2=0;
	(void)p_arg;
	while (DEF_TRUE) {                                 //�����壬ͨ��д��һ����ѭ��
		key2=JOYPAD2_Read();	
		switch(key2)
		{
			case 2:
					if(flag2==0)
					{
							Bullet_load(&bullet[newbullet_N++],&tankB);
							flag2=1;
					}
					break;			
			case 16: 
					Tank_turn(&tankB,1);
					Tank_move(&tankB);
					draw_Tank(&tankB);
			    flag2=0;
					break;
			case 32: 
					Tank_turn(&tankB,3);
					Tank_move(&tankB);
					draw_Tank(&tankB);
		     	flag2=0;
					break;
			case 64: 
					Tank_turn(&tankB,2);
					Tank_move(&tankB);
			    flag2=0;
					draw_Tank(&tankB);
					break;
			case 128: 
					Tank_turn(&tankB,0);
					Tank_move(&tankB);
					draw_Tank(&tankB);
			    flag2=0;
					break;		

			case 18: 
					Tank_turn(&tankB,1);
					Tank_move(&tankB);
					draw_Tank(&tankB);
					if(flag2==0)
					{
							Bullet_load(&bullet[newbullet_N++],&tankB);
							flag2=1;
					}
					break;
			case 34: 
					Tank_turn(&tankB,3);
					Tank_move(&tankB);
					draw_Tank(&tankB);
					if(flag2==0)
					{
						Bullet_load(&bullet[newbullet_N++],&tankB);
							flag2=1;
					}
					break;
			case 66: 
					Tank_turn(&tankB,2);
					Tank_move(&tankB);					
			    draw_Tank(&tankB);
					if(flag2==0)
					{
							Bullet_load(&bullet[newbullet_N++],&tankB);
							flag2=1;
					}
					break;
			case 130: 
					Tank_turn(&tankB,0);
					Tank_move(&tankB);
					draw_Tank(&tankB);
					if(flag2==0)
					{
							Bullet_load(&bullet[newbullet_N++],&tankB);
							flag2=1;
					}
					break;
			
			default:
				  flag2=0;
					break;
		}
   if(tankB.speed==8)
			OSTimeDly ( 50, OS_OPT_TIME_DLY, & err );        //�������ʱ1000��ʱ�ӽ��ģ�1s��
	 else
		  OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );        //�������ʱ1000��ʱ�ӽ��ģ�1s��
		
	}
}


/*
*********************************************************************************************************
*                                          Bullet TASK
*********************************************************************************************************
*/

static  void  AppTaskBullet ( void * p_arg )
{
	OS_ERR      err;

	(void)p_arg;


	while (DEF_TRUE) {                                 //�����壬ͨ��д��һ����ѭ��

		for(i = 0; i<newbullet_N; i++)
	  {  
		BulletMove(&bullet[i]);
	  BulletHittingWall(&bullet[i]);
		BulletHittingTank(&bullet[i],&tankA,&tankB,&RandomA, &RandomB);	
			if(bullet[i].disapper==1)
			  {
				  for(j=i;j<newbullet_N-1;j++)
            {bullet[j]=bullet[j+1];}
                    newbullet_N-=1;	
                       i-=1;													 										 
				}
		}

		OSTimeDly ( 50, OS_OPT_TIME_DLY, & err );      //�������ʱ1000��ʱ�ӽ��ģ�1s��
		
	}
}


/*
*********************************************************************************************************
*                                          Astar TASK
*********************************************************************************************************
*/

static  void  AppTaskAstar ( void * p_arg )
{
	OS_ERR      err;
	u16 X[10] = {8,158,307,12, 306,10,12, 260,29, 149};
	u16 Y[10] = {8,80, 230,100,9,  14,178,101,123,132};
	u8 randx = 0;
	u16 seedx = 0;
	u8 i = 0,t=0;	
	u16 x=13,dx=307,y=10,dy=230;
	int l[4] = {0,0,0,0};
	(void)p_arg;

	while (DEF_TRUE) {                                 //�����壬ͨ��д��һ����ѭ��

	while((x!=dx) || (y!=dy))
	{
		t++;
		if((!is_Wall(x+1,y)) && (x+1<313) && (y>7) && (y<233))
		{
			l[0] = abs(dx-(x+1)) + abs(dy-y);
		}
		else
		{
			l[0] = 20000;
		}
		if((!is_Wall(x,y+1)) && (x>7) && (y+1<313)&& (y+1<233))
		{
			l[1] = abs(dx-x) + abs(dy-(y+1));
		}
		else
		{
			l[1] = 20001;
		}
		if((!is_Wall(x-1,y)) && (x-1>7) && (y<233) && (y>7))
		{
			l[2] = abs(dx-(x-1)) + abs(dy-y);
		}
		else
		{
			l[2] = 20002;
		}
		if((!is_Wall(x,y-1)) && (x<313) && (x>7) && (y-1>7))
		{
			l[3] = abs(dx-x) + abs(dy-(y-1));
		}
		else
		{
			l[3] = 20003;
		}
		i = sort(l);
		switch(i)
		{
			case 0: 
				x = x+1;Tank_turn(&RandomA,3); break;
			case 1:
				y = y+1;Tank_turn(&RandomA,0);break;
			case 2: 
				x = x-1;Tank_turn(&RandomA,1);break;
			case 3: 
				y = y-1;Tank_turn(&RandomA,2);break;
			default :	LCD_SetColors(CYAN ,BLACK); ILI9341_SetPointPixel(x,y); break;
		}

		if(RandomA.blood > 0)
		{
			RandomA.x = x;
		  RandomA.y = y;
			Tank_move(&RandomA);
			draw_Tank(&RandomA);
			if(t==10)
			{
				Bullet_load(&bullet[newbullet_N++],&RandomA);
				t=0;
			}
  	}
		else
		{
			x = dx;
			y = dy;
			Tank_move(&RandomA);
			if(deadA==1)
			{
				deadA=0;
		    OSTimeDly ( 5000, OS_OPT_TIME_DLY, & err );      //�������ʱ1000��ʱ�ӽ��ģ�1s��
				RandomA.blood=1;
			}
		}
		OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );      //�������ʱ1000��ʱ�ӽ��ģ�1s��

	}
	  seedx = tankA.x;
		srand(seedx);
		randx = (u16)(rand()%10);
		dx = X[randx];
		dy = Y[randx];
		OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );      //�������ʱ1000��ʱ�ӽ��ģ�1s��
	}
}
/*
*********************************************************************************************************
*                                          Astar TASK
*********************************************************************************************************
*/
static  void  AppTaskAstar_B ( void * p_arg )
{
	OS_ERR      err;
	u16 X[10] = {8,158,307,12, 306,10,12, 260,29, 149};
	u16 Y[10] = {8,80, 230,100,9,  14,178,101,123,132};
	u8 randx = 0;
	u16 seedx = 0;
	u8 i = 0,t=0;	
	u16 dx=8,x=307,dy=8,y=230;
	int l[4] = {0,0,0,0};
	u16 pre[4] = {0};
	(void)p_arg;
	pre[0] = x;
	pre[1] = y;

	while (DEF_TRUE) {                                 //�����壬ͨ��д��һ����ѭ��

	while(((x!=dx) || (y!=dy)) && ((x != pre[2]) || (y != pre[3])))
	{
		t++;
		if((!is_Wall(x+1,y)) && (x+1<313) && (y>7) && (y<233))
		{
			l[0] = abs(dx-(x+1)) + abs(dy-y);
		}
		else
		{
			l[0] = 20000;
		}
		if((!is_Wall(x,y+1)) && (x>7) && (y+1<313)&& (y+1<233))
		{
			l[1] = abs(dx-x) + abs(dy-(y+1));
		}
		else
		{
			l[1] = 20001;
		}
		if((!is_Wall(x-1,y)) && (x-1>7) && (y<233) && (y>7))
		{
			l[2] = abs(dx-(x-1)) + abs(dy-y);
		}
		else
		{
			l[2] = 20002;
		}
		if((!is_Wall(x,y-1)) && (x<313) && (x>7) && (y-1>7))
		{
			l[3] = abs(dx-x) + abs(dy-(y-1));
		}
		else
		{
			l[3] = 20003;
		}
		i = sort(l);
		switch(i)
		{
			case 0: 
				x = x+1;Tank_turn(&RandomB,3); break;
			case 1:
				y = y+1;Tank_turn(&RandomB,0);break;
			case 2: 
				x = x-1;Tank_turn(&RandomB,1);break;
			case 3: 
				y = y-1;Tank_turn(&RandomB,2);break;
			default :	LCD_SetColors(CYAN ,BLACK); ILI9341_SetPointPixel(x,y); break;
		}

		if(RandomB.blood > 0)
		{
			pre[2] = pre[0];
			pre[3] = pre[1];
			pre[0] = x;
			pre[1] = y;
			RandomB.x = x;
	   	RandomB.y = y;
			Tank_move(&RandomB);
			draw_Tank(&RandomB);
			if(t==10)
			{
				Bullet_load(&bullet[newbullet_N++],&RandomB);
				t=0;
			}
  	}
		else
		{
			x = dx;
			y = dy;
			Tank_move(&RandomB);
		 if(deadB==1)
			{
				deadB=0;
		    OSTimeDly ( 5000, OS_OPT_TIME_DLY, & err );      //�������ʱ1000��ʱ�ӽ��ģ�1s��
				RandomB.blood=1;
			}
		}

		OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );      //�������ʱ1000��ʱ�ӽ��ģ�1s��

	}
	  seedx = tankA.x;
		srand(seedx);
		randx = (u16)(rand()%10);
		dx = X[randx];
		dy = Y[randx];
		OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );      //�������ʱ1000��ʱ�ӽ��ģ�1s��
	}
}
/*
*********************************************************************************************************
*                                          Package TASK
*********************************************************************************************************
*/

static  void  AppTaskPackage ( void * p_arg )
{
	OS_ERR      err;

	(void)p_arg;


	while (DEF_TRUE) {                                 //�����壬ͨ��д��һ����ѭ��
		
		Tank_eatPackage(&packX,&tankA);
		Tank_eatPackage(&packX,&tankB);
		
		draw_package(&packX);
		OSTimeDly ( 500, OS_OPT_TIME_DLY, & err );      //�������ʱ1000��ʱ�ӽ��ģ�1s��
		clear_package(&packX);
		OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );      //�������ʱ1000��ʱ�ӽ��ģ�1s��
		
	}

		
}

/*
*********************************************************************************************************
*                                          Dead TASK
*********************************************************************************************************
*/

static  void  AppTaskDead ( void * p_arg )
{
	OS_ERR      err;

	(void)p_arg;


	while (DEF_TRUE) {                                 //�����壬ͨ��д��һ����ѭ��
		
    if(tankA.blood<=0||tankB.blood<=0)
		{
			ILI9341_GramScan ( 6 );
			map_end();
			OSTaskSuspend ( &AppTaskPad1TCB, & err );                    //����
			OSTaskSuspend ( &AppTaskPad2TCB, & err );                    //����
			OSTaskSuspend ( &AppTaskBulletTCB, & err );                    //����
			OSTaskSuspend ( &AppTaskPackageTCB, & err );                    //����
			OSTaskSuspend ( &AppTaskAstarTCB, & err );                    //����		
			OSTaskSuspend ( &AppTaskAstar_BTCB, & err );                    //����					
		}
		if(RandomA.blood<=0)
		{
				deadA=1;
		}
		if(RandomB.blood<=0)
		{
				deadB=1;
		}
		OSTimeDly ( 500, OS_OPT_TIME_DLY, & err );      //�������ʱ1000��ʱ�ӽ��ģ�1s��
		
	}

}

