/*----------------------------------- itd.h -----------------------------------

    Header file for idt.c
    idt.c provides procedures to initialize the interrupt descriptor table.

    Functions:
        initIDTEntry - initialize a single IDT entry
        initIDT - initialze the IDT table
        setupPIC - configure the PIC

    Author: Robert McKay
    Since: 11/13/2021

-----------------------------------------------------------------------------*/

#ifndef IDT_H
#define IDT_H

#define IDT_SIZE 256

/* Structure to represent a single interrupt descriptor */
struct idt_entry_s {
    unsigned short base_low16;
    unsigned short selector;
    unsigned char zero;
    unsigned char access;
    unsigned short base_hi16;
} __attribute__ ((packed));

/* Structure for the limit and base address of the IDT */
struct idt_r_s {
    unsigned short limit;
    unsigned int base;
} __attribute__ ((packed));

/* type definitions */
typedef struct idt_entry_s idt_entry_t;
typedef struct idt_r_s idt_r_t;


/* ----------------------------- initIDTEntry ---------------------------------
    Initializes an entry in the IDT table.

    Parameters:
        entry - index of the the entry to initialize.
        base - the memory address of the routine for the interrupt
        selector - the code segment
        access - access bits for the entry
-----------------------------------------------------------------------------*/
void initIDTEntry(unsigned int entry, unsigned int base, 
                  unsigned short selector, unsigned char access);

/* -------------------------------- initIDT -----------------------------------
   Initializes the IDT
-----------------------------------------------------------------------------*/
void initIDT();

/* -------------------------------- setupPIC ----------------------------------
   Configures the PIC
-----------------------------------------------------------------------------*/
void setupPIC();

#endif