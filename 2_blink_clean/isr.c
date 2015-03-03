#define STACK_TOP 0x20001000

extern int main(void);

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
  // TODO

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
