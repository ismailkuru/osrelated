#include "multiboot.h"
#include "types.h"
#include "layout.h"
#include "mmu.h"
#include "param.h"

#define ALIGNED(x) __attribute__((__aligned__(x)))
#define PA(x) ((void *)V2P((char *)(x)))

ALIGNED(PAGE_SIZE) pde_t pgdir[PD_SIZE];
ALIGNED(PAGE_SIZE) pte_t pg0[PT_SIZE];
ALIGNED(PAGE_SIZE) pte_t pg1[PT_SIZE];

struct boot_params boot_params;

#if __GNUC__
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif

void setup_initial_mapping(void)
{
	pte_t * const pg0_phys = PA(pg0);
	pte_t * const pg1_phys = PA(pg0);
	pde_t * const pgdir_phys = PA(pgdir);

	pte_t const pte_flags = PTE_P | PTE_W;
	pde_t const pde_flags = PDE_P | PDE_W;

	for (size_t index = 0; index != PT_SIZE; ++index) {
		*(pg0_phys + index) = (index * PAGE_SIZE) | pte_flags;
		*(pg1_phys + index) = (index * PAGE_SIZE) | pte_flags;
	}

	*(pgdir_phys + PD_INDEX(0)) = (pde_t)pg0_phys | pde_flags;
	*(pgdir_phys + PD_INDEX(VIRTUAL_ADDRESS_BASE)) = (pde_t)pg1_phys | pde_flags;
}

void fill_mem_map(struct multiboot_info *mbi)
{
	struct multiboot_mmap_entry * const mmap_info =
				(struct multiboot_mmap_entry *)mbi->mmap_addr;
	size_t const length = mbi->mmap_length;

	struct multiboot_mmap_entry *entry = mmap_info;
	struct boot_params * const params = PA(&boot_params);
	struct memory_map * const map = &params->mmap;
	size_t count = 0;
	while ((size_t)entry < (size_t)mmap_info + length) {
		map->chunk[count].addr = entry->addr;
		map->chunk[count].size = entry->len;
		map->chunk[count].type = entry->type;

		entry = (struct multiboot_mmap_entry *)
                          ((size_t)entry + entry->size + sizeof(entry->size));
		++count;
	}
	map->entries = count;
}
