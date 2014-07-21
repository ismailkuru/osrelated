#include "multiboot.h"
#include "earlyio.h"
#include "types.h"

void setup(u32 magic, u32 addr)
{
	struct multiboot_info const *info = (struct multiboot_info const *)addr;

	eio_init();

	if (magic != MB_BOOT_MAGIC) {
		eio_puts("Multiboot loader expected!");
		return;
	}

	if (info->flags & MBI_MEMORY_INFO)
		eio_printf("lower memory = %x KB, upper memory = %x KB\n",
			(unsigned) info->lower_mem, (unsigned) info->upper_mem);

	eio_puts("Multiboot example loaded!");
	while (1);
}
