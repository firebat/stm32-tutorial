#include <stm32f10x.h>

void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);


void putc(char c)
{
  USART_SendData(USART1, c);
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void puts(char* s)
{
  while(*s) {
    putc(*s++);
  }
}

int main(void)
{
  RCC_Configuration();
  GPIO_Configuration();
  USART_Configuration();

  while(1) {
    puts("Hello world!\r\n");
  }
}


void RCC_Configuration(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1
                         | RCC_APB2Periph_GPIOA
                         | RCC_APB2Periph_AFIO, ENABLE);
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
  usart_init.USART_BaudRate = 115200;
  //  usart_init.USART_WordLength = USART_WordLength_8b;
  //  usart_init.USART_StopBits = USART_StopBits_1;
  //  usart_init.USART_Parity = USART_Parity_No;
  //  usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &usart_init);

  USART_Cmd(USART1, ENABLE);
}
