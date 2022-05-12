/*------------------------------------ io.h -----------------------------------

    Header file for io.c
    io.c provides procedures for writing to video memory.

    Functions:
        init_screen - initialize the screen.
        clearscr - clears the screen and set the screen color to blue.
        println - prints a string to the screen by calling k_print.
        convert_num_h - helper function for convert num.
        convert_num - converts integer to ascii representation.
        string_size - determines the length of a string given a char pointer.
        new_line - move to the next line of video memory.
        backspace - deletes the last char sent to the screen.
        tab_over - implements tab key

    Author: Robert McKay (except for convert_num, convert_num_h)
    Since: 11/26/2021

-----------------------------------------------------------------------------*/

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

/* row variables needed by driver.c */
extern int start_row;
extern int current_row;

/* ------------------------------ init_screen ---------------------------------
    Initialze the screen for I/O.
-----------------------------------------------------------------------------*/
void init_screen();

/* ------------------------------- clearscr -----------------------------------
    Clears the screen by calling k_print with whitespace as the argument.
-----------------------------------------------------------------------------*/
void clearscr();

/* ------------------------------- println ------------------------------------
    Prints a string of text to the current row in video memory.

    Paremeters:
        text - the text to to print.
-----------------------------------------------------------------------------*/
void println(char* text);

/* ----------------------------- convert_num ----------------------------------
    Converts an integer to a ascii string.

    Paremeters:
        num - the integer to convert.
        buf - string to store result.
-----------------------------------------------------------------------------*/
void convert_num(unsigned int num, char buf[]);

/* ---------------------------- convert_num_h ---------------------------------
    Helper function for convert_num.

    Paremeters:
        num - the integer to convert.
        buf - string to store result.
    Returns: The index in the string for the current digit
-----------------------------------------------------------------------------*/
int convert_num_h(unsigned int num, char buf[]);

/* ------------------------------ string_size ---------------------------------
    Calculates the length of a string given a char pointer.

    Parameters:
        ptr - pointer to the string.
    Returns: the length of the string.
-----------------------------------------------------------------------------*/
int string_size(char* ptr);

/* ------------------------------- new_line -----------------------------------
    Moves to the next line of video memory.
-----------------------------------------------------------------------------*/
void new_line();

/* ------------------------------- backspace ----------------------------------
    Deletes the last char output to the screen.
-----------------------------------------------------------------------------*/
void backspace();

/*------------------------------- tab_over ------------------------------------
    Implements tab key.
-----------------------------------------------------------------------------*/
void tab_over();

#endif