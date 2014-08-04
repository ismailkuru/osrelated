#include "earlyio.h"
#include "types.h"
#include "param.h"

static void print_memory_map(struct memory_map const * map)
{
	u32 i;
	eio_puts("memory map:\n");
	for (i = 0; i < map->entries; ++i) {
		eio_printf("mem 0x%x-0x%x %s\n",
		            (unsigned)(map->chunk[i].addr),
		            (unsigned)(map->chunk[i].addr +
		                       map->chunk[i].size - 1),
		            (map->chunk[i].type == RAM_CHUNK_USABLE) ?
		                       "usable" : "reserved");
	}
}

void entry_32()
{
	eio_init();
	eio_puts("Kernel is loaded\n");
	print_memory_map(&boot_params.mmap);
}
