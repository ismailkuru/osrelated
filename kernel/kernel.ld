OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)

/* must be equal to layout.h definitions */
LINEAR_ADDRESS_BASE  = 0x00100000;
VIRTUAL_ADDRESS_BASE = 0xC0000000;
KERNEL_LINK_ADDRESS  = LINEAR_ADDRESS_BASE + VIRTUAL_ADDRESS_BASE;

SECTIONS
{
	. = LINEAR_ADDRESS_BASE;

	__kernel_start = .;
	.header : {
		*(.header)
	}

	.bootstrap : {
		*(.bootstrap)
	}

	. += VIRTUAL_ADDRESS_BASE;

	.text : AT(ADDR(.text) - VIRTUAL_ADDRESS_BASE) {
		*(.text)
		*(.text.*)
	}

	.rodata : {
		*(.rodata)
		*(.rodata.*)
	}

	.data : {
		*(.data)
		*(.data.*)
	}

	__bss_first = .;
	.bss : {
		*(.bss)
	}
	__bss_last = .;
	__kernel_end = (. - VIRTUAL_ADDRESS_BASE);

	.debug_aranges 0 : {
		*(.debug_aranges)
	}

	.debug_info 0 : {
		*(.debug_info)
	}

	.debug_abbrev 0 : {
		*(.debug_abbrev)
	}

	.debug_line 0 : {
		*(.debug_line)
	}

	.debug_str 0 : {
		*(.debug_str)
	}

	/DISCARD/ : {
		*(.eh_frame .note.* .comment)
	}
}
