/**
 * @file buffer.h
 * @brief Implements a circular buffer for keyboard input.
 * @author Robert McKay
 * @version 0.1
 * @date 2022-05-12
 * 
 */

#ifndef BUFFER_H
#define BUFFER_H

/* global constants */
#define BUFFER_SIZE 10
#define TRUE 1
#define FALSE 0
#define EMPTY -1

/**
 * @brief Enqueues a char to the keyboard buffer.
 * 
 * @param value the char to add to the buffer.
 * @return int 1 (TRUE) if char added to buffer, 0 (FALSE) otherwise.
 */
int enqueue_char(char value);

/**
 * @brief Dequeues a char from the keyboard buffer.
 * 
 * @return char the element in the front of the buffer or 0 if buffer empty.
 */
char dequeue_char();

/**
 * @brief Checks if the buffer is empty.
 * 
 * @return 1 (TRUE) if the buffer is empty, 0 (FALSE) otherwise.
 */
int is_empty();

/**
 * @brief Checks if the buffer is full.
 * 
 * @return int 1 (TRUE) if the buffer is full, 0 (FALSE) otherwise.
 */
int is_full();

#endif