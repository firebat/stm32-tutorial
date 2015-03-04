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
  .text :
  {
     FILL (0xff)
 
     _isr_vectors_offs = . - 0x08000000;
    KEEP(*(.isr_vector))
 
    . = ALIGN(4);
    *(.text)
    *(.text.*)
    *(.rodata)
    *(.fini)
    *(.rodata*)
    *(.glue_7)
    *(.glue_7t)
    . = ALIGN(4);
    _etext = .;

  } > FLASH

  .data :
  {
    FILL (0xff)

    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    _edata = .;
  } > SRAM AT> FLASH
 
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
     _ebss = .;
  } > SRAM

  . = _sstack;
  .stack :
  {
    . = . + __stack_size;
  } > SRAM
}
