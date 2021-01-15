#ifndef __WS2812B_H
#define	__WS2812B_H

#include "stm32f10x.h"
#include "delay.h"	


#define White       0xFFFFFF  // 白色
#define Black       0x000000  // 黑色
#define Red         0x00ff00  // 红色
#define Green       0xff0000  // 绿色
#define Blue        0x0000ff  // 蓝色


#define nWs 6		// 有多少颗WS2811级联

extern unsigned long WsDat[];

extern void WS_Init(void);
void WS_Set1(unsigned long dat);
void RGB_Set(uint16_t R,uint16_t G,uint16_t B);
extern void WS_SetAll(void);
extern u32 ColorToColor(unsigned long color0, unsigned long color1);

void rainbow(uint8_t wait);
void  setAllPixelColor(uint8_t r, uint8_t g, uint8_t b);
void  setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
void SetPixelColor(uint16_t n, uint32_t c);
uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
uint32_t Wheel(uint8_t WheelPos);
void rainbowCycle(uint8_t wait) ;
void theaterChase(uint32_t c, uint8_t wait);
void theaterChaseRainbow(uint8_t wait);
void colorWipe(uint32_t c, uint8_t wait);
void WS2812B_Test(void);
void WS2812B_Init(void);

#endif /* __LED_H */
