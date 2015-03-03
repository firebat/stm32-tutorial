MEMORY
{
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
}

__stack_size = 1024;
_estack = ORIGIN(SRAM) + LENGTH(SRAM);
_sstack = _estack - __stack_size;

SECTIONS
{
  /* Text section (code and read-only data) */
  .text :
  {
    /* Reset and ISR vectors */
    KEEP(*(.isr_vector))

    . = ALIGN(4);
    *(.text)    /* code */
    *(.rodata)  /* read only data */
    . = ALIGN(4);
    _etext = .;
  } > FLASH


  /* Initialized data section. This section is programmed into FLASH (LMA address)
     and copied to RAM (VMA address) in startup code. */
  .data :   
  {
    . = ALIGN(4);
    _sdata = .;         /* data section VMA address */
    *(.data)
    . = ALIGN(4);
    _edata = .;
  } > SRAM AT> FLASH    /* LMA address (in FLASH) */


  /* Uninitialized data section (zeroed out by startup code) */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    . = ALIGN(4);
    _ebss = .;
  } > SRAM

  . = _sstack;
  .stack :
  {
    . = . + __stack_size;
  } > SRAM
}
