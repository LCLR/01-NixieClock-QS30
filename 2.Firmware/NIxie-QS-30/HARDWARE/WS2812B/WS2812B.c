#include "WS2812B.h"
#include "sys.h"
#include "delay.h"
/* 显存 */                //B R G
unsigned long WsDat[nWs]={0x110011,0x0C000C,0x030003};
//                          0x000000,0x000000,0x000000,
//                          0x001111,0x000C0C,0x000303,
//                          0x000000,0x000000,0x000000};

													
#define LED_PIN PAout(0)
#define PIXEL_MAX 6																				
/**************************************************************************************
* IO初始化（移植时请修改）
**************************************************************************************/
void WS_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	
	//端口时钟，使能
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );	 

	// 端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				// PIN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					// 根据设定参数初始化 
}

/**************************
* 内部延时
***************************/
void delay2us()
{
	unsigned char i;
	i=3;
	while(i)
	{
		i--;
	}
	
}
void delay05us()
{
	unsigned char i;
	i=1;
	while(i)
	{
		i--;
	}
}

/***************************
* 发送一比特
****************************/
void TX0()  	{ LED_PIN = 1; delay05us(); LED_PIN = 0; delay2us(); } // 发送0
void TX1()  	{ LED_PIN = 1; delay2us();  LED_PIN = 0; delay05us(); } // 发送1
void WS_Reset() { LED_PIN = 0; delay_us(60);LED_PIN = 1; LED_PIN = 0;   }

/**************************************************************************************
* 发送一字节
**************************************************************************************/
void WS_Set1(unsigned long dat)
{
	unsigned char i;
	
	for(i=0; i<24; i++)
	{
		if(0x800000 == (dat & 0x800000) )	
			TX1();
		else						
			TX0();
		dat<<=1;							//左移一位
	}
}

void RGB_Set(uint16_t R,uint16_t G,uint16_t B)
{
	unsigned long color;
	color=R*256 + G*256*256 + B;
	WS_Set1(color);
	
}


/**************************************************************************************
* 发送所有字节
**************************************************************************************/
void WS_SetAll()
{
	static uint8_t k;
	unsigned char j;
	unsigned long temp;
//	for(j=0; j<nWs; j++)
//	{
//		WS_Set1(WsDat[j]);  // j / 0
//	}
//	WS_Reset();

	{
		temp=WsDat[0];
		for(j=0;j<11;j++)
		{
			WsDat[j]=WsDat[j+1];
		}
		WsDat[11]=temp;
  }
	
}
/********************************************
* 求绝对值
********************************************/
unsigned char abs0(int num)
{
	if(num>0) return num;
	
	num = -num;
	return (unsigned char) num;
}

/***********************************************************************************
* 颜色渐变算法
* 误差 <= 2
************************************************************************************/
u32 ColorToColor(unsigned long color0, unsigned long color1)
{
	unsigned char Red0, Green0, Blue0;  // 起始三原色
	unsigned char Red1, Green1, Blue1;  // 结果三原色
	int			  RedMinus, GreenMinus, BlueMinus;	// 颜色差（color1 - color0）
	unsigned char NStep; 							// 需要几步
	float		  RedStep, GreenStep, BlueStep;		// 各色步进值
	unsigned long color;							// 结果色
	unsigned char i,j;
	static uint32_t WsDatTemp;
	// 绿 红 蓝 三原色分解
	Red0   = color0>>8;
	Green0 = color0>>16;
	Blue0  = color0;
	
	Red1   = color1>>8;
	Green1 = color1>>16;
	Blue1  = color1;
	
	// 计算需要多少步（取差值的最大值）
	RedMinus   = (Red1 - Red0); 
	GreenMinus = (Green1 - Green0); 
	BlueMinus  = (Blue1 - Blue0);
	
	NStep = ( abs0(RedMinus) > abs0(GreenMinus) ) ? abs0(RedMinus):abs0(GreenMinus);
	NStep = ( NStep > abs0(BlueMinus) ) ? NStep:abs0(BlueMinus);
	
	// 计算出各色步进值
	RedStep   = (float)RedMinus   / NStep;
	GreenStep = (float)GreenMinus / NStep;
	BlueStep  = (float)BlueMinus  / NStep;

	// 渐变开始
	for(i=0; i<NStep; i++)
	{
		Red1   = Red0   + (int)(RedStep   * i);
		Green1 = Green0 + (int)(GreenStep * i);
		Blue1  = Blue0  + (int)(BlueStep  * i);
		
		color  = Green1<<16 | Red1<<8 | Blue1; 	// 合成  绿红蓝
		WsDatTemp = color;
		for(j=0; j<nWs; j++)
	{
		WS_Set1(WsDatTemp);  // j / 0
	}
	  WS_Reset();
		delay_ms(10);						// 渐变速度
	}
	// 渐变结束
	
	return color;
}



void HAL_Delay(int time)
{
	delay_ms(time);
}
void  WS2812Send_8bit( uint8_t dat )
{
	uint16_t i;
		uint8_t mask = 0x80;
		uint8_t byte = dat;
		while (mask) 
		{
			if( byte & mask ) TX1(); else TX0();
			mask >>= 1;
        }

}
void WS2812BSend_24bit(uint8_t R, uint8_t G, uint8_t B)
{
	WS2812Send_8bit(G);
	WS2812Send_8bit(R);
	WS2812Send_8bit(B);
}

uint8_t rBuffer[PIXEL_MAX]={0};
uint8_t gBuffer[PIXEL_MAX]={0};
uint8_t bBuffer[PIXEL_MAX]={0};

void  setAllPixelColor(uint8_t r, uint8_t g, uint8_t b)
{ 
  uint8_t i=0;
  for(i=0;i<PIXEL_MAX;i++)
  {
    rBuffer[i]=0;
    gBuffer[i]=0;
    bBuffer[i]=0;
  }
  for(i=0;i<PIXEL_MAX;i++)
  {
    rBuffer[i]=r;
    gBuffer[i]=g;
    bBuffer[i]=b;
  }

  for(i=0;i<PIXEL_MAX;i++)
  {							  
    WS2812BSend_24bit(rBuffer[i],gBuffer[i],bBuffer[i]);
  }
}
void  setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{	 
  uint8_t i=0;

  for(i=0;i<PIXEL_MAX;i++)
  {
    rBuffer[i]=0;
    gBuffer[i]=0;
    bBuffer[i]=0;
  }
  rBuffer[n]=r;
  gBuffer[n]=g;
  bBuffer[n]=b;
  for(i=0;i<PIXEL_MAX;i++)
  {							  
    WS2812BSend_24bit(rBuffer[i],gBuffer[i],bBuffer[i]);
  }
}
void SetPixelColor(uint16_t n, uint32_t c)
{	 
  uint8_t i=0;
	  
  rBuffer[n]=(uint8_t)(c>>16);
  gBuffer[n]=(uint8_t)(c>>8);
  bBuffer[n]=(uint8_t)c;

  for(i=0;i<PIXEL_MAX;i++)
  {							  
    WS2812BSend_24bit(rBuffer[i],gBuffer[i],bBuffer[i]);
  }
}

uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
{
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
uint32_t Wheel(uint8_t WheelPos)
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) 
  {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
////2¨oo?
void rainbow(uint8_t wait)
{
  uint16_t i, j;
  
  for(j=0; j<256; j++) 
  {
    for(i=0; i<PIXEL_MAX; i++)
    {
      SetPixelColor(i, Wheel((i+j) & 255));
    }
    HAL_Delay (wait);
  }
}
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) 
{
  uint16_t i, j;
  
  for(j=0; j<256*5; j++) 
  { // 5 cycles of all colors on wheel
    for(i=0; i< PIXEL_MAX; i++) 
    {
      SetPixelColor(i, Wheel(((i * 256 / PIXEL_MAX) + j) & 255));
    }
    HAL_Delay (wait);
  }
}
//Theatre-style crawling lights.o??¨1|ì?
void theaterChase(uint32_t c, uint8_t wait) 
{
	int i,j,q;
  for (j=0; j<10; j++) 
  {  //do 10 cycles of chasing
    for (q=0; q < 3; q++) 
    {
      for ( i=0; i < PIXEL_MAX; i=i+1)//turn every one pixel on
      {
        SetPixelColor(i+q, c);    
      }
      HAL_Delay(wait);
      
      for ( i=0; i < PIXEL_MAX; i=i+1) //turn every one pixel off
      {
        SetPixelColor(i+q, 0);        
      }
    }
  }
}

////Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) 
{
	int i,j,q;
  for (j=0; j < 256; j++) 
  {     // cycle all 256 colors in the wheel
    for (q=0; q < 3; q++)
    {
      for ( i=0; i < PIXEL_MAX; i=i+1) //turn every one pixel on
      {
        SetPixelColor(i+q, Wheel( (i+j) % 255));    
      }
      
      HAL_Delay(wait);
      
      for ( i=0; i < PIXEL_MAX; i=i+1)//turn every one pixel off
      {
        SetPixelColor(i+q, 0);        
      }
    }
  }
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) 
{
  uint16_t i=0;
  for( i=0; i<PIXEL_MAX; i++) 
  {
    SetPixelColor(i, c);
    HAL_Delay(wait);
  }
}

void  WS2812B_Init(void)
{
	colorWipe(Color(0, 0, 255), 20); 
	setAllPixelColor(0, 0, 0);
}
void WS2812B_Test(void)
{
  colorWipe(Color(255, 0, 0), 5); // Red
  colorWipe(Color(0, 255, 0), 5); // Green
  colorWipe(Color(0, 0, 255), 5); // Blue
  //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // // Send a theater pixel chase in...
  // theaterChase(Color(127, 127, 127), 50); // White
  // theaterChase(Color(127, 0, 0), 50); // Red
  // theaterChase(Color(0, 0, 127), 50); // Blue

  // rainbow(20);
  // rainbowCycle(20);
  // theaterChaseRainbow(50);

    // setAllPixelColor(255, 0, 0);
  // HAL_Delay(100);
  // setAllPixelColor(0, 255, 0);
  // HAL_Delay(100);
  // setAllPixelColor(0, 0, 255);
  // HAL_Delay(100);
  // setAllPixelColor(0, 0, 0);
  // HAL_Delay(100);
  // setPixelColor(0, 0, 255, 0);
  // HAL_Delay(100);
  // setPixelColor(2, 0, 0, 255);
  // HAL_Delay(100);
  // setPixelColor(4, 255, 0, 0);
  // HAL_Delay(100);
  // setPixelColor(6, 125, 125, 125);  
  // HAL_Delay(100);
  // setPixelColor(5, 0, 255, 0);
  // HAL_Delay(100);
  // setPixelColor(3, 0, 0, 255);
  // HAL_Delay(100);
  // setPixelColor(1, 255, 0, 0);
  // HAL_Delay(100);
  // setAllPixelColor(0, 0, 0);
}


