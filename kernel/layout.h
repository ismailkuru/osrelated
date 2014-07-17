/* first virtual address of kernel space */
#define KERNEL_BASE  0xC0000000

/* actually shift of kernel from KERNEL_BASE */
#define EXT_MEM_SIZE 0x00100000

/* address where kernel is linked */
#define KERNEL_LINK  (KERNEL_BASE + EXT_MEM_SIZE)
