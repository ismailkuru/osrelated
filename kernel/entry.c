#include "earlyio.h"
#include "types.h"
#include "param.h"

static void e820_print_type(u32 type)
{
	switch (type) {
		case E820_RAM:
			eio_puts("usable");
			break;
		case E820_RESERVED:
			eio_puts("reserved");
			break;
		case E820_ACPI:
			eio_puts("ACPI data");
			break;
		case E820_NVS:
			eio_puts("ACPI NVS");
			break;
		case E820_UNUSABLE:
			eio_puts("unusable");
			break;
		default:
			eio_printf("type %u", type);
			break;
	}
}

static void e820_print_map(struct e820_map const * map)
{
	u32 i;
	eio_puts("memory map:\n");
	for (i = 0; i < map->entries; ++i) {
		eio_printf("mem 0x%x-0x%x ",
		            (unsigned)(map->map[i].addr),
		            (unsigned)(map->map[i].addr + map->map[i].size - 1));
		e820_print_type(map->map[i].type);
		eio_putchar('\n');
	}
}

void entry_32()
{
	eio_init();
	eio_puts("Kernel is loaded\n");
	e820_print_map(&boot_params.e820_mem_info);
}
