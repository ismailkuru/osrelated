#define NCPU 4

#define E820_RAM         1
#define E820_RESERVED    2
#define E820_ACPI        3
#define E820_NVS         4
#define E820_UNUSABLE    5
#define E820_MAX       128

#ifndef __ASM_FILE__

#include "types.h"

struct __attribute__((packed)) e820_entry
{
	u64 addr;
	u64 size;
        u32 type;
};

struct e820_map
{
	u32 entries;
	struct e820_entry map[E820_MAX];
};

struct boot_params
{
	struct e820_map e820_mem_info;
};

extern struct boot_params boot_params;

#endif 
