#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;				 //LED-->PB �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	//�����趨������ʼ��GPIOB.5

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_11;				 //LED-->PB �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	//�����趨������ʼ��GPIOB.5
	

	GPIO_SetBits(GPIOB,GPIO_Pin_6);//PB LED�����
	GPIO_SetBits(GPIOB,GPIO_Pin_7);//PB LED�����
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PB LED�����
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);//PB LED�����
}
//LED_delay
void Delay_ms_led(u16 nms)
{	
	uint16_t i,j;
	for(i=0;i<nms;i++)
		for(j=0;j<8500;j++);
} 

//-------LED��˸------

void LED_FLASH(void)//LED
{
	LED1=1;
	Delay_ms_led(100);
	LED1=0;
	Delay_ms_led(100);
}









