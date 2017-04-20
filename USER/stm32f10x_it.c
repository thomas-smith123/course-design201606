/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "stm32f10x_exti.h"
#include "led.h"
#include "pcf8563.h"
#include "oled.h"
#include "key.h"
#include "delay.h" 

void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}
void EXTI4_IRQHandler(void)
{
	u8 i=0;
	TIME today;
	today.year=0;	today.month=1;
	today.day=1;	today.hour=0;
	today.mint=0;	today.second=0;
	OLED_ShowNum(0,0,2,1,8);//÷
	OLED_ShowNum(8,0,0,1,8);		
	OLED_ShowCHinese(32,0,7);//year
	OLED_ShowCHinese(64,0,8);//month	
	OLED_ShowCHinese(96,0,9);//»’		
	OLED_ShowCHinese(16,2,10);// ±	
	OLED_ShowCHinese(48,2,11);//∑÷
	OLED_ShowCHinese(80,2,12);//√Î
	OLED_ShowNum(16,0,today.year/10,1,8);
	OLED_ShowNum(24,0,today.year%10,1,8);
	OLED_ShowNum(48,0,today.month/10,1,8);
	OLED_ShowNum(56,0,today.month%10,1,8);
	OLED_ShowNum(80,0,today.day/10,1,8);
	OLED_ShowNum(88,0,today.day%10,1,8);
	OLED_ShowNum(0,2,today.hour/10,1,8);
	OLED_ShowNum(8,2,today.hour%10,1,8);
	OLED_ShowNum(32,2,today.mint/10,1,8);
	OLED_ShowNum(40,2,today.mint%10,1,8);
	OLED_ShowNum(64,2,today.second/10,1,8);
	OLED_ShowNum(72,2,today.second%10,1,8);
	if(EXTI_GetITStatus(EXTI_Line4) != RESET) //»∑±£ «∑Ò≤˙…˙¡ÀEXTI Line÷–∂œ
	{
		// LED1 »°∑¥		
		LED1_TOGGLE;
		OLED_ShowCHinese(16,5,13);//…Ë
		OLED_ShowCHinese(32,5,14);//÷√
		while(1)
		{	
			if(!Key3_Scan(GPIOE,GPIO_Pin_8))
			{
				i++;
				if(i==7)i=0;
				switch (i)
				{
					case 1:OLED_ShowCHinese(0,5,12);
						break;//√Î
					case 2:OLED_ShowCHinese(0,5,11);
						break;//∑÷
					case 3:OLED_ShowCHinese(0,5,10);
						break;// ±
					case 4:OLED_ShowCHinese(0,5,9);
						break;//»’
					case 5:OLED_ShowCHinese(0,5,8);
						break;//‘¬
					case 6:OLED_ShowCHinese(0,5,7);
						break;//ƒÍ					
				}
			}
			if(!Key3_Scan(GPIOE,GPIO_Pin_9))
			{
				switch (i)
				{
					case 1:	today.second++;
									OLED_ShowNum(64,2,today.second/10,1,8);
									OLED_ShowNum(72,2,today.second%10,1,8);
									if(today.second==60)
										today.second=0;
									break;
					case 2:today.mint++;
									OLED_ShowNum(32,2,today.mint/10,1,8);
									OLED_ShowNum(40,2,today.mint%10,1,8);
									if(today.mint==60)
										today.mint=0;
									break;
					case 3:today.hour++;
									OLED_ShowNum(0,2,today.hour/10,1,8);
									OLED_ShowNum(8,2,today.hour%10,1,8);
									if(today.hour==24)
										today.hour=0;
									break;										
					case 4:today.day++;
									OLED_ShowNum(80,0,today.day/10,1,8);
									OLED_ShowNum(88,0,today.day%10,1,8);										
									if(today.day==31)
										today.day=1;
									break;
					case 5:today.month++;
									OLED_ShowNum(48,0,today.month/10,1,8);
									OLED_ShowNum(56,0,today.month%10,1,8);
									if(today.month==12)
										today.month=1;
									break;
					case 6:today.year++;
									OLED_ShowNum(16,0,today.year/10,1,8);
									OLED_ShowNum(24,0,today.year%10,1,8);
									if(today.year==99)
										today.year=0;
									break;
				}
				PCF_SetTime(today.year,today.month,today.day,today.hour,today.mint,today.second);
			}
				if(!Key2_Scan(GPIOE,GPIO_Pin_10))
				{	
					OLED_ShowCHinese(16,5,15);//…Ë
					OLED_ShowCHinese(32,5,15);//÷√
					OLED_ShowCHinese(0,5,15);//÷√
					EXTI_ClearITPendingBit(EXTI_Line4);
					break;
				}
		} 
	}
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
