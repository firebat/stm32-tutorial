#include <stm32f10x.h>

void USART1_Init(void)
{

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1
                         | RCC_APB2Periph_AFIO
                         | RCC_APB2Periph_GPIOA, ENABLE);


  GPIO_InitTypeDef gpio_init;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
  // TX
  gpio_init.GPIO_Pin = GPIO_Pin_9;
  gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &gpio_init);

  // RX
  gpio_init.GPIO_Pin = GPIO_Pin_10;
  gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &gpio_init);


  USART_InitTypeDef usart_init;
  usart_init.USART_BaudRate = 115200;
  usart_init.USART_WordLength = USART_WordLength_8b;
  usart_init.USART_StopBits = USART_StopBits_1;
  usart_init.USART_Parity = USART_Parity_No;
  usart_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &usart_init);
  USART_Cmd(USART1, ENABLE);
}


void usart_putc(char c)
{
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
  USART1->DR = (c & 0xff);
}

void usart_send(const char* s)
{
  while(*s)
    usart_putc(*s++);
}

int main(void)
{
  USART1_Init();

  usart_send("Hello World!\r\n");

  while(1) {}
}
