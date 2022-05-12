/*---------------------------------- buffer.c ---------------------------------

    Implements a circular buffer for keyboard input.

    Author: Robert McKay
    Since: 10/25/2021

-----------------------------------------------------------------------------*/

#include "buffer.h"
#include "scheduler.h"
#include "process.h"
#include "boot2.h"

/* global variables for keyboard buffer */
char kbd_buffer[BUFFER_SIZE];
int kbd_buf_head = EMPTY;
int kbd_buf_tail = EMPTY;

/*------------------------------- enqueue_char ------------------------------*/
int enqueue_char(char value) {
    if (is_full() == TRUE) {
        return FALSE;
    }
    if (kbd_buf_head == EMPTY) {
        kbd_buf_head = 0;
    }
    kbd_buf_tail = (kbd_buf_tail + 1) % BUFFER_SIZE;
    kbd_buffer[kbd_buf_tail] = value;
    return TRUE;
}

/*------------------------------- dequeue_char ------------------------------*/
char dequeue_char() {
    asm volatile ("cli");
    while (is_empty() == TRUE) {
        kbd_block();
    }
    char head = kbd_buffer[kbd_buf_head];
    if (kbd_buf_head == kbd_buf_tail) {
        kbd_buf_head = EMPTY;
        kbd_buf_tail = EMPTY;
    } else {
        kbd_buf_head = (kbd_buf_head + 1) % BUFFER_SIZE;
    }
    asm volatile ("sti");
    return head;
}

/*--------------------------------- is_empty --------------------------------*/
int is_empty() {
    if (kbd_buf_head == EMPTY) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*--------------------------------- is_full ---------------------------------*/
int is_full() {
    if (kbd_buf_head == kbd_buf_tail + 1) {
        return TRUE;
    }
    if (kbd_buf_head == 0 && kbd_buf_tail == BUFFER_SIZE - 1) {
        return TRUE;
    }
    return FALSE;
}