#include <stm32f10x.h>

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef gpio;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  gpio.GPIO_Pin = GPIO_Pin_13;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOC, &gpio);
}


void delay(uint32_t count)
{
  for(; count != 0; count--);
}

int main(void)
{
  GPIO_Configuration();

  while (1) {
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
    delay(500000);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    delay(500000);
  }
}
