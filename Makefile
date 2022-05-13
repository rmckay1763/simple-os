# Makefile for project two
# Author: Robert McKay
# Since: 11/26/2021

# variables
OBJECTS = boot2.o io.o idt.o keyboard.o buffer.o driver.o scheduler.o process.o
HEADERS = driver.h io.h idt.h buffer.h keyboard.h sheduler.h process.h boot2.h
COMPILER = gcc
LINKER = ld
CFLAGS = -g -m32 -fno-stack-protector -c -o
SFLAGS = -masm=intel $(CFLAGS)
LFLAGS = -g -melf_i386 -Ttext 0x10000 -e main -o

# target to run operating system
run: install
	qemu-system-i386 -curses -boot a -fda a.img

# target to run operating system in debug mode
debug: install
	qemu-system-i386 -S -s -curses -boot a -fda a.img

# target to install operating system
install: boot2 boot1 a.img
	dd if=boot1 of=a.img bs=1 count=512 conv=notrunc
	mcopy -o boot2 a:BOOT2

# target to create image
a.img:
	bximage -mode=create -fd=1.44M  -q a.img
	mkdosfs a.img

# target to create boot1
boot1: boot1.asm boot2.exe
	nasm -l boot1.list -DENTRY=`./getaddr.sh main` boot1.asm

# target to create boot2
boot2: boot2.exe
	objcopy -j .text* -j .data* -j .rodata* -S -O binary boot2.exe boot2

# rule for executables
%.exe: $(OBJECTS)
	$(LINKER) $(LFLAGS) $@ $^

# rule for c files
%.o: %.c $(HEADERS)
	$(COMPILER) $(CFLAGS) $@ $<

# rule for assembly file
boot2.o : boot2.S
	$(COMPILER) $(SFLAGS) $@ $<

clean:
	rm *.o *.exe *.list *.img boot1 boot2