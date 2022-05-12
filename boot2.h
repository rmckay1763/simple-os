/*--------------------------------- boot2.h -----------------------------------

    Header file for boot2.S
    Boot2.S defines external functions need by c files.

    Functions:
        k_print - moves a given string to video memory.
        k_scroll - scrolls video memory up by one row.
        kbd_enter - interrupt handler for keyboard.
        default_handler - default interrupt handler.
        lidtr - loads the IDT.
        outportb - writes given byte to specified port.
        go - dequeues the next process and jumps to it.
        dispatch - enqueues the current process and calls go.
        kbd_block - blocks a process waiting on keyboard input.
        init_timer_dev - initializes the timer interval.

    Author: Robert McKay (except for k_scroll)
    Since: 11/26/2021

-----------------------------------------------------------------------------*/

#ifndef BOOT2_H
#define BOOT2_H

/*---------------------------------- k_print ----------------------------------
    Moves a given string to video memory.
    Defined in boot2.S

    Paremeters:
        text - address of string to print.
        size - length of string to print.
        column - column of video memory.
        row - row of video memory.
-----------------------------------------------------------------------------*/
extern void k_print(char* text, int size, int column, int row);

/*---------------------------------- k_scroll ---------------------------------
    Scrolls the bytes in video memory up one row.
    Defined in boot2.S
-----------------------------------------------------------------------------*/
extern void k_scroll();

/*--------------------------------- kbd_enter ---------------------------------
    Keyboard interupt handler.
    Defined in boot2.S
-----------------------------------------------------------------------------*/
extern void kbd_enter();

/*----------------------------- default_handler -------------------------------
    Default interrupt handler.
    Defined in boot2.S
-----------------------------------------------------------------------------*/
extern void default_handler();

/*----------------------------------- lidtr -----------------------------------
    Loads the idt.
    Defined in boot2.S

    Paremeters:
        idtr - address of struct with limit and idt address
-----------------------------------------------------------------------------*/
extern void lidtr(unsigned int idtr);

/*---------------------------------- outportb ---------------------------------
    Writes a given byte to the specified port address.
    Defined in boot2.S

    Paremeters:
        port - address of the port to write to.
        value - the byte to write to the port.
-----------------------------------------------------------------------------*/
extern void outportb(unsigned short port, unsigned char value);

/*----------------------------------- go --------------------------------------
    Dequeue the next process, restore its state, and jump to it.
-----------------------------------------------------------------------------*/
extern void go();

/*------------------------------- dispatch ------------------------------------
    Save state and enqueue current process, call go.
-----------------------------------------------------------------------------*/
extern void dispatch();

/*------------------------------ kbd_block ------------------------------------
    Block a process waiting on keyboard input.
-----------------------------------------------------------------------------*/
extern void kbd_block();

/*---------------------------- init_timer_dev ---------------------------------
    Initialize the timer interval device.

    Parameters: 
        interval - the interval in milli seconds for the timer.
-----------------------------------------------------------------------------*/
extern void init_timer_dev(unsigned int interval);


#endif