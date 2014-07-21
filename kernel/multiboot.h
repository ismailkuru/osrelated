#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__

#define MB_HEADER_MAGIC 0x1BADB002
#define MB_BOOT_MAGIC   0x2BADB002

#define MBF_PAGE_ALIGN  0x00000001
#define MBF_MEMORY_INFO 0x00000002

#define MBI_MEMORY_INFO 0x00000001

/* there are other multiboot flags that i do not support so far */

#ifndef __ASM_FILE__

#include "types.h"

struct multiboot_header
{
	/* mandatory fields */
	u32 magic;
	u32 flags;
	u32 checksum;

	/* there are other fields */
};

struct multiboot_info
{
	u32 flags;

	u32 lower_mem;
	u32 upper_mem;

	/* there are other fields */
};

#endif

#endif /*__MULTIBOOT_H__*/
