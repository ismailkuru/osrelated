#include "mbr.h"

uint32_t chs_head(struct chs_address const *addr)
{
	return addr->head;
}

uint32_t chs_sector(struct chs_address const *addr)
{
	return addr->sector & 0x3Fu;
}

uint32_t chs_cylinder(struct chs_address const *addr)
{
	return ((addr->sector & 0xC0u) << 2) + addr->cylinder;
}

uint32_t mbr_partition_lba_first(struct mbr_partition_entry const *entry)
{
	return le32_to_cpu(entry->lba_first_sector);
}

uint32_t mbr_partition_size(struct mbr_partition_entry const *entry)
{
	return le32_to_cpu(entry->partition_size);
}

struct mbr_sector *mbr_sector(uint8_t *sector)
{
	struct mbr_sector *ptr = (struct mbr_sector *)sector;
	if (ptr->sign_lower == 0x55u && ptr->sign_upper == 0xAAu)
		return ptr;
	return 0;
}

struct mbr_partition_entry *mbr_boot_entry(struct mbr_sector *sector)
{
	size_t i;
	for (i = 0; i != PARTITION_TABLE_SIZE; ++i) {
		if (sector->table[i].status & MBR_BOOT_ENTRY)
			return &sector->table[i];
	}
	return 0;
}
