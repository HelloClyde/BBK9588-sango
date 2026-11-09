ENTRY(bda_main)
SECTIONS {
 . = 0x81c00020; .entry : { *(.text.entry) }
 . = 0x81c00060; .text : { *(EXCLUDE_FILE (*sango_touch.o) .text*) }
 .rodata : { *(EXCLUDE_FILE (*sango_touch.o) .rodata*) }
 .data : { *(EXCLUDE_FILE (*sango_touch.o) .data* .sdata* .bss* COMMON) }
 ASSERT(. <= 0x81c1fef0, "Recovered C exceeds original text area")
 . = 0x81c1fef0; .sango_data : { KEEP(*(.sango_data)) }
 . = 0x81c2b0d0; .sango_bss (NOLOAD) : { . += 0x9a1; }
 /* New input code/state follows the original fixed save/global region. */
 . = 0x81c2bb00; .sango_touch : {
   __sango_touch_begin = .;
   *sango_touch.o(.text* .rodata* .data* .sdata* .bss* COMMON)
   __sango_touch_end = .;
 }
 ASSERT(. <= 0x81c30000, "Touch extension exceeds reserved application space")
 /DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.gnu.attributes) }
}
