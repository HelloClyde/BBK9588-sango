ENTRY(bda_main)
SECTIONS {
 . = 0x81c00020; .entry : { *(.text.entry) }
 . = 0x81c00060; .text : {
   *(EXCLUDE_FILE (*sango_touch.o *sango_battle_info.o *sango_music.o *sango_music_sdk.o *sango_intro.o *sango_ruler.o) .text*)
   /* Keep the optional music diagnostics within the extension's size limit. */
   *sango_intro.o(.text.sango_intro_sdk_copy .text.sango_intro_compose)
 }
 .rodata : { *(EXCLUDE_FILE (*sango_touch.o *sango_battle_info.o *sango_music.o *sango_music_sdk.o *sango_intro.o *sango_ruler.o) .rodata*) }
 .data : {
   *(EXCLUDE_FILE (*sango_touch.o *sango_battle_info.o *sango_music.o *sango_music_sdk.o *sango_ui_paint.o *sango_intro.o *sango_ruler.o) .data*)
   *(EXCLUDE_FILE (*sango_touch.o *sango_battle_info.o *sango_music.o *sango_music_sdk.o *sango_ui_paint.o *sango_intro.o *sango_ruler.o) .sdata*)
   *(EXCLUDE_FILE (*sango_touch.o *sango_battle_info.o *sango_music.o *sango_music_sdk.o *sango_ui_paint.o *sango_intro.o *sango_ruler.o) .bss*)
   *(EXCLUDE_FILE (*sango_touch.o *sango_battle_info.o *sango_music.o *sango_music_sdk.o *sango_ui_paint.o *sango_intro.o *sango_ruler.o) COMMON)
 }
 ASSERT(. <= 0x81c1fef0, "Recovered C exceeds original text area")
 . = 0x81c1fef0; .sango_data : { KEEP(*(.sango_data)) }
 . = 0x81c2b0d0; .sango_bss (NOLOAD) : { . += 0x9a1; }
 /* New input/modal code and state follow the original fixed save/global region. */
 . = 0x81c2bb00; .sango_touch : {
   __sango_touch_begin = .;
   *sango_touch.o(.text* .rodata* .data* .sdata* .bss* COMMON)
   *sango_battle_info.o(.text* .rodata* .data* .sdata* .bss* COMMON)
   *sango_music.o(.text* .rodata* .data* .sdata* .bss* COMMON)
   *sango_music_sdk.o(.text* .rodata* .data* .sdata* .bss* COMMON)
   *sango_ui_paint.o(.data* .sdata* .bss* COMMON)
   *sango_intro.o(.text* .rodata* .data* .sdata* .bss* COMMON)
   *sango_ruler.o(.text* .rodata* .data* .sdata* .bss* COMMON)
   __sango_touch_end = .;
 }
 ASSERT(. <= 0x81c34000, "UI extension exceeds reserved application space")
 /DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.gnu.attributes) }
}
