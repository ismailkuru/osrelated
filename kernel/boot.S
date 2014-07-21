#include "multiboot.h"
#include "boot.h"
#include "layout.h"

	.text
	.globl _start
_start:
	jmp	entry

#define MB_HEADER_FLAGS MBF_PAGE_ALIGN
	.align 4
	.long MB_HEADER_MAGIC
	.long MB_HEADER_FLAGS
	.long -(MB_HEADER_MAGIC | MB_HEADER_FLAGS)

#define BOOT_TIME_STACK_SIZE 0x4000
entry:
	movl	$(stack + BOOT_TIME_STACK_SIZE), %esp
	pushl	%ebx
	pushl	%eax
	call	setup

loop:
	hlt
	jmp	loop

	.comm stack, BOOT_TIME_STACK_SIZE
