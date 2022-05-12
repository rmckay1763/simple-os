/*--------------------------------- driver.c ----------------------------------

    Implements a primitive OS with a simple IDT.
    Screen I/O implementd in io.c
    IDT implemented in idt.c
    Keyboard interrupt handler implemented in keyboard.c
    Process support implemented in process.c
    Process scheduling implemented in scheduler.c

    See header files for more details.

    Author: Robert McKay
    Since: 11/26/2021
    
-----------------------------------------------------------------------------*/

#include "driver.h"
#include "boot2.h"
#include "io.h"
#include "idt.h"
#include "keyboard.h"
#include "buffer.h"
#include "process.h"
#include "scheduler.h"

/*----------------------------- entry point ---------------------------------*/
int main() {
    
    /* local variables */
    int retval;
    int num_processes = 7; // controls how many processes get created
    char init[] = "initializing processes...";
    char running[] = "running processes...";
    char failure[] = "failed to create process";
    char success[] = "process created";
    unsigned int processes[] = {(unsigned int)p_idle, (unsigned int)p_keyboard,
                                (unsigned int)p1, (unsigned int)p2, (unsigned int)p3, 
                                (unsigned int)p4, (unsigned int)p5};

    /* initialzation */
    init_screen();
    initIDT();
    setupPIC();
    init_timer_dev(10);
    init_queues();
    println(init);
    new_line();

    /* create processes */
    for (int i = 0; i < num_processes; i++) {
        if (create_process(processes[i]) == EXIT_SUCCESS) {
            println(success);
        } else {
            println(failure);
        }
        new_line();
    }

    /* start processes */
    new_line();
    println(running);
    new_line();
    start_row = current_row + num_processes - 2; // set row for keyboard io
    go();
}

/* -------------------------------- p_idle --------------------------------- */
void p_idle() {
    asm volatile ("sti");
    while (TRUE);
}

/* ------------------------------ p_keyboard ------------------------------- */
void p_keyboard() {
    char value;
    char end = NULL_TERMINATOR;
    while(TRUE) {
        value = dequeue_char();
        if (value == NEWLINE) {
            new_line();
        } else if (value == BACKSPACE) {
            backspace();
        } else if (value == TAB) {
            tab_over();
        } else {
            println(&value);
        }
    }
}

/* ---------------------------------- p1 ----------------------------------- */
void p1() {
    unsigned int count = 0;
    char message[] = "process 1: ";
    int row = current_row; // current_row defined in io.c
    int column = string_size(message) + 2;
    char count_buf[5];
    println(message);
    new_line();
    while(TRUE) {
        convert_num(count % 500, count_buf);
        k_print(count_buf, string_size(count_buf), column, row);
        count++;
    }
}

/* ---------------------------------- p2 ----------------------------------- */
void p2() {
    unsigned int count = 0;
    char message[] = "process 2: ";
    int row = current_row; // current_row defined in io.c
    int column = string_size(message) + 2;
    char count_buf[5];
    println(message);
    new_line();
    while(TRUE) {
        convert_num(count % 500, count_buf);
        k_print(count_buf, string_size(count_buf), column, row);
        count++;
    }
}

/* ---------------------------------- p3 ----------------------------------- */
void p3() {
    unsigned int count = 0;
    char message[] = "process 3: ";
    int row = current_row; // current_row defined in io.c
    int column = string_size(message) + 2;
    char count_buf[5];
    println(message);
    new_line();
    while(TRUE) {
        convert_num(count % 500, count_buf);
        k_print(count_buf, string_size(count_buf), column, row);
        count++;
    }
}

/* ---------------------------------- p4 ----------------------------------- */
void p4() {
    unsigned int count = 0;
    char message[] = "process 4: ";
    int row = current_row; // current_row defined in io.c
    int column = string_size(message) + 2;
    char count_buf[5];
    println(message);
    new_line();
    while(TRUE) {
        convert_num(count % 500, count_buf);
        k_print(count_buf, string_size(count_buf), column, row);
        count++;
    }
}

/* ---------------------------------- p5 ----------------------------------- */
void p5() {
    unsigned int count = 0;
    char message[] = "process 5: ";
    int row = current_row; // current_row defined in io.c
    int column = string_size(message) + 2;
    char count_buf[5];
    println(message);
    new_line();
    while(TRUE) {
        convert_num(count % 500, count_buf);
        k_print(count_buf, string_size(count_buf), column, row);
        count++;
    }
}