#include "SYS_INT.h"

#include "led.h"
#include "delay.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"	 
#include "adc.h"
#include "dma.h"
#include "WS2812B.h"
#include "CD4514.h"
#include "ds3231.h"

extern u16 Save_data[4];
extern u8 tmp_buf[33];

void SYS_INT(void)//初始化函数
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级
	usart1_init();//串口初始化
	usart2_init();
//	usart3_init();
	delay_init();//延时函数初始化
	WS_Init();    //RGB的IO初始化
	WS2812B_Init();//WS2812初始化
	CD4514_Init();//CD4514初始化
	LED_Init();//LED初始化
	DS3231_Init();//时钟芯片初始化
}

u16 convert_data_GO(u8 res)
{
	if(res<30)
		return 1;
	if(res>230)
		return 2;
	else
		return 3;
}

void Direct_Choice(void)
{
	switch(10*convert_data_GO(Save_data[1])+convert_data_GO(Save_data[0]))
		{

		case 13:
			tmp_buf[0]='U';
		break;
				
		case 23:
			tmp_buf[0]='B';
		break;
				
		case 31:
			tmp_buf[0]='R';
		break;
				
		case 32:
			tmp_buf[0]='L';
		break;
		default:
			tmp_buf[0]='S';
		break;
	}
}
