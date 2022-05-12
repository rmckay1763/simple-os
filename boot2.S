/*---------------------------------- boot2.S ----------------------------------

    Contains function definitions for implementing a primitive os.
    Supports writing to video memory and a basic idt.

    Macros:
        call_kbd_handler - calls external keyboard handler.
        print - calls external function to print to screen.
        enqueue - adds current process to the specified queue.
        dequeue - removes next process from the specified queue.
        save_state - saves state of current process.
        restore_state - restores state of dequeued process.
        EOI - sends end of interrupt signal to PIC.

    Functions:
        k_print - moves a given string to video memory.
        k_scroll - scrolls video memory up by one row.
        kbd_enter - keyboard interrupt handler.
        default_handler - default interrupt handler.
        lidtr - loads the idt.
        init_timer_dev - initializes the timer interval.
        outportb - outputs given byte to specified port.
        go - dequeues the next process and jumps to it.
        dispatch - enqueues the current process and calls go.
        kbd_block - blocks a process waiting on keyboard input.
        
    Author: Robert McKay (except for k_scroll)
    Since: 11/26/2021

-----------------------------------------------------------------------------*/

.intel_syntax noprefix

/* global functions needed by c files */
.global k_print
.global k_scroll
.global kbd_enter
.global default_handler
.global lidtr
.global outportb
.global go
.global dispatch
.global kbd_block
.global init_timer_dev

/* external functions from c files */
.extern kbd_handler                 /* worker function for keyboard handler */
.extern println                     /* prints a char array to the screen */
.extern new_line                    /* advances one row in video memory */
.extern dequeue_process             /* remove next process from the queue */
.extern enqueue_process             /* add current process to queue */

/* external variables from scheduler.c */
.extern current_process             /* pointer to pcb of current process */
.extern ready_queue                 /* the process ready queue */
.extern blocked_queue               /* the process blocked queue */

/* label to reference the max offset for video memory */
max_offset:         .int 0xB8000 + 2 * (24 * 80 + 79)

/* message for default interrupt handler */
default_message:    .asciz "Default handler triggered"

/*------------------------------ call_kbd_handler -----------------------------
    macro: calls external function kbd_handler in kbd.c
    parameters:
        scancode - the scan code from the keyboard
-----------------------------------------------------------------------------*/
.macro call_kbd_handler scancode
    push    \scancode               /* pass scancode to kbd_handler */
    call    kbd_handler             /* call kbd_handler */
    add     esp, 4                  /* clean up stack */
.endm

/*---------------------------------- print ------------------------------------
    macro: calls external functions println followed by new_line in io.c
    parameters:
        message - char array to print
-----------------------------------------------------------------------------*/
.macro print message
    push    OFFSET \message         /* parameter for println */
    call    println                 /* call external function println */
    add     esp, 4                  /* clean up stack */
    call    new_line                /* print new line */
.endm

/*--------------------------------- enqueue -----------------------------------
    macro: calls external function enqueue_process from scheduler.c
    parameters:
        queue - the queue to enqueue into
-----------------------------------------------------------------------------*/

.macro enqueue queue
    mov     eax, [current_process]  /* dereference current pcb */
    mov     [eax], esp              /* save current's esp pointer */
    push    eax                     /* 2nd parameter (pcb to enqueue) */
    push    OFFSET \queue           /* 1st parameter (the queue to use) */
    call    enqueue_process         /* call external function */
    add     esp, 8                  /* clean up stack */
.endm

/*--------------------------------- dequeue -----------------------------------
    macro: calls external function dequeue_process from scheduler.c
    parameters:
        queue - the queue to dequeue from
-----------------------------------------------------------------------------*/
.macro dequeue queue
    push    OFFSET \queue           /* 1st parameter (the queue to use) */
    call    dequeue_process         /* call external function */
    add     esp, 4                  /* clean up stack */
    mov     current_process, eax    /* update current pcb */
.endm

/*-------------------------------- save_state ---------------------------------
    macro: saves state of current process
-----------------------------------------------------------------------------*/
.macro save_state
    pushad                          /* save general purpose registers */
    push    ds                      /* save ds */
    push    es                      /* save es */
    push    fs                      /* save fs */
    push    gs                      /* save gs */
.endm

/*------------------------------- restore_state -------------------------------
    macro: restores state of dequeued process
-----------------------------------------------------------------------------*/
.macro restore_state
    mov     eax, [current_process]  /* dereference pointer to current pcb */
    mov     esp, [eax]              /* set current processes esp */
    pop     gs                      /* restore gs */
    pop     fs                      /* restore fs */
    pop     es                      /* restore es */
    pop     ds                      /* restore ds */
    popad                           /* restore general purpose registers */
.endm

/*----------------------------------- EOI -------------------------------------
    macro: sends EOI signal to PIC
-----------------------------------------------------------------------------*/
.macro EOI
    push    eax                     /* save eax */
    mov     al, 0x20                /* EOI signal */
    out     0x20, al                /* signal PIC */
    pop     eax                     /* restore eax */
.endm

/*---------------------------------- k_print ----------------------------------
    Moves a given string to video memory.

    paremeter 1: address of string to print
    paremeter 2: length of string to print
    parameter 3: column of video memory
    paremeter 4: row of video memory
-----------------------------------------------------------------------------*/
k_print:
    push    ebp                     /* save ebp */
    mov     ebp, esp                /* get reference to stack */
    pushad                          /* save registers */

    /* retrieve parameters from stack */
    mov     esi, [ebp + 8]          /* starting address of string */
    mov     ecx, [ebp + 12]         /* length of string */
    mov     ebx, [ebp + 16]         /* column */
    mov     eax, [ebp + 20]         /* row */

    /* check length of string */
    jcxz    DONE                    /* exit if length is zero */
    
    /* calculate video memory offset */
    mov     edx, 80                 /* prepare to multiple row by 80 */
    mul     edx                     /* row * 80 */
    add     eax, ebx                /* row * 80 + col */
    add     eax, eax                /* (row * 80 + col) * 2 */
    mov     edi, 0xB8000            /* start of video memory */
    add     edi, eax                /* add offset to start of video memory */

L1:
    /* loop to move string to video memory */
    cmp     edi, [max_offset]       /* check edi is in video memory range */
    jnle    DONE                    /* exit if edi is not in range */
    movsb                           /* move string byte to video memory */
    movb    es:[edi], 31            /* move color byte to video memory */
    inc     edi                     /* point to next address in video memory */
    loop    L1                      /* loop. string length is in ecx */

DONE:
    /* exit code */
    popad                           /* restore registers */
    pop     ebp                     /* restore ebp */
    ret                             /* return */

/*---------------------------------- k_scroll ---------------------------------
    Scrolls the bytes in video memory up one row.
    Provided from ilearn instructions
-----------------------------------------------------------------------------*/
k_scroll:
    pushad
    pushf
    mov esi, 80* 2 + 0xb8000     
    mov edi, 0xb8000
    mov ecx, 80 * 24 * 2
    rep movsb
    mov ecx, 80
    mov al, ' '
    mov ah, 31
    rep stosw
    popf
    popad
    ret

/*-------------------------------- kbd_enter ----------------------------------
    Keyboard interrupt handler.
-----------------------------------------------------------------------------*/
kbd_enter:
    /* entry code */
    pushad                          /* save registers */
    cli                             /* clear interrupt flag */

    /* get scan code if available */
    in      al, 0x64                /* read keyboard status */
    and     al, 0x01                /* check if key available */
    jz      kbd_skip                /* exit if not key available */
    in      al, 0x60                /* read scan code */
    movzx   ebx, al                 /* move scan code to ebx */

    /* call handler in keyboard.c */
    call_kbd_handler ebx

kbd_skip:
    /* exit code */
    EOI                             /* send EOI to PIC */
    popad                           /* restore registers */
    iret                            /* return */

/*----------------------------- default_handler -------------------------------
    Default interrupt handler [assigned to 0-31 in idt].

    paremeter 1: address of char array with message to print
-----------------------------------------------------------------------------*/
default_handler:
    /* entry code */
    pushad                          /* save registers */
    cli                             /* clear interrupt flag */

    /* print default interrupt message */
    print default_message

    /* exit code */
    EOI                             /* send EOI to PIC */
    popad                           /* restore registers */
    iret                            /* return */

/*----------------------------------- lidtr -----------------------------------
    Loads the idt.

    paremeter 1: address of struct with limit and idt address
-----------------------------------------------------------------------------*/
lidtr:
    /* entry code */
    push    ebp                     /* save ebp */
    mov     ebp, esp                /* get reference to stack */
    pushad                          /* save registers */

    /* load idt */
    mov     eax, [ebp + 8]          /* get address of idtr */
    lidt    [eax]                   /* load idt */

    /* exit code */
    popad                           /* restore registers */
    pop     ebp                     /* restore ebp */
    ret                             /* return */

/*---------------------------- init_timer_dev ---------------------------------
    Initialize the timer interval device.

    Parameter 1: interval in milli seconds.
-----------------------------------------------------------------------------*/
init_timer_dev:
    /* entry code */
    push    ebp                     /* save ebp */
    mov     ebp, esp                /* get reference to stack */
    pushad                          /* save registers */

    /* get interval passed in and adjust for processor frequency */
    mov     eax, [ebp + 8]          /* get interval from stack */
    mov     dx, 1193                /* prepare to multiple by frequency (1193) */
    mul     dx                      /* ax now has correct interval */
    mov     dx, ax                  /* store interval in dx (need al free) */

    /* signal PIC to set up timer */
    mov     al, 0b00110110          /* command word to initialize counter 0 */
    out     0x43, al                /* signal PIC */
    mov     ax, dx                  /* move interval to ax */
    out     0x40, al                /* load LSB interval */
    xchg    ah, al                  /* move MSB of interval to al */
    out     0x40, al                /* load MSB of interval */

    /* exit code */
    popad                           /* restore general purpose registers */
    pop     ebp                     /* restore ebp */
    ret                             /* return */

/*-------------------------------- outportb -----------------------------------
    Outport a given byte to the specified port.

    parameter 1: the port number to outport to
    parameter 2: the byte to output to the port
-----------------------------------------------------------------------------*/
outportb:
    /* entry code */
    push    ebp                     /* save ebp */
    mov     ebp, esp                /* get reference to stack */
    pushad                          /* save registers */

    /* retrieve parameters from stack */
    mov     edx, [ebp + 8]           /* port address */
    mov     eax, [ebp + 12]          /* byte to output */

    /* write byte to port */
    out     dx, al 

    /* exit code */
    popad                           /* restore registers */
    pop     ebp                     /* restore ebp */
    ret                             /* return */

/*----------------------------------- go --------------------------------------
    Dequeue the next process, restore its state, and jump to it.
-----------------------------------------------------------------------------*/
go:
    /* dequeue the next process from the ready queue and restore its state */
    dequeue ready_queue             /* dequeue next process*/
    restore_state                   /* restore process state */

    /* send EOI signal to PIC  */
    EOI                             /* send EOI to PIC */
    iret                            /* jump to process */

/*------------------------------- dispatch ------------------------------------
    Save state and enqueue current process, call go.
-----------------------------------------------------------------------------*/
dispatch:
    /* save state of current process and add to ready queue */
    save_state                      /* save process state */
    enqueue ready_queue             /* add current process to ready queue */
    call    go                      /* jump to next process */

/*------------------------------- kbd_block -----------------------------------
    Blocks a process wating on keyboard input.
-----------------------------------------------------------------------------*/
kbd_block:
    /* mimic interrupt */
    pushf                           /* save eflags */
    push    cs                      /* save cs */
    push    OFFSET _afterSwitch     /* return address */

    /* add current to blocked queue and dequeue from ready queue */
    save_state                      /* save process state */
    enqueue blocked_queue           /* add process to blocked queue */
    dequeue ready_queue             /* dequeue pcb from ready queue */
    restore_state                   /* restore dequeued process state */
    iret                            /* mimic interrupt return */

_afterSwitch:
    ret                             /* return to caller (k_getchar) */