# Simple OS

### **Synopsis**

Implements a (extra emphasis) primitive operating system.

---

### **Objective**

Build a simple operating system for the x86 architecture with the following features:
- Basic keyboard I/O.
- Multiprocessing with round robin queue and timer interrupts.
- Blocked queue for I/O interrupts.

---

### **Implementation**

The project uses x86 assembly and C to implement the features.

**Assembly Files**
- **`Boot1.S`** - Provided bootloader file.
- **`Boot2.S`** - Defines various functions that require assembly instructions.

**C files**
- **`buffer.c/h`** - Defines a circular buffer for keyboard input.
- **`keyboard.c/h`** - Handles translating scancodes from the keyboard.
- **`io.h/c`** - Handles writing to the screen.
- **`idt.h/c`** - Sets up the IDT table and the PIC.
- **`process.h/c`** - Defines PCB and functions to create processes.
- **`scheduler.h/c`** - Defines a ready queue and blocked queue for process scheduling.

---

### **Prerequisites**

Project developed on WSL2 with Ubuntu 20.04. Standard linux distros include most of the requirements expected by the `Makefile`. Install packages and/or configure path if necessary.
- [**`nasm`**](http://manpages.ubuntu.com/manpages/focal/man1/nasm.1.html) for assembling `boot1.asm`.
- [**`gcc`**](https://manpages.ubuntu.com/manpages/focal/man1/gcc.1.html) for compiling C files and `boot2.S`.
- [**`ld`**](https://manpages.ubuntu.com/manpages/focal/man1/ld.1.html) for linking object files.
- [**`objcopy`**](http://manpages.ubuntu.com/manpages/focal/man1/arm-none-eabi-objcopy.1.html) for producing raw binary.
- [**`bximage`**](http://manpages.ubuntu.com/manpages/focal/man1/bximage.1.html) for creating the boot image.
- [**`mkdosfs`**](https://linux.die.net/man/8/mkdosfs) for making the file system.
- [**`dd`**](http://manpages.ubuntu.com/manpages/focal/man1/dd.1.html) for copying boot1 to the image.
- [**`mcopy`**](http://manpages.ubuntu.com/manpages/focal/man1/mcopy.1.html) for copying boot2 to the image.
- [**`qemu-system-i386`**](http://manpages.ubuntu.com/manpages/bionic/man1/qemu-system.1.html) for booting the image.

`mcopy` requires a user configuration file in the home directory. Move the provided `.mtoolsrc` file into the home directory.
```
mv ./.mtoolsrc ~/.mtoolsrc
```

---

### **Usage**

The provided `Makefile` includes several useful targets.
- **`make run`** - Runs the os with `qemu`
- **`make debug`** - Runs `qemu` in debug mode.
    ```
    (gdb) target remote localhost:1234
    ```
- **`make install`** - Builds the project.
- **`make clean`** - Removes build artifacts.

---

### **WSL2 Notes**

`qemu` tries to use a graphical interface to display the program. To accomodate WSL2's lack of graphics support, the `run` and `debug` targets in the `Makefile` use the `-curses` option to display the program in the console.

The linker complained about an undefined reference to `__stack_chk_fail_local` when building the project on WSL2. The `CFLAGS` variable in the `Makefile` includes the `-fno-stack-protector` to keep the linker happy.

Unless building the project on an imposter such as WSL2, consider removing `-curses` from the `run` and `debug` targets and removing the `-fno-stack-protector` flag from `CFLAGS`.