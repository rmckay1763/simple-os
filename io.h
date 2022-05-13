/**
 * @file io.h
 * @author Robert McKay
 * @brief Declares procedures for writing to video memory.
 * @version 0.1
 * @date 2022-05-12
 * 
 */

#ifndef IO_H
#define IO_H

/* global constants */
#define NUM_ROWS 25
#define NUM_COLS 80
#define MAX_ROW NUM_ROWS - 1
#define MAX_COL NUM_COLS - 1
#define TAB_SIZE 4
#define WHITESPACE 32
#define NULL_TERMINATOR 0

/**
 * @brief The starting row of video memory to use for keyboard output.
 * 
 */
extern int start_row;

/**
 * @brief The current row of video memory used for keyboard output.
 * 
 */
extern int current_row;

/**
 * @brief Initialze the screen for I/O.
 * 
 */
void init_screen();

/**
 * @brief Clears the screen by calling k_print with whitespace as the argument.
 * 
 */
void clearscr();

/**
 * @brief Prints a string of text to the current row in video memory.
 * 
 * @param text The text to to print.
 */
void println(char* text);

/**
 * @brief Converts an integer to a ascii string.
 * 
 * @param num The integer to convert.
 * @param buf String to store result.
 */
void convert_num(unsigned int num, char buf[]);

/**
 * @brief Helper function for convert_num.
 * 
 * @param num The integer to convert.
 * @param buf String to store result.
 * @return int The index in the string for the current digit.
 */
int convert_num_h(unsigned int num, char buf[]);

/**
 * @brief Computes the length of a string given a char pointer.
 * 
 * @param ptr Pointer to the string.
 * @return int The length of the string.
 */
int string_size(char* ptr);

/**
 * @brief Moves to the next line of video memory.
 * 
 */
void new_line();

/**
 * @brief Deletes the last char output to the screen.
 * 
 */
void backspace();

/**
 * @brief Implements tab key.
 * 
 */
void tab_over();

#endif