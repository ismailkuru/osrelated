CC = gcc
LD = ld

CFLAGS = -Wall -Wextra -Werror -std=gnu99 \
	-ffreestanding -fno-stack-protector \
	-MMD -m32 -g
ASFLAGS = -D__ASM_FILE__ -MMD -m32 -g

OBJS = \
	bootstrap.o \
	entry.o \
	earlyio.o \
	boot.o \
	utils.o \

default : kernel

kernel : $(OBJS) kernel.ld
	$(LD) -nostdinc -T kernel.ld $(OBJS) -o $@
	objcopy --only-keep-debug $@ kernel.sym
	objcopy --strip-debug $@

%.o : %.S
	$(CC) $(ASFLAGS) -c $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

-include *.d

clean:
	rm -rf kernel kernel.sym *.o *.d

.PHONY : clean
