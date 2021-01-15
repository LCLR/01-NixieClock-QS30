#include "stm32f10x.h"
#include "SYS_INT.h"
#include "led.h"
#include "adc.h"
#include "delay.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"	  
#include "dma.h"
#include "WS2812B.h"
#include "CD4514.h"
#include "ds3231.h"
#include "PIR.h"



u16 Save_data[4];
u8 tmp_buf[33];


/************************************************
25184OK
************************************************/
void main(void)
{
	u16 i,j;
	u16 Hou,Min,Sec;

	SYS_INT();//初始化函数
	CD4514_ON();
	PIR_Init();
	DS3231_Set(18,11,12,22,31,00);//设置时间	
	RGB_H=0;
	RGB_M=0;

//	rainbowCycle(8); //9LED 不同闪烁呼吸灯参数 时间ms
	CD4514_OFF();	
	while(1)	//
	{
		
//		rainbowCycle(2); //9LED 不同闪烁呼吸灯参数 时间ms
		if(GetPIR_Sta())
			{
				LED1=0;
				for(i=0;i<=9;i++)
				{
					QS30_Show(1,i);//QS显示
					QS30_Show(2,i);//QS显示
					QS30_Show(3,i);//QS显示
					QS30_Show(4,i);//QS显示
					QS30_Show(5,i);//QS显示
					QS30_Show(6,i);//QS显示
					delay_ms(500);		
					CD4514_OFF();
				}
			}
			LED1=1;
	}
}