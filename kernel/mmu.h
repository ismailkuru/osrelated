#define PAGE_SIZE     4096
#define PD_SIZE       1024
#define PT_SIZE       1024
#define PD_ENTRY_SIZE    4
#define PT_ENTRY_SIZE    4
#define DT_SIZE         16
#define DT_ENTRY_SIZE    8
#define PD_SHIFT        22
#define PT_SHIFT        12

#define PD_INDEX(va) ((va) >> PD_SHIFT)

#define PTE_P   0x00000001
#define PTE_W   0x00000002
#define PTE_U   0x00000004
#define PTE_PWT 0x00000008
#define PTE_PCD 0x00000010
#define PTE_A   0x00000020
#define PTE_D   0x00000040
#define PTE_PAT 0x00000080
#define PTE_G   0x00000100

#define PDE_P   0x00000001
#define PDE_W   0x00000002
#define PDE_U   0x00000004
#define PDE_PWT 0x00000008
#define PDE_PCD 0x00000010
#define PDE_A   0x00000020

#define CR0_PE  0x00000001
#define CR0_MP  0x00000002
#define CR0_EM  0x00000004
#define CR0_TS  0x00000008
#define CR0_ET  0x00000010
#define CR0_NE  0x00000020
#define CR0_WP  0x00010000
#define CR0_AM  0x00040000
#define CR0_NW  0x20000000
#define CR0_CD  0x40000000
#define CR0_PG  0x80000000

#ifndef __ASM_FILE__

typedef u32  pte_t;
typedef u32  pde_t;

#endif
