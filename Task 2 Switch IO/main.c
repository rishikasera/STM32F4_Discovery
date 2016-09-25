
#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitLed;

int press = 0;

void Delay(__IO uint32_t nCount)
{
	while(nCount--){

	}
}

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitLed.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitLed.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitLed.GPIO_OType = GPIO_OType_PP;
	GPIO_InitLed.GPIO_PuPd =  GPIO_PuPd_NOPULL;
	GPIO_InitLed.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOD, &GPIO_InitLed);

	GPIO_InitLed.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitLed.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitLed.GPIO_OType = GPIO_OType_PP;
	GPIO_InitLed.GPIO_PuPd =  GPIO_PuPd_DOWN;
	GPIO_InitLed.GPIO_Speed = GPIO_Speed_50MHz;


	GPIO_Init(GPIOA,&GPIO_InitLed);

	while(1)
	{
	     if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_SET)
	     {
	          if(press == 0)
	          {
	                press = 1;
	          }
	          else
	          {
	        	  	press = 0;

	          }
	          Delay(3000000);
	     }
	          if(press == 0)
	          {
	                GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_SET);
	                GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_SET);
	                GPIO_WriteBit(GPIOD,GPIO_Pin_14,Bit_RESET);
	                GPIO_WriteBit(GPIOD,GPIO_Pin_15,Bit_RESET);
	          }
	          else
	          {
	                GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_RESET);
	                GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_RESET);
	                GPIO_WriteBit(GPIOD,GPIO_Pin_14,Bit_SET);
	                GPIO_WriteBit(GPIOD,GPIO_Pin_15,Bit_SET);
	          }
		}
}
