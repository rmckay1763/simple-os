Title: Project Three
Author: Robert McKay
Date: 11/13/2021

Implements a primitive operating system.

Features:
    Multiprocessing with round robin queue.
    Interrupt handler for keyboard events.
    Supports all keys that produce printable characters.
    Supports the following functional keys:
        shift, caps lock, space, backspace, tab, enter
    Default interrupt handler for system interrupts.

Build Instructions (most useful targets):
    make run - install and run the os in normal mode.
    make debug - install and and run the os in debug mode.
    make install - install the os.
    make clean - remove everything except source files.

WSL Notes:
    Compiles with -fno-stack-protector to keep linker happy.
    Makefile run and debug targets use -curses option.