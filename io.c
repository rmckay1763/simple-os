/*----------------------------------- io.c ------------------------------------
    Implements functions to write to video memory.
    External functions defined in boot2.S
    See header file for more details.

    Author: Robert McKay (convert_num, convert_num_h)
    Since: 11/26/2021
-----------------------------------------------------------------------------*/

#include "io.h"
#include "boot2.h"

/* global variables for screen I/O */
int start_row;
int current_row;
int current_column;
int row_tails[NUM_ROWS];
char tab[TAB_SIZE + 1];
char space = WHITESPACE;
char end = NULL_TERMINATOR;

/*------------------------------ init_screen --------------------------------*/
void init_screen() {
    start_row = 0;
    current_row = 0;
    current_column = 0;
    for (int i = 0; i < NUM_ROWS; i++) {
        row_tails[i] = MAX_COL;
    }
    for (int i = 0; i < TAB_SIZE; i++) {
        tab[i] = WHITESPACE;
    }
    tab[TAB_SIZE] = NULL_TERMINATOR;
    clearscr();
}

/*--------------------------------- clearscr --------------------------------*/
void clearscr() {
    int length = NUM_COLS * NUM_ROWS;
    char whitespace[length];
    for (int i = 0; i < length; i++) {
        whitespace[i] = WHITESPACE;
    }
    k_print(whitespace, length, 0, 0);
    current_row = 0;
    current_column = 0;
}

/*-------------------------------- println ----------------------------------*/
void println(char* text) {
    if (current_row > MAX_ROW) {
        k_scroll();
        current_row = MAX_ROW;
    }
    int num_to_print = string_size(text);
    k_print(text, num_to_print, current_column, current_row);
    current_row += (current_column + num_to_print) / NUM_COLS;
    current_column = (current_column + num_to_print) % NUM_COLS;
}

/*------------------------------ convert_num --------------------------------*/
void convert_num(unsigned int num, char buf[]) {
    if (num == 0) {
        buf[0] = '0';
        buf[1] = NULL_TERMINATOR;
    } else {
        convert_num_h(num, buf);
    }
}

/*----------------------------- convert_num_h -------------------------------*/
int convert_num_h(unsigned int num, char buf[]) {
    if (num == 0) {
        return 0;
    }
    int idx = convert_num_h(num / 10, buf);
    buf[idx] = num % 10 + '0';
    buf[idx + 1] = NULL_TERMINATOR;
    return idx + 1;
}

/*------------------------------- string_size -------------------------------*/
int string_size(char* ptr) {
    int length = 0;
    while (*(ptr + length) != NULL_TERMINATOR) {
        length++;
    }
    return length;
}

/*-------------------------------- new_line ---------------------------------*/
void new_line() {
    row_tails[current_row] = current_column;
    current_column = 0;
    current_row++;
}

/*------------------------------- backspace ---------------------------------*/
void backspace() {
    if (current_row == start_row && current_column == 0) {
        return;
    }
    if (current_column == 0) {
        current_row--;
        current_column = row_tails[current_row];
        row_tails[current_row] = MAX_COL;
    } else {
        current_column--;
    }
    println(&space);
    current_column--;
}

/*------------------------------- tab_over ----------------------------------*/
void tab_over() {
    if (MAX_COL - current_column <= TAB_SIZE) {
        new_line();
        return;
    }
    println(tab);
}