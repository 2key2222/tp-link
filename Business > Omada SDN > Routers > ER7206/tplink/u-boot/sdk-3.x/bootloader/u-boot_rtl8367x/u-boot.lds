OUTPUT_FORMAT("elf32-ntradbigmips", "elf32-ntradbigmips", "elf32-ntradbigmips")
OUTPUT_ARCH(mips)
ENTRY(_start)
SECTIONS
{
 PROVIDE (__executable_start = SEGMENT_START("text-segment", 0xC0000000));
 . = SEGMENT_START("text-segment", 0xC0000000) + SIZEOF_HEADERS;
 . = ALIGN(4);
 .text :
 {
  *(.text) *(.text.*)
  *(.data_in_text.*)
 }
 uboot_start = _start;
 _gp = ALIGN(16);
 . = ALIGN(16);
 __got_start = .;
 .got : { *(.got) }
 __got_end = .;
 . = ALIGN(8);
 .rodata : { *(.rodata) *(.rodata.str*) *(.rodata.*) }
 . = ALIGN(8);
 .data : { *(.data) *(.data.*) }
 . = ALIGN(8);
 .sdata : { *(.sdata) *(.sdata.*) }
 . = ALIGN(8);
 .u_boot_list : {
  KEEP(*(SORT(.u_boot_list*)));
 }
 . = ALIGN(8);
 uboot_end_data = .;
 num_got_entries = (__got_end - __got_start) >> 2;
 . = ALIGN(8);
 .sbss : { *(.sbss) *(.sbss.*) }
 .bss : { *(.bss) *(.bss.*) }
 .scommon : { *(.scommon) *(.scommon.*) }
 .cvmx_shared_bss : { *(.cvmx_shared_bss) *(.cvmx_shared_bss.*) }
 . = ALIGN(8);
 uboot_end = .;
 .debug 0 : { *(.debug) }
 .line 0 : { *(.line) }
 .debug_srcinfo 0 : { *(.debug_srcinfo) }
 .debug_sfnames 0 : { *(.debug_sfnames) }
 .debug_aranges 0 : { *(.debug_aranges) }
 .debug_pubnames 0 : { *(.debug_pubnames) }
 .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
 .debug_abbrev 0 : { *(.debug_abbrev) }
 .debug_line 0 : { *(.debug_line) }
 .debug_frame 0 : { *(.debug_frame) }
 .debug_str 0 : { *(.debug_str) }
 .debug_loc 0 : { *(.debug_loc) }
 .debug_macinfo 0 : { *(.debug_macinfo) }
 .debug_weaknames 0 : { *(.debug_weaknames) }
 .debug_funcnames 0 : { *(.debug_funcnames) }
 .debug_typenames 0 : { *(.debug_typenames) }
 .debug_varnames 0 : { *(.debug_varnames) }
 .gptab.sdata : { *(.gptab.data) *(.gptab.sdata) }
 .gptab.sbss : { *(.gptab.bss) *(.gptab.sbss) }
 /DISCARD/ : { *(.note.GNU-stack) }
}
