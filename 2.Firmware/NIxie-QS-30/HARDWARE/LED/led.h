#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
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
#define LED1 PBout(6)// PB6
#define LED2 PBout(7)// PB7
#define RGB_H PAout(1)// PB7
#define RGB_M PAout(11)// PB7

void LED_Init(void);//��ʼ��
void Delay_ms_led(u16 nms);//��ʱ
//��˸����
void LED_FLASH(void);	 				    
#endif
