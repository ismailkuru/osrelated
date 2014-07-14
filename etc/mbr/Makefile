CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD
LDFLAGS = 

OBJS = \
	endianness.o \
	mbr.o \
	main.o \

all: mbr

mbr: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.PRECIOUS: %.o

-include *.d

clean:
	rm -rf *.o mbr

distclean: clean
	rm -rf *.d

.PHONY: clean
