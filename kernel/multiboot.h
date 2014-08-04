#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__

#define MB_HEADER_MAGIC  0x1BADB002
#define MB_BOOT_MAGIC    0x2BADB002

#define MBF_PAGE_ALIGN   0x00000001
#define MBF_MEMORY_INFO  0x00000002

#define MBI_MEMORY_INFO  0x00000001
#define MBI_BOOTDEV_INFO 0x00000002
#define MBI_CMDLINE_INFO 0x00000004
#define MBI_MEMMAP_INFO  0x00000040

/* there are other multiboot flags that i do not support so far */

#ifndef __ASM_FILE__

#include "types.h"

struct aout_symbol_table
{
	u32 tabsize;
	u32 strsize;
	u32 addr;
	u32 reserved;
};

struct elf_section_table
{
	u32 num;
	u32 size;
	u32 addr;
	u32 shndx;
};

struct __attribute__((packed)) multiboot_mmap_entry
{
	u32 size;
	u64 addr;
	u64 len;
	u32 type;
};

struct multiboot_info
{
	u32 flags;
	u32 lower_mem;
	u32 upper_mem;
	u32 boot_device;
	u32 cmdline;
	u32 mods_count;
	u32 mods_addr;
	union
	{
		struct aout_symbol_table aout_sym;
		struct elf_section_table elf_sec;
	} u;
	u32 mmap_length;
	u32 mmap_addr;
	u32 drives_length;
	u32 drives_addr;
	u32 rom_config_table;
	u32 bootloader_name;
	u32 apm_table;
	u32 vbe_control_info;
	u32 vbe_mode_info;
	u16 vbe_mode;
	u16 vbe_interface_seg;
	u16 vbe_interface_off;
	u16 vbe_interface_len;
};

#endif

#endif /*__MULTIBOOT_H__*/
