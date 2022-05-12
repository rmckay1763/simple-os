/*---------------------------------- buffer.h ---------------------------------

    Header file for buffer.c
    buffer.c implements a circular buffer for keyboard input.

    Functions:
        enqueue_char - enqueues a char to the buffer.
        dequeue_char - dequeues a char form the buffer.
        is_empty - check if the buffer is empty.
        is_full - check if the buffer is full.

    Author: Robert McKay
    Since: 10/25/2021

-----------------------------------------------------------------------------*/

#ifndef BUFFER_H
#define BUFFER_H

/* global constants */
#define BUFFER_SIZE 10
#define TRUE 1
#define FALSE 0
#define EMPTY -1

/*------------------------------- enqueue_char --------------------------------
    Enqueues a char to the keyboard buffer.

    Paremeters:
        value - the char to add to the buffer.

    Returns: 1 (TRUE) if char added to buffer, 0 (FALSE) otherwise.
-----------------------------------------------------------------------------*/
int enqueue_char(char value);

/*------------------------------- dequeue_char --------------------------------
    Dequeues a char from the keyboard buffer.

    Returns: the char in the front of the buffer or 0 if buffer empty.
-----------------------------------------------------------------------------*/
char dequeue_char();

/*-------------------------------- is_empty -----------------------------------
    Checks if the buffer is empty.

    Returns: 1 (TRUE) if the buffer is empty, 0 (FALSE) otherwise.
-----------------------------------------------------------------------------*/
int is_empty();

/*--------------------------------- is_full -----------------------------------
    Checks if the buffer is full.

    Returns: 1 (TRUE) if the buffer is full, 0 (FALSE) otherwise.
-----------------------------------------------------------------------------*/
int is_full();

#endif