#include "delay.h"
//#include "sys.h"
#include "oled.h"
#include "led.h"
#include "key.h"
#include "pcf8563.h"
#include "KeyExti.h"
#define CLI() __set_PRIMASK(1)		/* πÿ±’◊‹÷–∂œ */  
#define SEI() __set_PRIMASK(0)				/* ø™∑≈◊‹÷–∂œ */ 
 int main(void)
  {	
		unsigned char i;
//		unsigned char choose=0,increase=0;
		TIME today;
		TIME	tomorrow;
		today.day=1;		today.hour=0;		
		today.mint=0;		today.month=1;	
		today.second=0;	
		today.year=0;
		tomorrow=today;		tomorrow.hour=2;
		tomorrow.mint=30;		tomorrow.second=31;
		delay_init();	    	 //—” ±∫Ø ˝≥ı ºªØ	
		Key2_GPIO_Config();
		LED_GPIO_Config();	
		KeyExti_Config();		 //…Ë÷√NVIC÷–∂œ∑÷◊È2:2Œª«¿’º”≈œ»º∂£¨2ŒªœÏ”¶”≈œ»º∂ 	
		//LED_Init();			     //LED∂Àø⁄≥ı ºªØ
		OLED_Init();			//≥ı ºªØOLED 
		OLED_Clear(); 
		CLI();
		SEI();		
		/*******Name******/
		OLED_ShowCHinese(0,0,0);
		OLED_ShowCHinese(18,0,1);
		OLED_ShowCHinese(36,0,2);
		OLED_ShowCHinese(54,0,3);
		OLED_ShowCHinese(72,0,4);
		OLED_ShowCHinese(90,0,5);
		OLED_ShowCHinese(108,0,6);
		delay_ms(16000);
		OLED_Clear();
		PCF_SetTime(today.year,today.month,today.day,today.hour,today.mint,today.second);
		OLED_ShowNum(0,0,2,1,8);//÷
		OLED_ShowNum(8,0,0,1,8);		
		OLED_ShowCHinese(32,0,7);//year
		OLED_ShowCHinese(64,0,8);//month	
		OLED_ShowCHinese(96,0,9);//»’		
		OLED_ShowCHinese(16,2,10);// ±	
		OLED_ShowCHinese(48,2,11);//∑÷
		OLED_ShowCHinese(80,2,12);//√Î
	while(1) 
	{
		if(Key2_Scan(GPIOE,GPIO_Pin_11))
		{
			today=PCF8563_GetTime();
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
			tomorrow=today;		tomorrow.hour=2;
			tomorrow.mint=30;		tomorrow.second=31;
		}
		else
			{		
				for(i=0;i<19;i++)
					delay_us(50000);
				tomorrow.second=tomorrow.second+1;
				if(tomorrow.second==60)
				{
					tomorrow.second=0;
					tomorrow.mint++;
					if(tomorrow.mint==60)
					{
						tomorrow.mint=0;
						tomorrow.hour++;
						if(tomorrow.hour==24)
						{
							tomorrow.hour=0;
							tomorrow.day++;
							if(tomorrow.day==31)
							{
								tomorrow.day=1;
								tomorrow.month++;
							}
						}
						
					}
				}
				i=0;
				OLED_ShowNum(16,0,tomorrow.year/10,1,8);
				OLED_ShowNum(24,0,tomorrow.year%10,1,8);
				OLED_ShowNum(48,0,tomorrow.month/10,1,8);
				OLED_ShowNum(56,0,tomorrow.month%10,1,8);
				OLED_ShowNum(80,0,tomorrow.day/10,1,8);
				OLED_ShowNum(88,0,tomorrow.day%10,1,8);
				OLED_ShowNum(0,2,tomorrow.hour/10,1,8);
				OLED_ShowNum(8,2,tomorrow.hour%10,1,8);
				OLED_ShowNum(32,2,tomorrow.mint/10,1,8);
				OLED_ShowNum(40,2,tomorrow.mint%10,1,8);
				OLED_ShowNum(64,2,tomorrow.second/10,1,8);
				OLED_ShowNum(72,2,tomorrow.second%10,1,8);
				}		
		}
	}	
