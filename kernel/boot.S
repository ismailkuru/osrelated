#include "multiboot.h"
#include "layout.h"
#include "mmu.h"
#include "param.h"

	.section ".header", "a"
#define MB_HEADER_FLAGS (MBF_PAGE_ALIGN | MBF_MEMORY_INFO)
	.align 4
	.long MB_HEADER_MAGIC
	.long MB_HEADER_FLAGS
	.long -(MB_HEADER_MAGIC + MB_HEADER_FLAGS)

	.section ".bootstrap", "ax"
	.globl _start, enter_pm
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
	pushl	$0
	popf
	pushl	%ebx
	pushl	%edx

	call	setup
	jmp	loop

enter_pm:
	movl	%cr0, %eax
	orl	$CR0_PE, %eax
	movl	%eax, %cr0

	movl	$(V2P(pgdir)), %eax
	movl	%eax, %cr3

	movl	%cr0, %eax
	orl	$(CR0_PG | CR0_WP), %eax
	movl	%eax, %cr0

	call	entry_32
loop:
	jmp	loop

	.bss
#define BOOT_TIME_STACK_SIZE 0x4000
	.space BOOT_TIME_STACK_SIZE
stack_end:
