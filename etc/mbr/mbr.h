#ifndef __MBR_FORMAT_H__
#define __MBR_FORMAT_H__

#include "endianness.h"

struct __attribute__ ((__packed__)) chs_address {
	uint8_t	head;
	uint8_t	sector;
	uint8_t	cylinder;
};

uint32_t chs_head(struct chs_address const *addr);
uint32_t chs_sector(struct chs_address const *addr);
uint32_t chs_cylinder(struct chs_address const *addr);


#define	MBR_BOOT_ENTRY	0x80u
struct __attribute__ ((__packed__)) mbr_partition_entry {
	uint8_t			status;
	struct chs_address	first_sector;
	uint8_t			type;
	struct chs_address	last_sector;
	le32			lba_first_sector;
	le32			partition_size;
};

uint32_t mbr_partition_lba_first(struct mbr_partition_entry const *entry);
uint32_t mbr_partition_size(struct mbr_partition_entry const *entry);

#define	PARTITION_TABLE_SIZE	4
struct __attribute__ ((__packed__)) mbr_sector {
	uint8_t				bootstrap_code[446];
	struct mbr_partition_entry	table[PARTITION_TABLE_SIZE];
	uint8_t				sign_lower;
	uint8_t				sign_upper;
};

struct mbr_sector *mbr_sector(uint8_t *sector);
struct mbr_partition_entry *mbr_boot_entry(struct mbr_sector *sector);

#endif /*__MBR_FORMAT_H__*/
