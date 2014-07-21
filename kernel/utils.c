void itoa(char *buf, int d, int base)
{
	char *begin = buf, *end = buf;
	unsigned n = d;

	if (base == 10 && d < 0) {
		n = -d;
		*begin++ = '-';
	}

	do {
		int const rem = n % base;
		*end++ = (rem < 10) ? rem + '0' : rem + 'a' - 10;
	} while (n /= base);

	*end-- = 0;
	while (begin < end) {
		char tmp = *begin;
		*begin++ = *end;
		*end-- = tmp;
	}
}
