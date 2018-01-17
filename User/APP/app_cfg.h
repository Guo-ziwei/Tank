/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                           (c) Copyright 2009-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                         Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : JJL
*                 EHS
*                 DC
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/

#define  APP_CFG_SERIAL_EN                          DEF_DISABLED          // Modified by fire ��ԭ�� DEF_ENABLED��

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/
#define  APP_TASK_START_PRIO                        2            //�������ȼ�
#define  APP_TASK_STARTGAME_PRIO                        3            //�������ȼ�
#define  APP_TASK_PAD1_PRIO                         3
#define  APP_TASK_PAD2_PRIO                         3

#define  APP_TASK_BULLET_PRIO                         4

#define  APP_TASK_PACKAGE_PRIO                         4
#define  APP_TASK_ASTAR_PRIO                         5
#define  APP_TASK_ASTAR_B_PRIO                         5
#define  APP_TASK_DEAD_PRIO                         7
/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE                    128          //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
#define  APP_TASK_STARTGAME_STK_SIZE                    128          //�����ջ�ռ䣨��λ��sizeof(CPU_STK)��
#define  APP_TASK_PAD1_STK_SIZE                     512   
#define  APP_TASK_PAD2_STK_SIZE                     512
#define  APP_TASK_BULLET_STK_SIZE                     512 
#define  APP_TASK_PACKAGE_STK_SIZE                     512 
#define  APP_TASK_ASTAR_STK_SIZE                     512 
#define  APP_TASK_ASTAR_B_STK_SIZE                     512 
#define  APP_TASK_DEAD_STK_SIZE                     512 
/*
*********************************************************************************************************
*                                    BSP CONFIGURATION: RS-232
*********************************************************************************************************
*/

#define  BSP_CFG_SER_COMM_SEL             			BSP_SER_COMM_UART_02
#define  BSP_CFG_TS_TMR_SEL                         2


/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/
#if 0
#define  TRACE_LEVEL_OFF                            0
#define  TRACE_LEVEL_INFO                           1
#define  TRACE_LEVEL_DEBUG                          2
#endif

#define  APP_TRACE_LEVEL                            TRACE_LEVEL_INFO
#define  APP_TRACE                                  BSP_Ser_Printf

#define  APP_TRACE_INFO(x)            ((APP_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_TRACE x) : (void)0)
#define  APP_TRACE_DEBUG(x)           ((APP_TRACE_LEVEL >= TRACE_LEVEL_DEBUG) ? (void)(APP_TRACE x) : (void)0)


#endif




