#include "PIR.h"

void PIR_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

int GetPIR_Sta(void)
{
	if(PIR_Sta==1)
		return 1;
	else
		return 0;
}


