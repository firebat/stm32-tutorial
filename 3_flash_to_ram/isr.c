#define STACK_TOP 0x20001000

extern int main(void);

extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;


void ResetISR(void);
void NMIException(void);
void HardFaultException(void);


typedef void (*pfnISR)(void);

__attribute__((section(".isr_vector")))
pfnISR VectorTable[] = 
{
  (pfnISR) STACK_TOP,
  ResetISR,
  NMIException,
  HardFaultException
};


void ResetISR(void)
{
  unsigned long *src, *dst;

  // Copy data segment from flash to SRAM
  src = &_etext;
  dst = &_data;

  while (dst < &_edata) {
    *dst++ = *src++;
  }

  // Zero fill bss segment
  for (dst = &_bss; dst < &_ebss; dst++) {
    *dst = 0;
  }


  // Call entry point.
  main();
}

void NMIException(void)
{
  return;
}

void HardFaultException(void)
{
  return;
}
