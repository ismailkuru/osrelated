#define NCPU 4

#define RAM_CHUNK_USABLE   1
#define RAM_CHUNK_MAX    128

#ifndef __ASM_FILE__

#include "types.h"

struct __attribute__((packed)) mmap_entry
{
	u64 addr;
	u64 size;
        u32 type;
};

struct memory_map
{
	u32 entries;
	struct mmap_entry chunk[RAM_CHUNK_MAX];
};

struct boot_params
{
	struct memory_map mmap;
};

extern struct boot_params boot_params;
extern char __bss_first;
extern char __bss_last;
extern char __kernel_start;
extern char __kernel_end;

#endif
