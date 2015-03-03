MEMORY
{
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
}

SECTIONS
{
  /* program code into FLASH */
  .text :
  {
    *(.isr_vector)    /* Vector table */
    *(.text)          /* Program code */
  } > FLASH

  /* uninitialized global and static variables into SRAM */
  .data :
  {
    *(.data)
  } > SRAM
}
