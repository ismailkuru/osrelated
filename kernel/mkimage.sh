#!/usr/bin/bash

KERNEL=kernel
IMAGE_NAME=disk.img
TMPDIR=./tmp
USER=`whoami`


dd if=/dev/zero of=$IMAGE_NAME bs=1M count=64
echo -e "n\np\n1\n\n\na\n1\nw" | fdisk $IMAGE_NAME >/dev/null 2>/dev/null

PARTITION=`sudo losetup -f`
sudo losetup $PARTITION $IMAGE_NAME

FILESYSTEM=`sudo losetup -f`
sudo losetup $FILESYSTEM $IMAGE_NAME -o 1048576
sudo mke2fs $FILESYSTEM

mkdir $TMPDIR
sudo mount -t ext2 $FILESYSTEM $TMPDIR
sudo chown $USER:$USER $TMPDIR

mkdir -p $TMPDIR/boot/grub
cp $KERNEL $TMPDIR/boot
echo "insmod part_msdos
insmod ext2
set root='(hd0,msdos1)'
set timeout=15
set default=0

menuentry \"Study OS\" {
	insmod part_msdos
	insmod ext2
	set root='(hd0,msdos1)'
	multiboot /boot/kernel
	boot
}
" > $TMPDIR/boot/grub/grub.cfg

sudo grub-install --no-floppy --boot-directory=$TMPDIR/boot --modules="normal part_msdos ext2" $PARTITION
sync

sudo umount $TMPDIR
rm -r $TMPDIR
sudo losetup -d $FILESYSTEM
sudo losetup -d $PARTITION
