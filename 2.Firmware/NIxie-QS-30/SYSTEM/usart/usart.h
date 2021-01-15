#ifndef __USART_H
#define __USART_H
#include<stm32f10x.h>

void usart1_init(void);
void usart2_init(void);
void usart3_init(void);
void UART_PutStr(USART_TypeDef* USARTx,uint8_t *str);
void UART_PutChar(USART_TypeDef* USARTx,uint8_t Data);

extern uint8_t usart_sta,Get_Uchar;
#endif
