#include "multiboot.h"
#include "types.h"
#include "layout.h"
#include "mmu.h"
#include "param.h"

#define ALIGNED(x) __attribute__((__aligned__(x)))
#define SECTION(x) __attribute__((section(x)))
#define BOOTSTRAP SECTION(".bootstrap")
#define PA(x) ((void *)V2P((char *)(x)))


ALIGNED(PAGE_SIZE) pde_t pgdir[PD_SIZE];
ALIGNED(PAGE_SIZE) pte_t pg0[PT_SIZE];
ALIGNED(PAGE_SIZE) pte_t pg1[PT_SIZE];


struct boot_params boot_params;
#define BOOT_PARAMS ((struct boot_params *)PA(&boot_params))


void BOOTSTRAP setup_mapping(void)
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

void BOOTSTRAP fill_mem_map(struct multiboot_mmap_entry *mmap, size_t length)
{
	struct e820_map * const e820_map = &BOOT_PARAMS->e820_mem_info;
	struct multiboot_mmap_entry *entry = mmap;
	size_t count = 0;
	while ((size_t)entry < (size_t)mmap + length) {
		e820_map->map[count].addr = entry->addr;
		e820_map->map[count].size = entry->len;
		e820_map->map[count].type = entry->type;

		entry = (struct multiboot_mmap_entry *)
                          ((size_t)entry + entry->size + sizeof(entry->size));
		++count;
	}
	e820_map->entries = count;
}

void BOOTSTRAP setup(u32 magic, struct multiboot_info *mbi)
{
	extern void enter_pm(void);

	if (magic != MB_BOOT_MAGIC)
		return;

	if (!(mbi->flags & MBI_MEMMAP_INFO))
		return;

        fill_mem_map((struct multiboot_mmap_entry *)mbi->mmap_addr,
                       mbi->mmap_length);
	setup_mapping();
	enter_pm();
}
