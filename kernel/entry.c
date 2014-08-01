#include "earlyio.h"
#include "types.h"

void entry_32()
{
	eio_init();
	eio_puts("Kernel is loaded");
}
