/*
  The Definitive Guide To ARM Cortex M3
  -------------------------------------
  2.5 THE MEMORY MAP

  +---------------+ 0xFFFFFFFF
  |               |
  |  System level |
  |               |
  +---------------+ 0xE0000000
  |               |
  |External device|
  |               |
  +---------------+ 0xA0000000
  |               |
  | External RAM  |
  |               |
  +---------------+ 0x60000000
  | Peripherlals  |
  +---------------+ 0x40000000
  |      SRAM     |
  +---------------+ 0x20000000
  |      CODE     |
  +---------------+ 0x00000000


  -------------------------------------
  3.7 RESET SEQUENCE

  After the processor exits reset, it will read two words from memory:
  • Address 0x00000000: Starting value of R13 (the SP)
  • Address 0x00000004: Reset vector (the starting address of program execution)

               Fetch initial   Fetch reset +----+ Instruction
                 SP value        vector    |    V    fetch
  +-------+   +--------------+--------------+  +--------------+---+---+
  | Reset |---|  0x00000000  |  0x00000004  |--| reset vector |xxx|xxx|
  +-------+   +--------------+--------------+  +--------------+---+---+

 
             +------------------+
             |                  |
             |   Other momory   |
             |                  |
  0x20008000 +------------------+--+  <-- Initial SP <-+
             | 1st stacked item |  |      0x20008000   |
             +------------------+  |                   |
             | 2nd stacked item |   > Stack memory     |
             +------------------+  |                   |
             |        ...       |  |                   |
             +------------------+--+                   |
             |                  |                      |
             |   Other memory   |                      |
             |                  |                      |
             +------------------+                      |
             |xxxxxxxxxxxxxxxxxx|                      |
             |xxxxxxxxxxxxxxxxxx|                      |
             +------------------+                      |
             |                  |                      |
             |      Flash       |                      |
             |+----------------+|                      |
             ||   Boot code    || <--+                 |
  0x00000100 +------------------+    |                 |
             | Other exception  |    | Reset           |
             |     vectors      |    | vector          |
             +------------------+    |                 |
             |    0x00000101    | ---+                 |
  0x00000004 +------------------+                      |
             |    0x20008000    | ---------------------+
  0x00000000 +------------------+

  Because the stack operation in the Cortex-M3 is a full descending stack (SP decrement before
  store), the initial SP value should be set to the first memory after the top of the stack region. For
  example, if you have a stack memory range from 0x20007C00 to 0x20007FFF (1 KB), the initial stack
  value should be set to 0x20008000
 */

// STM32F103C8T6 only has a 20k SRAM, so MSP must be less than 0x20005000.
// For example, stack size = 0x20001000-0x20000000 = 0x1000 = 4K, that's enough.
__asm__(".word 0x20001000");
__asm__(".word main");


/*
  STM32F10x Reference manual (RM0008)
  -----------------------------------
  3.3 Memory map

            Table 3. Register boundary addresses
  +---------------------------+-------------------------+
  |     Boundary address      |         Peripheral      |
  +---------------------------+-------------------------+
  |           .....           |              .....      |
  +---------------------------+-------------------------+
  | 0x4002 1000 - 0x4002 13FF | Reset and clock control |
  +---------------------------+-------------------------+
  |           .....           |            .....        |
  +---------------------------+-------------------------+
  | 0x4001 1000 - 0x4001 13FF | GPIO Port C             |
  +---------------------------+-------------------------+
  |           .....           |            .....        |
  +---------------------------+-------------------------+
 */
#define GPIOC_CRH    (*((volatile unsigned long*)(0x40011000 + 0x4)))
#define GPIOC_BSRR   (*((volatile unsigned long*)(0x40011000 + 0x10)))
#define RCC_APB2ENR  (*((volatile unsigned long*)(0x40021000 + 0x18)))

int main(void)
{

  unsigned int i = 0;

  // -------------------------------------
  // Enable GPIO_C
  /*
    GPIO(General Purpose I/O) must be ENABLED before use, else it will be disabled for
    a lower power cost, which is controlled by RCC_APB2ENR(APB2 peripheral clock enable register).


    STM32F10x Reference manual (RM0008)
    -----------------------------------
    7.3.7 APB2 peripheral clock enable register (RCC_APB2ENR)
          Address: 0x18
          Reset value: 0x0000 0000

      31    30    29    28    27    26    25    24    23    22    21    20    19    18    17    16
    +-----------------------------------------------------------+-----+-----+-----+-----------------+
    |                                                           |TIM11|TIM10| TIM9|                 |
    |                           Reserved                        | EN  | EN  |  EN |     Reserved    |
    |                                                           |-----+-----+-----|                 |
    |                                                           | rw  | rw  | rw  |                 |
    +-----------------------------------------------------------+-----+-----+-----+-----+-----+-----+
      15    14    13    12    11    10     9     8     7     6     5     4     3     2     1     0
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    | ADC3|USART| TIM8| SPI1| TIM1| ADC2| ADC1| IOPG| IOPF| IOPE| IOPD| IOPC| IOPB| IOPA|     | AFIO|
    |  EN |  EN |  EN |  EN |  EN |  EN |  EN |  EN |  EN |  EN |  EN |  EN |  EN |  EN | Res.|  EN |
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|     |-----+
    |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |     |  rw |
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+ 
  */

  // - IOPCEN = 1
  RCC_APB2ENR = (1 << 4);

  // -------------------------------------
  // Configure PC_13
  /*
    Each of the general-purpose I/O ports has two 32-bit configuration registers (GPIOx_CRL,
    GPIOx_CRH), two 32-bit data registers (GPIOx_IDR, GPIOx_ODR), a 32-bit set/reset
    register (GPIOx_BSRR), a 16-bit reset register (GPIOx_BRR) and a 32-bit locking register
    (GPIOx_LCKR).

    STM32F10x Reference manual (RM0008)
    -----------------------------------
    9.2.2 Port configuration register high (GPIOx_CRH) (x=A..G)
          Address offset: 0x04
          Reset value: 0x4444 4444

      31    30    29    28    27    26    25    24    23    22    21    20    19    18    17    16
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    | CNF15[1:0]|MODE15[1:0]| CNF14[1:0]|MODE14[1:0]| CNF13[1:0]|MODE13[1:0]| CNF12[1:0]|MODE12[1:0]|
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+ 
      15    14    13    12    11    10     9     8     7     6     5     4     3     2     1     0
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    | CNF11[1:0]|MODE11[1:0]| CNF10[1:0]|MODE10[1:0]| CNF9[1:0] | MODE9[1:0]| CNF8[1:0] | MODE8[1:0]|
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |  rw |
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+ 
   */

  // - CNF13[1:0] = 00 (General purpose output push-pull)
  // - MODE[1:0]  = 01
  GPIOC_CRH = 0x44144444;

  // Light on/off
  /*
    STM32F10x Reference manual (RM0008)
    -----------------------------------
    9.2.5 Port bit set/reset register (GPIOx_BSRR) (x=A..G)
          Address offset: 0x10
          Reset value: 0x0000 0000

      31    30    29    28    27    26    25    24    23    22    21    20    19    18    17    16
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    | BR15| BR14| BR13| BR12| BR11| BR10| BR9 | BR8 | BR7 | BR6 | BR5 | BR4 | BR3 | BR2 | BR1 | BR0 |
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+ 
      15    14    13    12    11    10     9     8     7     6     5     4     3     2     1     0
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    | BS15| BS14| BS13| BS12| BS11| BS10| BS9 | BS8 | BS7 | BS6 | BS5 | BS4 | BS3 | BS2 | BS1 | BS0 |
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |  w  |
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+ 
   */


  // - ON : BR13 = 1
  // - OFF: BS13 = 1
  while(1) {
    GPIOC_BSRR = (1 << 29);
    for(i=0; i<500000; i++);
    GPIOC_BSRR = (1 << 13);
    for(i=0; i<500000; i++);
  }

  return 0;
}
