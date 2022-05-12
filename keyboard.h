/*--------------------------------- keyboard.h --------------------------------

    Header file for keyboard.c
    keyboard.c implements a keyboard interupt handler.

    Functions:
        kbd_handler - handles keyboard interrupts.
        tranlsate_char - translates scancode to char.
        translate_char_normal - translates scancode if shift key not active.
        translate_char_shift - translate scancode if shift key is active.

    Author: Robert McKay
    Since: 10/25/2021

-----------------------------------------------------------------------------*/

#ifndef KEYBOARD_H
#define KEYBOARD_H

/* constants for ascii codes */
#define SPACE 0x20
#define NEWLINE 0xa
#define BACKSPACE 0x7f
#define BACKTICK 0x27
#define TILDE 0x7e
#define BACKSLASH 0x5c
#define PIPE 0x7c
#define LOWER_A 0x61
#define UPPER_A 0x42
#define LOWER_Z 0x7a
#define UPPER_Z 0x5a
#define TAB 0x09
#define LOWERCASE_OFFSET 0x20

/* constants for individual scan codes */
#define NEWLINE_PRESSED 0x1c
#define SPACE_PRESSED 0x39
#define BACKSPACE_PRESSED 0x0e
#define BACKTICK_PRESSED 0x29
#define BACKSLASH_PRESSED 0x2b
#define LEFT_SHIFT_PRESSED 0x2a
#define RIGHT_SHIFT_PRESSED 0x36
#define LEFT_SHIFT_RELEASED 0xaa
#define RIGHT_SHIFT_RELEASED 0xb6
#define CAPS_LOCK_PRESSED 0x3a
#define TAB_PRESSED 0x0f

/* constants for ranges of scan codes */
#define NUMBER_ROW_START 0x02
#define NUMBER_ROW_END 0x0d
#define Q_ROW_START 0x10
#define Q_ROW_END 0x1b
#define A_ROW_START 0x1e
#define A_ROW_END 0x28
#define Z_ROW_START 0x2c
#define Z_ROW_END 0x35

/*------------------------------- kbd_handler ---------------------------------
    Handles keyboard interrupts.
-----------------------------------------------------------------------------*/
void kbd_handler(unsigned int scancode);

/*---------------------------- translate_scancode -----------------------------
    Translates given scancode to corresponding character.
    Calls helper function depending on state of shift key.

    Paremeters:
        scancode - the scancode to translate.

    Returns: the char associated with the scancode.
-----------------------------------------------------------------------------*/
char translate_scancode(unsigned int scancode);

/*------------------------ translate_scancode_normal --------------------------
    Translates scancode given shift key not active.

    Paremeters:
        scancode - the scancode to translate.

    Returns: the char associated with the scancode.
-----------------------------------------------------------------------------*/
char translate_scancode_normal(unsigned int scancode);

/*------------------------ translate_scancode_shift ---------------------------
    Translates scancode given shift key is active.

    Paremeters:
        scancode - the scancode to translate.

    Returns: the char associated with the scancode.
-----------------------------------------------------------------------------*/
char translate_scancode_shift(unsigned int scancode);

#endif