#include <stm32f10x.h>

extern unsigned long _etext;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;
extern unsigned long _estack;

extern int main(void);

typedef void (*pfnISR)(void);

void Reset_Handler(void);
void Default_Handler (void) { while(1);}
void NMI_Handler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void HardFault_Handler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void MemMange_Handler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void BusFault_Handler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void UsageFault_Handler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void SVC_Handler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DebugMon_Handler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void PendSV_Handler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void SysTick_Handler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void WWDG_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void PVD_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TAMPER_STAMP_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void RTC_WKUP_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void FLASH_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void RCC_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void EXTI0_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void EXTI1_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void EXTI2_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void EXTI3_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void EXTI4_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA1_Channel1_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA1_Channel2_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA1_Channel3_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA1_Channel4_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA1_Channel5_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA1_Channel6_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA1_Channel7_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void ADC1_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void EXTI9_5_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM1_BRK_TIM15_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM1_UP_TIM16_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM1_TRG_COM_TIM17_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM1_CC_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM2_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM3_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM4_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void I2C1_EV_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void I2C1_ER_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void I2C2_EV_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void I2C2_ER_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void SPI1_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void SPI2_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void USART1_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void USART2_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void USART3_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void EXTI15_10_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void RTCAlarm_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void CEC_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM12_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM13_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM14_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void ADC3_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void FSMC_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM5_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void SPI3_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void UART4_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void UART5_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM6_DAC_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void TIM7_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA2_Channel1_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA2_Channel2_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA2_Channel3_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA2_Channel4_5_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));
void DMA2_Channel5_IRQHandler (void) __attribute__ ((weak,  alias ("Default_Handler")));


__attribute__ ((section(".isr_vector")))
pfnISR VectorTable[] = 
{
  (pfnISR)((unsigned long)&_estack),
  Reset_Handler,
  NMI_Handler,
  HardFault_Handler,
  MemMange_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0, 0, 0, 0,
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,
  WWDG_IRQHandler,
  PVD_IRQHandler,
  TAMPER_STAMP_IRQHandler,
  RTC_WKUP_IRQHandler,
  FLASH_IRQHandler,
  RCC_IRQHandler,
  EXTI0_IRQHandler,
  EXTI1_IRQHandler,
  EXTI2_IRQHandler,
  EXTI3_IRQHandler,
  EXTI4_IRQHandler,
  DMA1_Channel1_IRQHandler,
  DMA1_Channel2_IRQHandler,
  DMA1_Channel3_IRQHandler,
  DMA1_Channel4_IRQHandler,
  DMA1_Channel5_IRQHandler,
  DMA1_Channel6_IRQHandler,
  DMA1_Channel7_IRQHandler,
  ADC1_IRQHandler,
  0, 0, 0, 0,
  EXTI9_5_IRQHandler,
  TIM1_BRK_TIM15_IRQHandler,
  TIM1_UP_TIM16_IRQHandler,
  TIM1_TRG_COM_TIM17_IRQHandler,
  TIM1_CC_IRQHandler,
  TIM2_IRQHandler,
  TIM3_IRQHandler,
  TIM4_IRQHandler,
  I2C1_EV_IRQHandler,
  I2C1_ER_IRQHandler,
  I2C2_EV_IRQHandler,
  I2C2_ER_IRQHandler,
  SPI1_IRQHandler,
  SPI2_IRQHandler,
  USART1_IRQHandler,
  USART2_IRQHandler,
  USART3_IRQHandler,
  EXTI15_10_IRQHandler,
  RTCAlarm_IRQHandler,
  CEC_IRQHandler,
  TIM12_IRQHandler,
  TIM13_IRQHandler,
  TIM14_IRQHandler,
  0,
  ADC3_IRQHandler,
  FSMC_IRQHandler,
  0,
  TIM5_IRQHandler,
  SPI3_IRQHandler,
  UART4_IRQHandler,
  UART5_IRQHandler,
  TIM6_DAC_IRQHandler,
  TIM7_IRQHandler,
  DMA2_Channel1_IRQHandler,
  DMA2_Channel2_IRQHandler,
  DMA2_Channel3_IRQHandler,
  DMA2_Channel4_5_IRQHandler,
  DMA2_Channel5_IRQHandler,
  0, 0, 0, 0, 0, 0, 0, 0,
  0,
#if defined (STM32F10X_LD_VL) || (defined STM32F10X_MD_VL) 
  [0x1CC/4] = 0xF108F85F
#elif defined (STM32F10X_HD_VL)
  [0x1E0/4] = 0xF108F85F
#endif
};


void __attribute__ ((weak)) __libc_init_array (void){}

void __Init_Data(void)
{
  unsigned long *src, *dst;

  // .data
  src = &_etext;
  dst = &_sdata;
  while (dst < &_edata) {
    *(dst++) = *(src++);
  }

  // .bss
  dst = &_sbss;
  while (dst < &_ebss) {
    *(dst++) = 0;
  }
}

void Reset_Handler(void)
{
  __Init_Data();

  SystemInit();

  __libc_init_array();

  main();
}

