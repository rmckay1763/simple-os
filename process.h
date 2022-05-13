/**
 * @file process.h
 * @author Robert McKay
 * @brief Declares structures and functions to support multi processing.
 * @version 0.1
 * @date 2022-05-12
 * 
 */

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

/**
 * @brief Structure for a process control block.
 * 
 */
struct pcb_s {
    unsigned int esp;
    unsigned int pid;
} __attribute__ ((packed));

/**
 * @brief Type definition for a process control block.
 * 
 */
typedef struct pcb_s pcb_t;

/**
 * @brief Allocates a pcb structure to a process.
 * 
 * @return pcb_t* Pointer to the pcb.
 */
pcb_t* alloc_pcb();

/**
 * @brief Allocates a stack to a process.
 * 
 * @return unsigned int* Pointer to the top of the stack.
 */
unsigned int* alloc_stack();

/**
 * @brief Creates a new process and adds it to the queue.
 * 
 * @param process_entry The entry point of the process.
 * @return int EXIT_SUCCESS (0) if successful, EXIT_FAILURE (1) otherwise.
 */
int create_process(unsigned int process_entry);

/**
 * @brief Initializes the stack for a new process.
 * 
 * @param tos Pointer to the top of the stack.
 * @param process_entry The entry point of the process.
 */
void init_stack(unsigned int** tos, unsigned int process_entry);

/*-------------------------------- push --------------------------------------
    Pushes a value on the processes stack.

    Parameters:
        tos - points to the processes top of stack.
        value - the value to push.
-----------------------------------------------------------------------------*/

/**
 * @brief Pushes a value on the stack.
 * 
 * @param tos Pointer to the top of the stack.
 * @param value The value to push.
 */
void push(unsigned int** tos, unsigned int value);

#endif