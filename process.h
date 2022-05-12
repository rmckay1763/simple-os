/*------------------------------- process.h -----------------------------------

    Header file for process.c
    process.c provides support implementing process.

    Functions:
        alloc_pcb - allocates a pcb to a process.
        alloc_stack - allocates a stack to a process.
        create_process - initializes a process and adds it to the queue.
        init_stack - initializes the stack for a new process.
        push - pushes a value on the stack.

    Author: Robert McKay
    Since: 11/13/2021

-----------------------------------------------------------------------------*/

#ifndef PROCESS_H
#define PROCESS_H

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define STACK_SIZE 1024
#define CS 0x10
#define SEGMENT_REGISTERS 0x8
#define GENERAL_REGISTERS 0x0
#define EFLAGS 0x0200

/* structure for a process control block */
struct pcb_s {
    unsigned int esp;
    unsigned int pid;
} __attribute__ ((packed));
typedef struct pcb_s pcb_t;

/*------------------------------- alloc_pcb -----------------------------------
    Allocates a pcb structure to a process.

    Returns: a pointer to the pcb.
-----------------------------------------------------------------------------*/
pcb_t* alloc_pcb();

/*------------------------------ alloc_stack ----------------------------------
    Allocates a stack to a process.

    Returns: a pointer to the top of the stack.
-----------------------------------------------------------------------------*/
unsigned int* alloc_stack();

/*---------------------------- create_process ---------------------------------
    Creates a new process and adds it to the queue.

    Parameters:
        process_entry - the entry point of the process.

    Returns: EXIT_SUCCESS (0) if successful, EXIT_FAILURE (1) otherwise.
-----------------------------------------------------------------------------*/
int create_process(unsigned int process_entry);

/*------------------------------ init_stack -----------------------------------
    Initializes the stack for a new process.

    Parameters:
        tos - points to the processes top of stack.
        process_entry - the entry point of the process.
-----------------------------------------------------------------------------*/
void init_stack(unsigned int** tos, unsigned int process_entry);

/*-------------------------------- push --------------------------------------
    Pushes a value on the processes stack.

    Parameters:
        tos - points to the processes top of stack.
        value - the value to push.
-----------------------------------------------------------------------------*/
void push(unsigned int** tos, unsigned int value);

#endif