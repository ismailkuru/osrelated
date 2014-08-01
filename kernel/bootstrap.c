#include "multiboot.h"
#include "types.h"
#include "layout.h"
#include "mmu.h"

#define ALIGNED(x) __attribute__((__aligned__(x)))
#define SECTION(x) __attribute__((section(x)))
#define BOOTSTRAP SECTION(".bootstrap")
#define PA(x) ((void *)V2P((char *)(x)))

ALIGNED(PAGE_SIZE) pde_t pgdir[PD_SIZE];
ALIGNED(PAGE_SIZE) pte_t pg0[PT_SIZE];
ALIGNED(PAGE_SIZE) pte_t pg1[PT_SIZE];

pte_t * BOOTSTRAP page_entry(pte_t *pt, size_t idx)
{
	return (pt + idx);
}

pde_t * BOOTSTRAP dir_entry(pde_t *pd, size_t idx)
{
	return (pd + idx);
}

void BOOTSTRAP setup_mapping(void)
{
	pte_t const pte_flags = PTE_P | PTE_W;
	pde_t const pde_flags = PDE_P | PDE_W;

	for (size_t index = 0; index != PT_SIZE; ++index) {
		*page_entry(PA(pg0), index) = (index * PAGE_SIZE) | pte_flags;
		*page_entry(PA(pg1), index) = (index * PAGE_SIZE) | pte_flags;
	}

	*dir_entry(PA(pgdir), PD_INDEX(0)) = (pde_t)PA(pg0) | pde_flags;
	*dir_entry(PA(pgdir), PD_INDEX(VIRTUAL_ADDRESS_BASE)) = (pde_t)PA(pg1) | pde_flags;
}

void BOOTSTRAP setup(void)
{
	extern void enter_pm(void);
	setup_mapping();
	enter_pm();
}
