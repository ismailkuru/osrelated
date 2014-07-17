#include "multiboot.h"
#include "earlyio.h"
#include "types.h"

void setup(u32 magic)
{
	eio_init();

	if (magic != MB_BOOT_MAGIC) {
		eio_puts("Multiboot loader expected!");
		return;
	}

	eio_puts("Multiboot example loaded!");
	while (1);
}
