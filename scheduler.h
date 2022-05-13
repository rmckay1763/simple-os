/**
 * @file scheduler.h
 * @author Robert McKay
 * @brief Implements a LIFO queue for process scheduling.
 * @version 0.1
 * @date 2022-05-12
 * 
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_PROCESSES 10
#define NULL 0

#include "process.h"

/**
 * @brief Structure for a queue node.
 * 
 */
struct node_s {
    pcb_t* pcb;
    struct node_s* next;
};

/**
 * @brief Type definitions for a queue node.
 * 
 */
typedef struct node_s node_t;

/**
 * @brief Structure for a queue
 * 
 */
struct queue_s {
    node_t *head;
    node_t *tail;
};

/**
 * @brief Type definition for a queue.
 * 
 */
typedef struct queue_s queue_t;

/**
 * @brief Queue for processes ready to execute.
 * 
 */
extern queue_t ready_queue;

/**
 * @brief Queue for processes in blocked state.
 * 
 */
extern queue_t blocked_queue;

/**
 * @brief Initializes the ready/blocked queues. Sets all nodes to null.
 * 
 */
void init_queues();

/**
 * @brief Allocates a new node for the queue.
 * 
 * @return node_t* Pointer to the new node.
 */
node_t* alloc_node();

/**
 * @brief Deallocates a node from the queue.
 * 
 */
void free_node();

/**
 * @brief Adds a process to the end of the queue.
 * 
 * @param queue The queue to enqueue into.
 * @param pcb The pcb of the process to enqueue.
 */
void enqueue_process(queue_t *queue, pcb_t* pcb);

/*-------------------------- dequeue_process ----------------------------------
    Removes a process from the queue. Sets global variable current_process.

    Parameters:
        queue - the queue to dequeue from.

    Returns: a pointer (as unsigned int) to the processes top of stack.
-----------------------------------------------------------------------------*/

/**
 * @brief Removes a process from a queue.
 * 
 * @param queue The queue to dequeue from.
 * @return pcb_t* Pointer to the PCB of the dequeued process.
 */
pcb_t* dequeue_process(queue_t *queue);

#endif