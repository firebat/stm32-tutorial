extern int main(void);

extern unsigned long _etext;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;
extern unsigned long _estack;


typedef void (*pfnISR)(void);

void ResetISR(void);
void NMIException(void);
void HardFaultException(void);


__attribute__((section(".isr_vector")))
pfnISR VectorTable[] = 
{
  (pfnISR)((unsigned long)&_estack),
  ResetISR,
  NMIException,
  HardFaultException
};


void ResetISR(void)
{
  unsigned long *src, *dst;

  // Copy data segment from flash to SRAM
  src = &_etext;
  dst = &_sdata;
  while (dst < &_edata) {
    *dst++ = *src++;
  }

  // Zero fill bss segment
  dst = &_sbss;
  while (dst < &_ebss) {
    *(dst++) = 0;
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
