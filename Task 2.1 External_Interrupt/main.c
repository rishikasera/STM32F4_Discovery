
#include "stm32f4xx.h"


GPIO_InitTypeDef GPIO_InitLed;
EXTI_InitTypeDef EXTI_InitSwitch;
NVIC_InitTypeDef NVIC_InitSwitch;

void Delay(__IO uint32_t nCount)
{
   while(nCount--){}
}


int main(void)
{

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

GPIO_InitLed.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;
GPIO_InitLed.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitLed.GPIO_OType = GPIO_OType_PP;
GPIO_InitLed.GPIO_PuPd =  GPIO_PuPd_NOPULL;
GPIO_InitLed.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOD,&GPIO_InitLed);

GPIO_InitLed.GPIO_Pin = GPIO_Pin_1 ;
GPIO_InitLed.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitLed.GPIO_OType = GPIO_OType_PP;
GPIO_InitLed.GPIO_PuPd =  GPIO_PuPd_DOWN;
GPIO_InitLed.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitLed);

SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);

EXTI_InitSwitch.EXTI_Line = EXTI_Line1;         //PA1
EXTI_InitSwitch.EXTI_Mode = EXTI_Mode_Interrupt;
EXTI_InitSwitch.EXTI_Trigger = EXTI_Trigger_Rising;
EXTI_InitSwitch.EXTI_LineCmd = ENABLE;

EXTI_Init(&EXTI_InitSwitch);

NVIC_InitSwitch.NVIC_IRQChannel = EXTI1_IRQn;
NVIC_InitSwitch.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitSwitch.NVIC_IRQChannelSubPriority = 0;
NVIC_InitSwitch.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitSwitch);


    while(1)
    {
          GPIO_WriteBit(GPIOD,GPIO_Pin_14,Bit_SET);
          GPIO_WriteBit(GPIOD,GPIO_Pin_15,Bit_RESET);
          Delay(1680000);
          GPIO_WriteBit(GPIOD,GPIO_Pin_14,Bit_RESET);
          GPIO_WriteBit(GPIOD,GPIO_Pin_15,Bit_SET);
          Delay(1680000);
          GPIO_WriteBit(GPIOD,GPIO_Pin_14,Bit_RESET);
          GPIO_WriteBit(GPIOD,GPIO_Pin_15,Bit_RESET);

    }
}

int i = 0;

void EXTI1_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
   {
      i=0;
      do{
             GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_SET);
             GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_RESET);
             Delay(1680000);
             GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_RESET);
             GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_SET);
             Delay(1680000);
             i++;
      }while(i<4);
      GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_RESET);
      GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_RESET);

      EXTI_ClearITPendingBit(EXTI_Line1);
   }
}
