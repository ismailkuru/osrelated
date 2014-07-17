#ifndef __EARLY_IO_H__
#define __EARLY_IO_H__

void eio_init(void);
void eio_putchar(int c);
void eio_puts(char const *asciiz);

#endif /*__EARLY_IO_H__*/
