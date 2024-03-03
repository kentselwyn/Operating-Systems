#include <8051.h>
#include "preemptive.h"

// Global variables for preemptive scheduling
__data __at (0x20) char thread_bitmap;
__data __at (0x21) ThreadID current_thread_id;
__data __at (0x22) char new_thread_id;
__data __at (0x23) char temp_SP;
__data __at (0x24) char saved_SP[4];
__data __at (0x28) char direction;
__data __at (0x3E) char thread_it;

#define SAVESTATE \
        __asm \
        PUSH ACC \
        PUSH B \
        PUSH DPL \
        PUSH DPH \
        PUSH PSW \
        __endasm; \
        saved_SP[current_thread_id] = SP; \

#define RESTORESTATE \
        SP = saved_SP[current_thread_id]; \
        __asm \
        POP PSW \
        POP DPH \
        POP DPL \
        POP B \
        POP ACC \
        __endasm; \

#define ROUND_ROBIN(label)

// Allow other sources to reference `main`
extern void main(void);

void Bootstrap(void)
{
    // Timer 0 Mode 1
    TMOD = 1;
    // Enable Timer 0 interrupt
    // IE   = {  EA |  -  | ET2 |  ES | ET1 | EX1 | ET0 | EX0 }
    // 0x82 = {  1  |  0  |  0  |  0  |  0  |  0  |  1  |  0  }
    IE = 0x82;
    // Start running the timer
    TR0 = 1;
    // Initialize global data structures
    thread_bitmap = 0x00;
    // Create a new thread for main
    current_thread_id = ThreadCreate(main);
    // Jump to main and start running
    RESTORESTATE;
}

ThreadID ThreadCreate(FunctionPtr fp)
{
    // [CRITICAL SECTION START] Disable interrupts
    EA = 0;
    // If reached maximum number threads
    if(thread_bitmap == 0x0F) {return -1;} // Invalid thread ID
    // Find available thread ID
    new_thread_id = 0;
    if     (!(thread_bitmap & 0x1)) {new_thread_id = 0;}
    else if(!(thread_bitmap & 0x2)) {new_thread_id = 1;}
    else if(!(thread_bitmap & 0x4)) {new_thread_id = 2;}
    else                            {new_thread_id = 3;}
    // [a] Update the bitmap
    thread_bitmap |= (1 << new_thread_id);
    // [b] Compute new stack location
    // [c] Save current SP into a temporary variable and set SP to the stack of the new thread
    temp_SP = SP;
    SP = (0x3F) + (0x10) * new_thread_id;
    // [d] Push starting address of fp (DPTR contains the function address) onto current stack
    __asm
        PUSH DPL
        PUSH DPH
    __endasm;
    // [e] Initialize registers to 0. Push four zeros into the new stack
    __asm
        CLR A
        PUSH ACC
        PUSH ACC
        PUSH ACC
        PUSH ACC
    __endasm;
    // [f] Push PSW with bits <4:3> initialize with register select bits
    PSW = (new_thread_id << 3);
    __asm
        PUSH PSW
    __endasm;
    // [g] Write the new stack pointer to the saved stack pointer array
    saved_SP[new_thread_id] = SP;
    // [h] Set SP to the original stack.
    SP = temp_SP;
    EA = 1;
    // [CRITICAL SECTION END] Reenable interrupts

    // [i] Return the new thread ID
    return new_thread_id;
}

// Exclusively only for local use in ThreadYield function
#define _yield_begin 00001$
#define _yield_try_thread3 00002$
#define _yield_try_thread0 00003$
#define _yield_try_thread1 00004$
#define _yield_try_thread2 00005$
#define _yield_end 00006$
void ThreadYield(void)
{
    // [CRITICAL SECTION START] Disable interrupts
    EA = 0;
    SAVESTATE;
    __asm
        _yield_begin:
            MOV A, _current_thread_id
            ADD A, _direction
            ANL A, #3
            
            JZ _yield_try_thread0
            DEC A
            JZ _yield_try_thread1
            DEC A
            JZ _yield_try_thread2

        _yield_try_thread3:
            MOV _current_thread_id, #3
            MOV A, _thread_bitmap
            ANL A, #8
            JNZ _yield_end
            JZ _yield_begin
        
        _yield_try_thread0:
            MOV _current_thread_id, #0
            XRL _direction, #0xFE
            MOV A, _thread_bitmap
            ANL A, #1
            JNZ _yield_end
            JZ _yield_begin

        _yield_try_thread1:
            MOV _current_thread_id, #1
            MOV A, _thread_bitmap
            ANL A, #2
            JNZ _yield_end
            JZ _yield_begin

        _yield_try_thread2:
            MOV _current_thread_id, #2
            MOV A, _thread_bitmap
            ANL A, #4
            JNZ _yield_end
            JZ _yield_begin
            
        _yield_end:
    __endasm;
    RESTORESTATE;
    EA = 1;
    // [CRITICAL SECTION END] Reenable interrupts
}

// Exclusively only for local use in ThreadExit function
#define _exit_thread0 00001$
#define _exit_thread1 00002$
#define _exit_thread2 00003$
#define _exit_thread3 00004$
#define _exit_begin 00005$
#define _exit_try_thread3 00006$
#define _exit_try_thread2 00007$
#define _exit_try_thread1 00008$
#define _exit_try_thread0 00009$
#define _exit_end 00010$
void ThreadExit(void)
{
    // [CRITICAL SECTION] Disable interrupt
    EA = 0;
    
    __asm
            MOV A, _current_thread_id
            JZ _exit_thread0
            DEC A
            JZ _exit_thread1
            DEC A
            JZ _exit_thread2
            MOV A, _thread_bitmap
            XRL A, #8
            MOV _thread_bitmap, A
            JNZ _exit_begin
        _exit_thread0:
            MOV A, _thread_bitmap
            XRL A, #1
            MOV _thread_bitmap, A
            JNZ _exit_begin
        _exit_thread1:
            MOV A, _thread_bitmap
            XRL A, #2
            MOV _thread_bitmap, A
            JNZ _exit_begin
        _exit_thread2:
            MOV A, _thread_bitmap
            XRL A, #4
            MOV _thread_bitmap, A
        _exit_begin:
            MOV A, _current_thread_id
            INC A
            ANL A, #3
            JZ _exit_try_thread0
            DEC A
            JZ _exit_try_thread1
            DEC A
            JZ _exit_try_thread2

        _exit_try_thread3:
            MOV _current_thread_id, #3
            MOV A, _thread_bitmap
            ANL A, #8
            JNZ _exit_end
            JZ _exit_begin
        
        _exit_try_thread0:
            MOV _current_thread_id, #0
            XRL _direction, #0xFE
            MOV A, _thread_bitmap
            ANL A, #1
            JNZ _exit_end
            JZ _exit_begin

        _exit_try_thread1:
            MOV _current_thread_id, #1
            MOV A, _thread_bitmap
            ANL A, #2
            JNZ _exit_end
            JZ _exit_begin

        _exit_try_thread2:
            MOV _current_thread_id, #2
            MOV A, _thread_bitmap
            ANL A, #4
            JNZ _exit_end
            JZ _exit_begin

        _exit_end:            
    __endasm;
    RESTORESTATE;

    // [CRITICAL SECTION] Reenable interrupt
    EA = 1;
}

// Exclusively only for local use in myTimer0Handler function
#define _timer0_begin 00001$
#define _timer0_try_thread3 00002$
#define _timer0_try_thread0 00003$
#define _timer0_try_thread1 00004$
#define _timer0_try_thread2 00005$
#define _timer0_end 00006$
void myTimer0Handler(void)
{
    // [CRITICAL SECTION START] Disable interrupts
    EA = 0;
    SAVESTATE;
    __asm
        _timer0_begin:
            MOV A, _current_thread_id
            ADD A, _direction
            ANL A, #3
            
            JZ _timer0_try_thread0
            DEC A
            JZ _timer0_try_thread1
            DEC A
            JZ _timer0_try_thread2

        _timer0_try_thread3:
            MOV _current_thread_id, #3
            MOV A, _thread_bitmap
            ANL A, #8
            JNZ _timer0_end
            JZ _timer0_begin
        
        _timer0_try_thread0:
            MOV _current_thread_id, #0
            XRL _direction, #0xFE
            MOV A, _thread_bitmap
            ANL A, #1
            JNZ _timer0_end
            JZ _timer0_begin

        _timer0_try_thread1:
            MOV _current_thread_id, #1
            MOV A, _thread_bitmap
            ANL A, #2
            JNZ _timer0_end
            JZ _timer0_begin

        _timer0_try_thread2:
            MOV _current_thread_id, #2
            MOV A, _thread_bitmap
            ANL A, #4
            JNZ _timer0_end
            JZ _timer0_begin
            
        _timer0_end:
    __endasm;
    RESTORESTATE;
    EA = 1;
    // [CRITICAL SECTION END] Reenable interrupts

    // Return from interrupt
    __asm
        RETI
    __endasm;
}