#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;				 //LED-->PB 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	//根据设定参数初始化GPIOB.5

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_11;				 //LED-->PB 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	//根据设定参数初始化GPIOB.5
	

	GPIO_SetBits(GPIOB,GPIO_Pin_6);//PB LED输出高
	GPIO_SetBits(GPIOB,GPIO_Pin_7);//PB LED输出高
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PB LED输出高
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);//PB LED输出高
}
//LED_delay
void Delay_ms_led(u16 nms)
{	
	uint16_t i,j;
	for(i=0;i<nms;i++)
		for(j=0;j<8500;j++);
} 

//-------LED闪烁------

void LED_FLASH(void)//LED
{
	LED1=1;
	Delay_ms_led(100);
	LED1=0;
	Delay_ms_led(100);
}









