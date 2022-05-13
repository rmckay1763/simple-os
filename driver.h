/**
 * @file driver.h
 * @author Robert McKay
 * @brief Implements a primitive os with process support and basic i/o. 
 * @version 0.1
 * @date 2022-05-12
 * 
 */

#ifndef DRIVER_H
#define DRIVER_H

/**
 * @brief First process added to queue. Enables interrupts.
 * 
 */
void p_idle();

/**
 * @brief Process for keyboard i/o.
 * 
 */
void p_keyboard();

/**
 * @brief Example process.
 * 
 */
void p1();

/**
 * @brief Example process.
 * 
 */
void p2();

/**
 * @brief Example process.
 * 
 */
void p3();

/**
 * @brief Example process.
 * 
 */
void p4();

/**
 * @brief Example process.
 * 
 */
void p5();

#endif