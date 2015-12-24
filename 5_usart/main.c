#include <stm32f10x.h>

void RCC_Configuration(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}


void GPIO_Configuration(void)
{
  GPIO_InitTypeDef gpio_init;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

  gpio_init.GPIO_Pin = GPIO_Pin_9;
  gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &gpio_init);

  gpio_init.GPIO_Pin = GPIO_Pin_10;
  gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &gpio_init);
}


void USART_Configuration(void)
{
  USART_InitTypeDef usart_init;
  usart_init.USART_BaudRate = 9600;
  //  usart_init.USART_WordLength = USART_WordLength_8b;
  //  usart_init.USART_StopBits = USART_StopBits_1;
  //  usart_init.USART_Parity = USART_Parity_No;
  //  usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &usart_init);

  USART_Cmd(USART1, ENABLE);
}

void USART_Write(USART_TypeDef *usart, char *s)
{
  while(*s) {
    USART_SendData(usart, *s++);
    while(USART_GetFlagStatus(usart, USART_FLAG_TC) == RESET);
  }
}

int main(void)
{
  RCC_Configuration();
  GPIO_Configuration();
  USART_Configuration();

  while(1) {
    USART_Write(USART1, "Welcome!\r\n");
  }
}

