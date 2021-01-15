#ifndef __SYS_INT_H
#define __SYS_INT_H
#include "stm32f10x.h"
//-----初始化函数------
void SYS_INT(void);//所有硬件初始化
u16 convert_data_GO(u8 res);//方向数据转化函数
void Direct_Choice(void);//方向选择函数
#endif