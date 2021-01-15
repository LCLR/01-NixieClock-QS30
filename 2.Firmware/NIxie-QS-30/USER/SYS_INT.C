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

void SYS_INT(void)//��ʼ������
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�
	usart1_init();//���ڳ�ʼ��
	usart2_init();
//	usart3_init();
	delay_init();//��ʱ������ʼ��
	WS_Init();    //RGB��IO��ʼ��
	WS2812B_Init();//WS2812��ʼ��
	CD4514_Init();//CD4514��ʼ��
	LED_Init();//LED��ʼ��
	DS3231_Init();//ʱ��оƬ��ʼ��
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