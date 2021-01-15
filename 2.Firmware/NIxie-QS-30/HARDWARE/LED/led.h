#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
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
#define LED1 PBout(6)// PB6
#define LED2 PBout(7)// PB7
#define RGB_H PAout(1)// PB7
#define RGB_M PAout(11)// PB7

void LED_Init(void);//初始化
void Delay_ms_led(u16 nms);//延时
//闪烁函数
void LED_FLASH(void);	 				    
#endif
