#include "earlyio.h"
#include "types.h"
#include "utils.h"

static unsigned const COLUMNS = 80;
static unsigned const ROWS = 24;
static unsigned const VIDEO_MEMORY_START = 0xB8000;
static unsigned char const ATTRIBUTE = 7;

static volatile unsigned char *eio_video_buffer = 0;
static unsigned eio_output_row = 0;
static unsigned eio_output_column = 0;

static void eio_newline(void)
{
	eio_output_column = 0;
	eio_output_row = (eio_output_row + 1) % ROWS;
}

void eio_init(void)
{
	unsigned it;

	eio_video_buffer = (unsigned char *) VIDEO_MEMORY_START;
	eio_output_row = eio_output_column = 0;

	for (it = 0; it != COLUMNS * ROWS * 2; ++it)
		*(eio_video_buffer + it) = 0;
}

void eio_putchar(int c)
{
	unsigned const shift = (eio_output_column + eio_output_row * COLUMNS)*2;

	if (c == '\n') {
		eio_newline();
		return;
	}

	*(eio_video_buffer + shift) = c & 0xFF;
	*(eio_video_buffer + shift + 1) = ATTRIBUTE;

	if (++eio_output_column == COLUMNS)
		eio_newline();
}

void eio_puts(char const *asciiz)
{
	while (*asciiz)
		eio_putchar(*asciiz++);
}

#include <stdarg.h>

void eio_printf(char const *fmt, ...)
{
	char buffer[20];
	int c;

	va_list vararg_lst;
	va_start(vararg_lst, fmt);

	while ((c = *fmt++) != 0) {
		if (c != '%') {
			eio_putchar(c);
			continue;
		}

		c = *fmt++;
		if (c == 'd' || c == 'u' || c == 'x') {
			int value = va_arg(vararg_lst, int);
			itoa(buffer, value, (c == 'x' ? 16 : 10));
			eio_puts(buffer);	
		} else if (c == 's') {
			eio_puts(va_arg(vararg_lst, char const *));
		} else if (c == 'c') {
			eio_putchar(va_arg(vararg_lst, int));
		} else {
			eio_putchar(c);
		}
	}

	va_end(vararg_lst);
}
