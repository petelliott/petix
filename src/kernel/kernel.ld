/* linker script for two stage pdp 11 bootloader */
OUTPUT_FORMAT("a.out-pdp11")
OUTPUT_ARCH(pdp11)
SEARCH_DIR("/usr/local/pdp11-aout/lib");
PROVIDE (__stack = 0);

ENTRY(__start);
SECTIONS
{
  . = 0 + SIZEOF_HEADERS;
  .text :
  {
    CREATE_OBJECT_SYMBOLS
    *(.text)
    _etext = .;
    __etext = .;
  }
  . = ALIGN(256);
  .data :
  {
    *(.data)
    CONSTRUCTORS
    _edata  =  .;
    __edata  =  .;
  }
  .bss :
  {
    __bss_start = .;
   *(.bss)
   *(COMMON)
   . = ALIGN(4);
   _end = . ;
   __end = . ;
  }
}

