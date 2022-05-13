/**
 * @file keyboard.h
 * @author Robert McKay
 * @brief Implements a keyboard interupt handler.
 * @version 0.1
 * @date 2022-05-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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

/**
 * @brief Handles keyboard interrupts.
 * 
 * @param scancode The scancode generated from user input.
 */
void kbd_handler(unsigned int scancode);

/**
 * @brief Translates given scancode to corresponding character.
 * 
 * @param scancode The scancode to translate.
 * @return char The char associated with the scancode.
 */
char translate_scancode(unsigned int scancode);

/**
 * @brief Translates scancode given shift key not active.
 * 
 * @param scancode The scancode to translate.
 * @return char The char associated with the scancode.
 */
char translate_scancode_normal(unsigned int scancode);

/**
 * @brief Translates scancode given shift key is active.
 * 
 * @param scancode The scancode to translate.
 * @return char The char associated with the scancode.
 */
char translate_scancode_shift(unsigned int scancode);

#endif