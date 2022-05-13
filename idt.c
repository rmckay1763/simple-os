/**
 * @file idt.c
 * @author Robert McKay
 * @brief Defines procedures to initialize the interrupt descriptor table.
 * @version 0.1
 * @date 2022-05-12
 * 
 */

#include "boot2.h"
#include "idt.h"

/**
 * @brief Interrupt Descriptor Table.
 * 
 */
idt_entry_t idt[IDT_SIZE];

/**
 * @brief Base address and limit of IDT.
 * 
 */
idt_r_t idtr;

void initIDTEntry(unsigned int entry, unsigned int base, 
                  unsigned short selector, unsigned char access) {
    idt[entry].base_low16 = (base & 0x0000ffff);
    idt[entry].selector = selector;
    idt[entry].zero = 0;
    idt[entry].access = access;
    idt[entry].base_hi16 = (base & 0xffff0000) >> 16;
}

void initIDT() {
    /* entries 0-31 */
    for (unsigned int entry = 0; entry < 31; entry++) {
        initIDTEntry(entry, (unsigned int)default_handler, 0x10, 0x8e);
    }

    /* entry 32 */
    initIDTEntry(32, (unsigned int)dispatch, 0x10, 0x8e);

    /* entry 33 */
    initIDTEntry(33, (unsigned int)kbd_enter, 0x10, 0x8e);

    /* entries 34-255 */
    for (unsigned int entry = 34; entry < IDT_SIZE; entry++) {
        initIDTEntry(entry, 0, 0, 0);
    }

    /* load idt */
    idtr.limit = sizeof(idt_entry_t) * IDT_SIZE - 1;
    idtr.base = (unsigned int)&idt;
    lidtr((unsigned int)&idtr);
}

void setupPIC() {
    outportb(0x20, 0x11);   /* start 8259 master initialization */
    outportb(0xa0, 0x11);   /* start 8259 slave initialization */

    outportb(0x21, 0x20);   /* set master base interrupt vector (idt 32-38) */
    outportb(0xa1, 0x28);   /* set slave base interrupt vector (idt 39-45) */

    outportb(0x21, 0x04);   /* set cascade ... */
    outportb(0xa1, 0x02);   /* on IRQ2 */

    outportb(0x21, 0x01);   /* finish 8259 initialization */
    outportb(0xa1, 0x01);

    outportb(0x21, 0x0);    /* Reset the IRQ masks */
    outportb(0xa1, 0x0);

    outportb(0x21, 0xfc);   /* Turn on the keyboard IRQ */
    outportb(0xa1, 0xff);   /* Turn off all others */
}