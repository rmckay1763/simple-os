/*------------------------------- process.c -----------------------------------

    Provides support for multiprocessing.

    Author: Robert McKay
    Since: 11/13/2021

-----------------------------------------------------------------------------*/

#include "process.h"
#include "boot2.h"
#include "scheduler.h"
#include "driver.h"

int process_count = 0;
pcb_t pcbs[MAX_PROCESSES];
unsigned int stack[MAX_PROCESSES][STACK_SIZE];

/*------------------------------- alloc_pcb -------------------------------- */
pcb_t* alloc_pcb() {
    if (process_count < MAX_PROCESSES) {
        return &pcbs[process_count];
    }
    return NULL;
}

/*------------------------------ alloc_stack ------------------------------- */
unsigned int* alloc_stack() {
    if (process_count < MAX_PROCESSES) {
        return &stack[process_count][STACK_SIZE];
    }
    return NULL;
}

/*---------------------------- create_process ------------------------------ */
int create_process(unsigned int process_entry) {
    pcb_t* pcb = alloc_pcb();
    unsigned int* tos = alloc_stack();
    if (tos == NULL || pcb == NULL) {
        return EXIT_FAILURE;
    }
    init_stack(&tos, process_entry);
    pcb->esp = (unsigned int)tos;
    pcb->pid = process_count;
    enqueue_process(&ready_queue, pcb);
    process_count++;
    return EXIT_SUCCESS;
}

/*------------------------------- init_stack ------------------------------- */
void init_stack(unsigned int** tos, unsigned int process_entry) {
    
    push(tos, (unsigned int)go);
    push(tos, EFLAGS);
    push(tos, CS);
    push(tos, process_entry);
    // push 0x0 for eax, ebx, ecx, edx, esi, edi, esp, ebp
    for (int i = 0; i < 8; i++) {
        push(tos, GENERAL_REGISTERS);
    }
    // push 0x8 for ds, es, fs, gs
    for (int i = 0; i < 4; i++) {
        push(tos, SEGMENT_REGISTERS);
    }
}

/*--------------------------------- push ----------------------------------- */
void push(unsigned int** tos, unsigned int value) {
    *tos = *tos - 1;
    **tos = value;
}