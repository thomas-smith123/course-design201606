#include "stm32f10x.h"
#ifndef __led_H
#define __led_H	
#define ON  0
#define OFF 1
/* ???,??????????? */
#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_5)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_6)

#define LED1_TOGGLE		digitalToggle(GPIOE,GPIO_Pin_5)
#define LED1_OFF			digitalHi(GPIOE,GPIO_Pin_5)
#define LED1_ON				digitalLo(GPIOE,GPIO_Pin_5)
#define	digitalHi(p,i)				{p->BSRR=i;}			//����Ϊ�ߵ�ƽ		
#define digitalLo(p,i)				{p->BRR	=i;}				//����͵�ƽ
#define digitalToggle(p,i)		{p->ODR ^=i;}			//�����ת״̬

void LED_GPIO_Config(void);
#endif
