MEMORY
{
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
}

SECTIONS
{

  /* Reset and ISR vectors */
  .isr_vector :
  {
    _isr_vector = .;
    KEEP(*(.isr_vector))
    ASSERT(. != _isr_vector, "The .isr_vector section is empty");
  } > FLASH


  /* Text section (code and read-only data) */
  .text :
  {
    _text = .;
    *(.text)    /* code */
    *(.rodata)  /* read only data */
    . = ALIGN(4);
    _etext = .;
  } > FLASH


  /* Initialized data section. This section is programmed into FLASH (LMA address)
     and copied to RAM (VMA address) in startup code. */
  .data : AT (_etext)   /* LMA address (in FLASH) */
  {
    _data = .;          /* data section VMA address */
    *(.data)
    . = ALIGN(4);
    _edata = .;
  } > SRAM


  /* Uninitialized data section (zeroed out by startup code) */
  .bss (NOLOAD) :
  {
    _bss = .;
    *(.bss)
    . = ALIGN(4);
    _ebss = .;
  } > SRAM

  _end = .;
}


/* Nice to have */
__isr_vector_size = SIZEOF(.isr_vector);
__text_size = SIZEOF(.text);
__data_size = SIZEOF(.data);
__bss_size = SIZEOF(.bss);
