
#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_Led;
void Delay(__IO uint32_t nCount)
{
    while(nCount--){}
}

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	    GPIO_Led.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	    GPIO_Led.GPIO_Mode = GPIO_Mode_OUT;
	    GPIO_Led.GPIO_OType = GPIO_OType_PP;
	    GPIO_Led.GPIO_Speed = GPIO_Speed_50MHz;

	    GPIO_Init(GPIOD,&GPIO_Led);

        int k =0;
	    while(1)
	    {
	           GPIO_WriteBit(GPIOD, GPIO_Pin_0,Bit_SET);
	           Delay(16800000);
	           GPIO_WriteBit(GPIOD, GPIO_Pin_0,Bit_RESET);
	           GPIO_WriteBit(GPIOD, GPIO_Pin_1,Bit_SET);
	           Delay(16800000);
	           GPIO_WriteBit(GPIOD, GPIO_Pin_1,Bit_RESET);
	           GPIO_WriteBit(GPIOD, GPIO_Pin_2,Bit_SET);
	           Delay(16800000);
	           GPIO_WriteBit(GPIOD, GPIO_Pin_2,Bit_RESET);
               k++;
	    }
}
