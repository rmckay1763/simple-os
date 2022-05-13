/**
 * @file keyboard.c
 * @author Robert McKay
 * @brief Implements a keyboard interupt handler.
 * @version 0.1
 * @date 2022-05-12
 * 
 */

#include "keyboard.h"
#include "buffer.h"
#include "scheduler.h"
#include "process.h"

/* constants for ranges of keys */

static const char NUMBER_ROW[] = "1234567890-=";
static const char Q_ROW[] = "qwertyuiop[]";
static const char A_ROW[] = "asdfghjkl;\'";
static const char Z_ROW[] = "zxcvbnm,./";
static const char NUMBER_ROW_SHIFT[] = "!@#$%^&*()_+";
static const char Q_ROW_SHIFT[] = "QWERTYUIOP{}";
static const char A_ROW_SHIFT[] = "ASDFGHJKL:\"";
static const char Z_ROW_SHIFT[] = "ZXCVBNM<>\?";

/* global variable to track state */

int shift_active = FALSE;
int caps_active = FALSE;

void kbd_handler(unsigned int scancode) {
    if (scancode == FALSE || is_full() == TRUE) {
        return;
    }
    char value = translate_scancode(scancode);
    if (value == FALSE) {
        return;
    }
    enqueue_char(value);
    if (blocked_queue.tail != NULL) {
        pcb_t* pcb = dequeue_process(&blocked_queue);
        enqueue_process(&ready_queue, pcb);
    }
}

char translate_scancode(unsigned int scancode) {

    /* check for a shift key event or caps lock event */
    if (scancode == LEFT_SHIFT_PRESSED || scancode == RIGHT_SHIFT_PRESSED) {
        shift_active = TRUE;
        return FALSE;
    }
    if (scancode == LEFT_SHIFT_RELEASED || scancode == RIGHT_SHIFT_RELEASED) {
        shift_active = FALSE;
        return FALSE;
    }
    if (scancode == CAPS_LOCK_PRESSED) {
        if (caps_active == FALSE) {
            caps_active = TRUE;
        }
        else {
            caps_active = FALSE;
        }
        return FALSE;
    }

    /* event is not from shift key or caps lock */
    char key;
    if (shift_active == TRUE) {
        key = translate_scancode_shift(scancode);
    } else {
        key = translate_scancode_normal(scancode);
    }

    /* adjust key if caps lock is active and key is a letter */
    if (caps_active == TRUE) {
        if (key >= LOWER_A && key <= LOWER_Z) {
            key -= LOWERCASE_OFFSET;
        }
        if (key >= UPPER_A && key <= UPPER_Z) {
            key += LOWERCASE_OFFSET;
        }
    }
    return key;
}

char translate_scancode_normal(unsigned int scancode) {

    /* number row: 1 through = (equals sign) */
    if (scancode >= NUMBER_ROW_START && scancode <= NUMBER_ROW_END) {
        return NUMBER_ROW[scancode - NUMBER_ROW_START];
    }

    /* q row: q through ] (closing bracket) */
    if (scancode >= Q_ROW_START && scancode <= Q_ROW_END){
        return Q_ROW[scancode - Q_ROW_START];
    }

    /* a row: a through ' (single quote) */
    if (scancode >= A_ROW_START && scancode <= A_ROW_END) {
        return A_ROW[scancode - A_ROW_START];
    }

    /* z row: z through / (foward slash) */
    if (scancode >= Z_ROW_START && scancode <= Z_ROW_END) {
        return Z_ROW[scancode - Z_ROW_START];
    }

    /* individual cases */
    switch (scancode) {
        case BACKTICK_PRESSED: return BACKTICK;
        case BACKSLASH_PRESSED: return BACKSLASH;
        case NEWLINE_PRESSED: return NEWLINE;
        case SPACE_PRESSED: return SPACE;
        case BACKSPACE_PRESSED: return BACKSPACE;
        case TAB_PRESSED: return TAB;
        default: return FALSE;
    }
}

char translate_scancode_shift(unsigned int scancode) {

    /* number row: 1 through + (plus sign) */
    if (scancode >= NUMBER_ROW_START && scancode <= NUMBER_ROW_END) {
        return NUMBER_ROW_SHIFT[scancode - NUMBER_ROW_START];
    }

    /* q row: q through ] (closing bracket) */
    if (scancode >= Q_ROW_START && scancode <= Q_ROW_END){
        return Q_ROW_SHIFT[scancode - Q_ROW_START];
    }

    /* a row: a through ' (single quote) */
    if (scancode >= A_ROW_START && scancode <= A_ROW_END) {
        return A_ROW_SHIFT[scancode - A_ROW_START];
    }

    /* z row: z through / (foward slash) */
    if (scancode >= Z_ROW_START && scancode <= Z_ROW_END) {
        return Z_ROW_SHIFT[scancode - Z_ROW_START];
    }

    /* individual cases */
    switch (scancode) {
        case BACKTICK_PRESSED: return TILDE;
        case BACKSLASH_PRESSED: return PIPE;
        case NEWLINE_PRESSED: return NEWLINE;
        case SPACE_PRESSED: return SPACE;
        case BACKSPACE_PRESSED: return BACKSPACE;
        case TAB_PRESSED: return TAB;
        default: return FALSE;
    }
}