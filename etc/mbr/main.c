#include <stdio.h>
#include "mbr.h"

static void print_partition(struct mbr_partition_entry const *entry)
{
	printf("status: %x, type: %x\n"
		"first sector (h/s/c): %u/%u/%u\n"
		"last sector (h/s/c): %u/%u/%u\n"
		"lba fisrt sector: %u\n"
		"number of sectors: %u\n",
		(unsigned)entry->status,
		(unsigned)entry->type,
		(unsigned)chs_head(&entry->first_sector),
		(unsigned)chs_sector(&entry->first_sector),
		(unsigned)chs_cylinder(&entry->first_sector),
		(unsigned)chs_head(&entry->last_sector),
		(unsigned)chs_sector(&entry->last_sector),
		(unsigned)chs_cylinder(&entry->last_sector),
		(unsigned)le32_to_cpu(entry->lba_first_sector),
		(unsigned)le32_to_cpu(entry->partition_size));
}

static int process_file(char const *fname)
{
	struct mbr_sector const *sector = 0;
	unsigned i;
	uint8_t buffer[512];
	FILE *fp = fopen(fname, "r");
	if (!fp) {
		printf("cannot open file %s\n", fname);
		return 2;
	}

	if (fread(buffer, 1u, 512, fp) != 512) {
		printf("cannot read from file %s\n", fname);
		fclose(fp);
		return 3;
	}
	fclose(fp);

	printf("processing file %s\n", fname);
	sector = mbr_sector(buffer);
	if (!sector)
		printf("first sector is not bootable mbr\n");

	for (i = 0; i != PARTITION_TABLE_SIZE; ++i) {
		printf("partition %u\n", i);
		print_partition(&sector->table[i]);
	}

	return 0;
}

int main(int argc, char **argv)
{
	int i;
	if (argc < 2) {
		printf("file or disk expected\n");
		return 1;
	}

	for (i = 1; i != argc; ++i) {
		int rc = process_file(argv[i]);
		if (rc)
			return rc;
	}

	return 0;
}
