/**
 * @file idt.h
 * @author Robert McKay
 * @brief Declares procedures to initialize the interrupt descriptor table.
 * @version 0.1
 * @date 2022-05-12
 * 
 */

#ifndef IDT_H
#define IDT_H

#define IDT_SIZE 256

/**
 * @brief Structure to represent a single interrupt descriptor.
 * 
 */
struct idt_entry_s {
    unsigned short base_low16;
    unsigned short selector;
    unsigned char zero;
    unsigned char access;
    unsigned short base_hi16;
} __attribute__ ((packed));

/**
 * @brief Structure for the limit and base address of the IDT.
 * 
 */
struct idt_r_s {
    unsigned short limit;
    unsigned int base;
} __attribute__ ((packed));

/**
 * @brief Type definition for a single interrupt descriptor.
 * 
 */
typedef struct idt_entry_s idt_entry_t;

/**
 * @brief Type definition for the base/limit of the IDT.
 * 
 */
typedef struct idt_r_s idt_r_t;

/**
 * @brief Initializes an entry in the IDT table.
 * 
 * @param entry index of the the entry to initialize.
 * @param base the memory address of the routine for the interrupt.
 * @param selector the code segment.
 * @param access access bits for the entry.
 */
void initIDTEntry(unsigned int entry, unsigned int base, 
                  unsigned short selector, unsigned char access);

/**
 * @brief Initializes the Interrupt Descriptor Table.
 * 
 */
void initIDT();

/**
 * @brief Configures the Programmerable Interrupt Controller.
 * 
 */
void setupPIC();

#endif