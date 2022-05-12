/*------------------------------ scheduler.h ----------------------------------

    Header file for scheduler.c
    scheduler.c implements a LIFO ready queue and blocked queue.

    Functions:
        init_queues - initialiezes ready queue and blocked queue.
        alloc_node - allocates a node for the queue.
        free_node - deallocates a node.
        dequeue_process - removes the process at the front of the queue.
        enqueue_process - adds a process to the end of the queue.
    
    Author: Robert McKay
    Since: 11/26/2021

-----------------------------------------------------------------------------*/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_PROCESSES 10
#define NULL 0

#include "process.h"

/* structure for a queue node */
struct node_s {
    pcb_t* pcb;
    struct node_s* next;
};
typedef struct node_s node_t;

/* structure for a queue */
struct queue_s {
    node_t *head;
    node_t *tail;
};
typedef struct queue_s queue_t;

/* make queues visible to other files */
extern queue_t ready_queue;
extern queue_t blocked_queue;

/*------------------------------ init_queue -----------------------------------
    Initializes the queues. Sets all nodes to null.
-----------------------------------------------------------------------------*/
void init_queues();

/*------------------------------ alloc_node -----------------------------------
    Allocates a new node for the queue.

    Returns: a pointer to the new node.
-----------------------------------------------------------------------------*/
node_t* alloc_node();

/*------------------------------ alloc_node -----------------------------------
    Deallocates a node from the queue.
-----------------------------------------------------------------------------*/
void free_node();

/*-------------------------- enqueue_process ----------------------------------
    Adds a process to the end of the queue.

    Parameters:
        queue - the queue to enqueue into.
        pcb - the pcb of the process to add.
-----------------------------------------------------------------------------*/
void enqueue_process(queue_t *queue, pcb_t* pcb);

/*-------------------------- dequeue_process ----------------------------------
    Removes a process from the queue. Sets global variable current_process.

    Parameters:
        queue - the queue to dequeue from.

    Returns: a pointer (as unsigned int) to the processes top of stack.
-----------------------------------------------------------------------------*/
pcb_t* dequeue_process(queue_t *queue);

#endif