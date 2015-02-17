#define GPIOC_CRH    (*((volatile unsigned long*)(0x40011000 + 0x4)))
#define GPIOC_BSRR   (*((volatile unsigned long*)(0x40011000 + 0x10)))
#define RCC_APB2ENR  (*((volatile unsigned long*)(0x40021000 + 0x18)))

int main(void)
{
  unsigned int i = 0;

  RCC_APB2ENR = (1 << 4);

  GPIOC_CRH = 0x44144444;

  while(1) {
    GPIOC_BSRR = (1 << 29);
    for(i=0; i<500000; i++);
    GPIOC_BSRR = (1 << 13);
    for(i=0; i<500000; i++);
  }

  return 0;
}
