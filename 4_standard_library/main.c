#include <stm32f10x.h>

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef gpioc_init = {GPIO_Pin_13, GPIO_Speed_50MHz, GPIO_Mode_Out_PP};

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_Init(GPIOC, &gpioc_init);
}


void delay(uint32_t count)
{
  for(; count != 0; count--);
}

int main(void)
{
  GPIO_Configuration();

  while (1) {
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
    delay(500000);
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
    delay(500000);
  }
}
