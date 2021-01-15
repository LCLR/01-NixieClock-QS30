#include "CD4514.h"
#include "sys.h"
#include "delay.h"

void CD4514_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	
	//端口时钟，使能
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE );	 

	// -------------------------------端口配置--------------------------
	//ST系列端口 1~6
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_10;// CONTROL
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					// 根据设定参数初始化
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);//PA 4输出低
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);//PA 5输出低
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);//PA 6输出低
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);//PA 7输出低
	GPIO_ResetBits(GPIOA,GPIO_Pin_9);//PA 9输出低
	GPIO_ResetBits(GPIOA,GPIO_Pin_10);//PA 10输出低

	//数据系列端口 1~4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_13|GPIO_Pin_14;// DATA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					// 根据设定参数初始化
	
	//使能端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;// INT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					// 根据设定参数初始化
}

void CD4514_ON(void)//使能开关
{
		INT=0;
}

void CD4514_OFF(void)
{
		INT=1;
}

void QS30_Show(u16 ST,u8 Num)
{
	CD4514_OFF();	
	switch(ST)
	{
		case 1:ST1=1;break;
		case 2:ST2=1;break;
		case 3:ST3=1;break;
		case 4:ST4=1;break;
		case 5:ST5=1;break;
		case 6:ST6=1;break;
	}
	
//	D4 = (Num&0x04);
//	D3 = (Num&0x03);
//	D2 = (Num&0x02);
//	D1 = (Num&0x01);
	
	if(Num&0x01)	D1 = 1;
	else					D1 = 0;
	
	if(Num&0x02)	D2 = 1;
	else					D2 = 0;
	
	if(Num&0x04)	D3 = 1;
	else					D3 = 0;
	
	if(Num&0x08)	D4 = 1;
	else					D4 = 0;
	
	switch(ST)
	{
		case 1:ST1=0;break;
		case 2:ST2=0;break;
		case 3:ST3=0;break;
		case 4:ST4=0;break;
		case 5:ST5=0;break;
		case 6:ST6=0;break;
	}
	
	{
		D1 = 1;
		D2 = 1;
		D3 = 1;
		D4 = 1;
	}
	
	CD4514_ON();
}








