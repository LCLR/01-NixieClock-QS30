#ifndef __CD4514_H
#define	__CD4514_H
#include "sys.h"

//λ����IO
#define ST1 PAout(4)// PA4
#define ST2 PAout(5)// PA5
#define ST3 PAout(6)// PA6
#define ST4 PAout(7)// PA7
#define ST5 PAout(9)// PA9
#define ST6 PAout(10)// PA10

//����IO
#define D1 PBout(8)// PB8
#define D2 PBout(9)// PB9
#define D3 PBout(13)// PB13
#define D4 PBout(14)// PB14

//ʹ��IO
#define INT PAout(12)// PB14


//��������
void CD4514_Init(void);//IO�˿ڳ�ʼ��
void CD4514_ON(void);  //ʹ�ܿ���
void CD4514_OFF(void);//ʹ�ܿ���
void QS30_Show(u16 ST,u8 Num);//QS��ʾ
#endif 

