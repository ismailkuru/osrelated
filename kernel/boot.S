#include "multiboot.h"
#include "layout.h"
#include "mmu.h"
#include "param.h"

	.section ".bootstrap", "ax"
	.globl _start


#define MB_HEADER_FLAGS MBF_PAGE_ALIGN
	.align 4
	.long MB_HEADER_MAGIC
	.long MB_HEADER_FLAGS
	.long -(MB_HEADER_MAGIC | MB_HEADER_FLAGS)


	.align 4
boot_gdt:
	.quad 0x0000000000000000
#define BOOT_CS 0x0008
	.quad 0x00cf9a000000ffff
#define BOOT_DS 0x0010
	.quad 0x00cf92000000ffff
boot_gdt_descr:
	.word (boot_gdt_descr - boot_gdt - 1)
	.long boot_gdt


_start:
	movl	%eax, %edx
	cld
	xorl	%eax, %eax
	movl	$(V2P(__bss_first)), %edi
	movl	$(V2P(__bss_last)), %ecx
	subl	%edi, %ecx
	shrl	$2, %ecx
	rep
	stosl

	lgdt	boot_gdt_descr
	movw	$(BOOT_DS), %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %ss
	movw	%ax, %gs
	movw	%ax, %fs

	ljmp	$(BOOT_CS), $reload_cs


reload_cs:
	movl	$(V2P(stack_end)), %esp
	pushl	%ebx
	pushl	%edx

	movl	%cr0, %eax
	orl	$0x00000001, %eax
	movl	%eax, %cr0

	movl	$(V2P(boot_page_dir)), %eax
	movl	$0x00000083, (%eax)
	movl	$0x00400083, 4(%eax)
	movl	$0x00000083, (VIRTUAL_ADDRESS_BASE >> 20)(%eax)
	movl	$0x00400083, (VIRTUAL_ADDRESS_BASE >> 20 + 4)(%eax)

	/* enable page size extension */
	movl	%cr4, %eax
	orl	$0x00000010, %eax
	movl	%eax, %cr4

	/* load page dir address */
	movl	$(V2P(boot_page_dir)), %eax
	movl	%eax, %cr3

	/* turn on paging */
	movl	%cr0, %eax
	orl	$0x80010000, %eax
	movl	%eax, %cr0

	call	setup
loop:
	jmp	loop

	.bss

	.align 4096

boot_page_dir:
	.space (PD_SIZE * PD_ENTRY_SIZE)

#define BOOT_TIME_STACK_SIZE 0x4000
	.space BOOT_TIME_STACK_SIZE
stack_end:

	.align 4096
