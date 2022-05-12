/*------------------------------ scheduler.c ----------------------------------

    Implements a process ready queue and a process blocked queue.

    Author: Robert McKay
    Since: 11/26/2021

-----------------------------------------------------------------------------*/

#include "scheduler.h"

/* structures for queue */
node_t nodes[MAX_PROCESSES];
queue_t ready_queue;
queue_t blocked_queue;

/* global variable for current process */
pcb_t current_process;

/*------------------------------ init_queue -------------------------------- */
void init_queues() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        nodes[i].pcb = NULL;
        nodes[i].next = NULL;
    }
    ready_queue.head = NULL;
    ready_queue.tail = NULL;
    blocked_queue.head = NULL;
    blocked_queue.tail = NULL;
}

/*------------------------------ alloc_node -------------------------------- */
node_t* alloc_node() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (nodes[i].pcb == NULL) {
            nodes[i].next = NULL;
            return &nodes[i];
        }
    }
    return NULL;
}

/*------------------------------- free_node -------------------------------- */
void free_node(node_t *node) {
    node->pcb = NULL;
    node->next = NULL;
}

/*--------------------------- enqueue_process ------------------------------ */
void enqueue_process(queue_t *queue, pcb_t *pcb) {
    node_t* new_node = alloc_node();
    if (new_node == NULL) {
        return;
    }
    new_node->pcb = pcb;
    if (queue->tail == NULL) {
        queue->head = new_node;
        queue->tail = new_node;
        return;
    }
    queue->tail->next = new_node;
    queue->tail = new_node;
}

/*--------------------------- dequeue_process ------------------------------ */
pcb_t* dequeue_process(queue_t *queue) {
    if (queue->head == NULL)
    {
        return NULL;
    }
    node_t *temp = queue->head;
    pcb_t *pcb = temp->pcb;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    free_node(temp);
    return pcb;
}