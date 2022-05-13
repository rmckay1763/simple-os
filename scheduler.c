/**
 * @file scheduler.c
 * @author Robert McKay
 * @brief Implements a LIFO queue for process scheduling.
 * @version 0.1
 * @date 2022-05-12
 * 
 */

#include "scheduler.h"

/**
 * @brief Array of nodes to allocate to the queues.
 * 
 */
node_t nodes[MAX_PROCESSES];

/**
 * @brief Stores reference to the pcb of the current process.
 * The process dispatcher in boot2.S needs this to save/restore state.
 * 
 */
pcb_t current_process;

queue_t ready_queue;
queue_t blocked_queue;

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

node_t* alloc_node() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (nodes[i].pcb == NULL) {
            nodes[i].next = NULL;
            return &nodes[i];
        }
    }
    return NULL;
}

void free_node(node_t *node) {
    node->pcb = NULL;
    node->next = NULL;
}

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