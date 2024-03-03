#include <8051.h>
#include "cooperative.h"

// Global variables for producer-consumer
__data __at (0x20) char thread_bitmap;
__data __at (0x21) ThreadID current_thread_id;
__data __at (0x22) char new_thread_id;
__data __at (0x23) char temp_SP;
__data __at (0x24) char saved_SP[4];
__data __at (0x3E) char it;

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

// Allow other sources to reference `main`
extern void main(void);

void Bootstrap(void)
{
   // Initialize global data structures
   thread_bitmap = 0x00;
   // Create a new thread for main
   current_thread_id = ThreadCreate(main);
   // Jump to main and start running
   RESTORESTATE;
}

ThreadID ThreadCreate(FunctionPtr fp)
{
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
   // [i] Return the new thread ID
   return new_thread_id;
}

void ThreadYield(void)
{
   SAVESTATE;
   do
   {
      // Cycle through thread IDs (RR policy)
      current_thread_id = ((current_thread_id == 3) ? (0) : (current_thread_id + 1));
      // If the current thread is active, break
      if(thread_bitmap & (1 << current_thread_id)) {break;}
   } while (1);
   RESTORESTATE;
}

void ThreadExit(void)
{
   // Remove bit in the bitmap
   thread_bitmap &= (0xFF ^ (1 << current_thread_id)); 
   for(it = 0; it < 4; ++it)
   {
      // Set to existing active thread
      if(thread_bitmap & (1 << it)) {current_thread_id = it; break;}
   }
   RESTORESTATE;
}
