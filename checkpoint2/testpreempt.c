#include <8051.h>
#include "preemptive.h"

// Global variables
__data __at (0x30) char full;
__data __at (0x31) char shared_buffer;
__data __at (0x32) char next_data;

void Producer(void)
{
        // Initialize producer
        next_data = 'A';
        while(1)
        {
                // Wait for buffer to be free
                while(full); // {ThreadYield();} No voluntary yield, rely on preemption

                // [CRITICAL SECTION START] Disable interrupts
                EA = 0;
                // Write new data
                shared_buffer = next_data;
                // Flag buffer as full
                full = 1;
                EA = 1;
                // [CRITICAL SECTION END] Reenable interrupts
                
                // Compute new data
                next_data = ((next_data == 'Z') ? ('A') : (next_data + 1));
        }
}

void Consumer(void) {
        // Initialize Tx for polling
        TMOD |= 0x20;
        TH1 = (char)-6;
        SCON = 0x50;
        TR1 = 1;

        while (1)
        {
                // Wait for new data from producer
                while (!full); // {ThreadYield();} No voluntary yield, rely on preemption
                
                // [CRITICAL SECTION START] Disable interrupts
                EA = 0;
                // Get data, write to serial port Tx, and clear buffer full flag
                SBUF = shared_buffer;
                full = 0;
                EA = 1;
                // [CRITICAL SECTION END] Reenable interrupts

                // Poll for Tx to finish writing
                while(!TI); // {ThreadYield();} No voluntary yield, rely on preemption
                // Clear Tx flag
                TI = 0;
        }
}

void main(void)
{       
        // Initialize global variables
        full = 0;
        // Set up producer
        ThreadCreate(Producer);
        // Set up consumer (use current thread)
        Consumer();
}

void _sdcc_gsinit_startup(void) 
{
        __asm
                ljmp  _Bootstrap
        __endasm;
}

void _mcs51_genRAMCLEAR(void) {}
void _mcs51_genXINIT(void) {}
void _mcs51_genXRAMCLEAR(void) {}
void timer0_ISR(void) __interrupt(1)
{
        __asm
                ljmp _myTimer0Handler
        __endasm;
}