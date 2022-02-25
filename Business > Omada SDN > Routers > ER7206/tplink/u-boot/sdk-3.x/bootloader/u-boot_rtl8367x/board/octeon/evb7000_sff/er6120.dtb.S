.section .rodata, "a"
.balign 8
.global __dtb_begin
__dtb_begin:
.incbin "er6120.dtb" 
__dtb_end:
.global __dtb_end
.balign 8
