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

//OS_MEM  mem;                    //声明内存管理对象
//uint8_t ucArray [ 3 ] [ 20 ];   //声明内存分区大小


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

static  OS_TCB   AppTaskStartTCB;    //任务控制块
static  OS_TCB   AppTaskStartGameTCB;    //任务控制块

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

static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];       //任务堆栈
static  CPU_STK  AppTaskStartGameStk[APP_TASK_STARTGAME_STK_SIZE];       //任务堆栈
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

static  void  AppTaskStart  (void *p_arg);               //任务函数声明
static  void  AppTaskStartGame  (void *p_arg);               //任务函数声明
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
		 
	  JOYPAD_Init();			//手柄初始化
    JOYPAD2_Init();			//手柄初始化
		ILI9341_Init ();         //LCD 初始化
	
		LCD_SetFont(&Font8x16);
		LCD_SetColors(RED,BLACK);
		ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
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
    OSInit(&err);                                                           //初始化 uC/OS-III

	  /* 创建起始任务 */
    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                            //任务控制块地址
                 (CPU_CHAR   *)"App Task Start",                            //任务名称
                 (OS_TASK_PTR ) AppTaskStart,                               //任务函数
                 (void       *) 0,                                          //传递给任务函数（形参p_arg）的实参
                 (OS_PRIO     ) APP_TASK_START_PRIO,                        //任务的优先级
                 (CPU_STK    *)&AppTaskStartStk[0],                         //任务堆栈的基地址
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,               //任务堆栈空间剩下1/10时限制其增长
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,                    //任务堆栈空间（单位：sizeof(CPU_STK)）
                 (OS_MSG_QTY  ) 5u,                                         //任务可接收的最大消息数
                 (OS_TICK     ) 0u,                                         //任务的时间片节拍数（0表默认值OSCfg_TickRate_Hz/10）
                 (void       *) 0,                                          //任务扩展（0表不扩展）
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //任务选项
                 (OS_ERR     *)&err);                                       //返回错误类型

    OSStart(&err);                                                          //启动多任务管理（交由uC/OS-III控制）

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

    CPU_Init();                                                 //初始化 CPU 组件（时间戳、关中断时间测量和主机名）

    
	cpu_clk_freq = BSP_CPU_ClkFreq();                           //获取 CPU 内核时钟频率（SysTick 工作时钟）
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        //根据用户设定的时钟节拍频率计算 SysTick 定时器的计数值
    OS_CPU_SysTickInit(cnts);                                   //调用 SysTick 初始化函数，设置定时器计数值和启动定时器

    Mem_Init();                                                 //初始化内存管理组件（堆内存池和内存池表）

#if OS_CFG_STAT_TASK_EN > 0u                                    //如果使能（默认使能）了统计任务
    OSStatTaskCPUUsageInit(&err);                               //计算没有应用任务（只有空闲任务）运行时 CPU 的（最大）
#endif                                                          //容量（决定 OS_Stat_IdleCtrMax 的值，为后面计算 CPU 
                                                                //使用率使用）。
    CPU_IntDisMeasMaxCurReset();                                //复位（清零）当前最大关中断时间

    
    /* 配置时间片轮转调度 */		
    OSSchedRoundRobinCfg((CPU_BOOLEAN   )DEF_ENABLED,          //使能时间片轮转调度
		                     (OS_TICK       )0,                    //把 OSCfg_TickRate_Hz / 10 设为默认时间片值
												 (OS_ERR       *)&err );               //返回错误类型
    OSStart(&err);                                                          //启动多任务管理（交由uC/OS-III控制）
	  
		/* 创建 StartGame 任务 */
    OSTaskCreate((OS_TCB     *)&AppTaskStartGameTCB,                            //任务控制块地址
                 (CPU_CHAR   *)"App Task StartGame",                            //任务名称
                 (OS_TASK_PTR ) AppTaskStartGame,                               //任务函数
                 (void       *) 0,                                          //传递给任务函数（形参p_arg）的实参
                 (OS_PRIO     ) APP_TASK_STARTGAME_PRIO,                        //任务的优先级
                 (CPU_STK    *)&AppTaskStartGameStk[0],                         //任务堆栈的基地址
                 (CPU_STK_SIZE) APP_TASK_STARTGAME_STK_SIZE / 10,               //任务堆栈空间剩下1/10时限制其增长
                 (CPU_STK_SIZE) APP_TASK_STARTGAME_STK_SIZE,                    //任务堆栈空间（单位：sizeof(CPU_STK)）
                 (OS_MSG_QTY  ) 5u,                                         //任务可接收的最大消息数
                 (OS_TICK     ) 0u,                                         //任务的时间片节拍数（0表默认值OSCfg_TickRate_Hz/10）
                 (void       *) 0,                                          //任务扩展（0表不扩展）
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //任务选项
                 (OS_ERR     *)&err);                                       //返回错误类型
		OSTaskDel ( 0, & err );                     //删除起始任务本身，该任务不再运行
		
		
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
	while (DEF_TRUE) {	                      //任务体，通常写成一个死循环
		
		key=JOYPAD_Read();
		if(key==8)
		{
		map();
	  ILI9341_GramScan ( 7 );
		/* 创建 PAD1 任务 */
    OSTaskCreate((OS_TCB     *)&AppTaskPad1TCB,                             //任务控制块地址
                 (CPU_CHAR   *)"App Task Pad1",                             //任务名称
                 (OS_TASK_PTR ) AppTaskPad1,                                //任务函数
                 (void       *) 0,                                          //传递给任务函数（形参p_arg）的实参
                 (OS_PRIO     ) APP_TASK_PAD1_PRIO,                         //任务的优先级
                 (CPU_STK    *)&AppTaskPad1Stk[0],                          //任务堆栈的基地址
                 (CPU_STK_SIZE) APP_TASK_PAD1_STK_SIZE / 10,                //任务堆栈空间剩下1/10时限制其增长
                 (CPU_STK_SIZE) APP_TASK_PAD1_STK_SIZE,                     //任务堆栈空间（单位：sizeof(CPU_STK)）
                 (OS_MSG_QTY  ) 5u,                                         //任务可接收的最大消息数
                 (OS_TICK     ) 0u,                                         //任务的时间片节拍数（0表默认值）
                 (void       *) 0,                                          //任务扩展（0表不扩展）
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //任务选项
                 (OS_ERR     *)&err);                                       //返回错误类型
		
		/* 创建 PAD2 任务 */
    OSTaskCreate((OS_TCB     *)&AppTaskPad2TCB,                             //任务控制块地址
                 (CPU_CHAR   *)"App Task Pad2",                             //任务名称
                 (OS_TASK_PTR ) AppTaskPad2,                                //任务函数
                 (void       *) 0,                                          //传递给任务函数（形参p_arg）的实参
                 (OS_PRIO     ) APP_TASK_PAD2_PRIO,                         //任务的优先级
                 (CPU_STK    *)&AppTaskPad2Stk[0],                          //任务堆栈的基地址
                 (CPU_STK_SIZE) APP_TASK_PAD2_STK_SIZE / 10,                //任务堆栈空间剩下1/10时限制其增长
                 (CPU_STK_SIZE) APP_TASK_PAD2_STK_SIZE,                     //任务堆栈空间（单位：sizeof(CPU_STK)）
                 (OS_MSG_QTY  ) 5u,                                         //任务可接收的最大消息数
                 (OS_TICK     ) 0u,                                         //任务的时间片节拍数（0表默认值）
                 (void       *) 0,                                          //任务扩展（0表不扩展）
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //任务选项
                 (OS_ERR     *)&err);                                       //返回错误类型								 

		/* 创建 BULLET 任务 */
    OSTaskCreate((OS_TCB     *)&AppTaskBulletTCB,                             //任务控制块地址
                 (CPU_CHAR   *)"App Task Bullet",                             //任务名称
                 (OS_TASK_PTR ) AppTaskBullet,                                //任务函数
                 (void       *) 0,                                          //传递给任务函数（形参p_arg）的实参
                 (OS_PRIO     ) APP_TASK_BULLET_PRIO,                         //任务的优先级
                 (CPU_STK    *)&AppTaskBulletStk[0],                          //任务堆栈的基地址
                 (CPU_STK_SIZE) APP_TASK_BULLET_STK_SIZE / 10,                //任务堆栈空间剩下1/10时限制其增长
                 (CPU_STK_SIZE) APP_TASK_BULLET_STK_SIZE,                     //任务堆栈空间（单位：sizeof(CPU_STK)）
                 (OS_MSG_QTY  ) 5u,                                         //任务可接收的最大消息数
                 (OS_TICK     ) 0u,                                         //任务的时间片节拍数（0表默认值）
                 (void       *) 0,                                          //任务扩展（0表不扩展）
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //任务选项
                 (OS_ERR     *)&err);                                       //返回错误类型
		/* 创建 DEAD 任务 */
    OSTaskCreate((OS_TCB     *)&AppTaskDeadTCB,                             //任务控制块地址
                 (CPU_CHAR   *)"App Task Dead",                             //任务名称
                 (OS_TASK_PTR ) AppTaskDead,                                //任务函数
                 (void       *) 0,                                          //传递给任务函数（形参p_arg）的实参
                 (OS_PRIO     ) APP_TASK_DEAD_PRIO,                         //任务的优先级
                 (CPU_STK    *)&AppTaskDeadStk[0],                          //任务堆栈的基地址
                 (CPU_STK_SIZE) APP_TASK_DEAD_STK_SIZE / 10,                //任务堆栈空间剩下1/10时限制其增长
                 (CPU_STK_SIZE) APP_TASK_DEAD_STK_SIZE,                     //任务堆栈空间（单位：sizeof(CPU_STK)）
                 (OS_MSG_QTY  ) 5u,                                         //任务可接收的最大消息数
                 (OS_TICK     ) 0u,                                         //任务的时间片节拍数（0表默认值）
                 (void       *) 0,                                          //任务扩展（0表不扩展）
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //任务选项
                 (OS_ERR     *)&err);                                       //返回错误类型
		/* 创建 ASTAR 任务 */
    OSTaskCreate((OS_TCB     *)&AppTaskAstarTCB,                             //任务控制块地址
                 (CPU_CHAR   *)"App Task Astar",                             //任务名称
                 (OS_TASK_PTR ) AppTaskAstar,                                //任务函数
                 (void       *) 0,                                          //传递给任务函数（形参p_arg）的实参
                 (OS_PRIO     ) APP_TASK_ASTAR_PRIO,                         //任务的优先级
                 (CPU_STK    *)&AppTaskAstarStk[0],                          //任务堆栈的基地址
                 (CPU_STK_SIZE) APP_TASK_ASTAR_STK_SIZE / 10,                //任务堆栈空间剩下1/10时限制其增长
                 (CPU_STK_SIZE) APP_TASK_ASTAR_STK_SIZE,                     //任务堆栈空间（单位：sizeof(CPU_STK)）
                 (OS_MSG_QTY  ) 5u,                                         //任务可接收的最大消息数
                 (OS_TICK     ) 0u,                                         //任务的时间片节拍数（0表默认值）
                 (void       *) 0,                                          //任务扩展（0表不扩展）
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //任务选项
                 (OS_ERR     *)&err);                                       //返回错误类型
   
								 OSTaskCreate((OS_TCB     *)&AppTaskAstar_BTCB,                             //任务控制块地址
                 (CPU_CHAR   *)"App Task Astar_B",                             //任务名称
                 (OS_TASK_PTR ) AppTaskAstar_B,                                //任务函数
                 (void       *) 0,                                          //传递给任务函数（形参p_arg）的实参
                 (OS_PRIO     ) APP_TASK_ASTAR_B_PRIO,                         //任务的优先级
                 (CPU_STK    *)&AppTaskAstar_BStk[0],                          //任务堆栈的基地址
                 (CPU_STK_SIZE) APP_TASK_ASTAR_B_STK_SIZE / 10,                //任务堆栈空间剩下1/10时限制其增长
                 (CPU_STK_SIZE) APP_TASK_ASTAR_B_STK_SIZE,                     //任务堆栈空间（单位：sizeof(CPU_STK)）
                 (OS_MSG_QTY  ) 5u,                                         //任务可接收的最大消息数
                 (OS_TICK     ) 0u,                                         //任务的时间片节拍数（0表默认值）
                 (void       *) 0,                                          //任务扩展（0表不扩展）
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //任务选项
                 (OS_ERR     *)&err);                                       //返回错误类型
//	
//		/* 创建 PACKAGE 任务 */
    OSTaskCreate((OS_TCB     *)&AppTaskPackageTCB,                             //任务控制块地址
                 (CPU_CHAR   *)"App Task Package",                             //任务名称
                 (OS_TASK_PTR ) AppTaskPackage,                                //任务函数
                 (void       *) 0,                                          //传递给任务函数（形参p_arg）的实参
                 (OS_PRIO     ) APP_TASK_PACKAGE_PRIO,                         //任务的优先级
                 (CPU_STK    *)&AppTaskPackageStk[0],                          //任务堆栈的基地址
                 (CPU_STK_SIZE) APP_TASK_PACKAGE_STK_SIZE / 10,                //任务堆栈空间剩下1/10时限制其增长
                 (CPU_STK_SIZE) APP_TASK_PACKAGE_STK_SIZE,                     //任务堆栈空间（单位：sizeof(CPU_STK)）
                 (OS_MSG_QTY  ) 5u,                                         //任务可接收的最大消息数
                 (OS_TICK     ) 0u,                                         //任务的时间片节拍数（0表默认值）
                 (void       *) 0,                                          //任务扩展（0表不扩展）
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //任务选项
                 (OS_ERR     *)&err);                                       //返回错误类型

					OSTaskDel ( 0, & err );                     //删除起始任务本身，该任务不再运行
					}
				  OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );        //相对性延时1000个时钟节拍（1s）
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

	while (DEF_TRUE) {                                   //任务体，通常写成一个死循环
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
			OSTimeDly ( 50, OS_OPT_TIME_DLY, & err );        //相对性延时1000个时钟节拍（1s）
	 else
		  OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );        //相对性延时1000个时钟节拍（1s）
		
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
	while (DEF_TRUE) {                                 //任务体，通常写成一个死循环
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
			OSTimeDly ( 50, OS_OPT_TIME_DLY, & err );        //相对性延时1000个时钟节拍（1s）
	 else
		  OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );        //相对性延时1000个时钟节拍（1s）
		
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


	while (DEF_TRUE) {                                 //任务体，通常写成一个死循环

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

		OSTimeDly ( 50, OS_OPT_TIME_DLY, & err );      //相对性延时1000个时钟节拍（1s）
		
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

	while (DEF_TRUE) {                                 //任务体，通常写成一个死循环

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
		    OSTimeDly ( 5000, OS_OPT_TIME_DLY, & err );      //相对性延时1000个时钟节拍（1s）
				RandomA.blood=1;
			}
		}
		OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );      //相对性延时1000个时钟节拍（1s）

	}
	  seedx = tankA.x;
		srand(seedx);
		randx = (u16)(rand()%10);
		dx = X[randx];
		dy = Y[randx];
		OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );      //相对性延时1000个时钟节拍（1s）
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

	while (DEF_TRUE) {                                 //任务体，通常写成一个死循环

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
		    OSTimeDly ( 5000, OS_OPT_TIME_DLY, & err );      //相对性延时1000个时钟节拍（1s）
				RandomB.blood=1;
			}
		}

		OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );      //相对性延时1000个时钟节拍（1s）

	}
	  seedx = tankA.x;
		srand(seedx);
		randx = (u16)(rand()%10);
		dx = X[randx];
		dy = Y[randx];
		OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );      //相对性延时1000个时钟节拍（1s）
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


	while (DEF_TRUE) {                                 //任务体，通常写成一个死循环
		
		Tank_eatPackage(&packX,&tankA);
		Tank_eatPackage(&packX,&tankB);
		
		draw_package(&packX);
		OSTimeDly ( 500, OS_OPT_TIME_DLY, & err );      //相对性延时1000个时钟节拍（1s）
		clear_package(&packX);
		OSTimeDly ( 100, OS_OPT_TIME_DLY, & err );      //相对性延时1000个时钟节拍（1s）
		
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


	while (DEF_TRUE) {                                 //任务体，通常写成一个死循环
		
    if(tankA.blood<=0||tankB.blood<=0)
		{
			ILI9341_GramScan ( 6 );
			map_end();
			OSTaskSuspend ( &AppTaskPad1TCB, & err );                    //挂起
			OSTaskSuspend ( &AppTaskPad2TCB, & err );                    //挂起
			OSTaskSuspend ( &AppTaskBulletTCB, & err );                    //挂起
			OSTaskSuspend ( &AppTaskPackageTCB, & err );                    //挂起
			OSTaskSuspend ( &AppTaskAstarTCB, & err );                    //挂起		
			OSTaskSuspend ( &AppTaskAstar_BTCB, & err );                    //挂起					
		}
		if(RandomA.blood<=0)
		{
				deadA=1;
		}
		if(RandomB.blood<=0)
		{
				deadB=1;
		}
		OSTimeDly ( 500, OS_OPT_TIME_DLY, & err );      //相对性延时1000个时钟节拍（1s）
		
	}

}

