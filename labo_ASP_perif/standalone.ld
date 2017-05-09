
GROUP(-lgcc -lc -lcs3 -lcs3unhosted -lcs3arm)

MEMORY
{
  ram (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS
{
  .text :
  {
  *(.text .text.* .gnu.linkonce.t.*)
  }>ram

  .bss :
{
  _bss = .;
  *(.bss*)
  *(COMMON)
  _ebss = .;
  . = ALIGN (8);
  _end = .;
} > ram
}
