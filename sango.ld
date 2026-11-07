ENTRY(bda_main)
SECTIONS {
 . = 0x81c00020; .entry : { *(.text.entry) }
 . = 0x81c00060; .text : { *(.text*) }
 .rodata : { *(.rodata*) }
 .data : { *(.data*) *(.sdata*) *(.bss*) *(COMMON) }
 ASSERT(. <= 0x81c1fef0, "Recovered C exceeds original text area")
 . = 0x81c1fef0; .sango_data : { KEEP(*(.sango_data)) }
 . = 0x81c2b0d0; .sango_bss (NOLOAD) : { . += 0x9a1; }
 /DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.gnu.attributes) }
}
