#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__

#define MB_HEADER_MAGIC 0x1BADB002
#define MB_BOOT_MAGIC   0x2BADB002

#define MBF_PAGE_ALIGN  0x00000001
/* there are other multiboot flags that i do not support so far */

#ifndef __ASM_FILE__

#include "types.h"

struct multiboot_header
{
	/* mandatory fields */
	u32 magic;
	u32 flags;
	u32 checksum;

	/* there are other fields that i do not support so far */
};

#endif

#endif /*__MULTIBOOT_H__*/
