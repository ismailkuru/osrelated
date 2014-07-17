ENTRY(_start)

EXT_MEM_SIZE = 0x00100000; /* must be equal to layout.h::EXT_MEM_SIZE */
KERNEL_BASE  = 0xC0000000; /* must be equal to layout.h::KERNEL_BASE */

SECTIONS
{
	. = EXT_MEM_SIZE;
	.text :
	{
		*(.text)
	}

	.rodata :
	{
		*(.rodata)
	}

	.data :
	{
		*(.data)
	}

	.bss :
	{
		*(.bss)
	}

	.debug_aranges :
	{
		*(.debug_aranges)
	}

	.debug_info :
	{
		*(.debug_info)
	}

	.debug_abbrev :
	{
		*(.debug_abbrev)
	}

	.debug_line :
	{
		*(.debug_line)
	}

	.debug_str :
	{
		*(.debug_str)
	}

	/DISCARD/ :
	{
		*(.eh_frame .note.* .comment)
	}
}
