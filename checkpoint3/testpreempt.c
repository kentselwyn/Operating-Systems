#include <8051.h>
#include "preemptive.h"

// Global variables for producer-consumer
__data __at (0x30) char mutex;
__data __at (0x31) char full;
__data __at (0x32) char empty;
__data __at (0x33) char in;
__data __at (0x34) char out;
__data __at (0x35) char shared_buffer[3];
__data __at (0x39) char next_data;

void Producer(void)
{
    // Initialize producer
    next_data = 'A';
    while(1)
    {
        // Wait for buffer to be free
        SemaphoreWait(empty);
        SemaphoreWait(mutex);
        // [CRITICAL SECTION START] Disable interrupts
        EA = 0;
        // Write new data
        shared_buffer[in] = next_data;
        EA = 1;
        // [CRITICAL SECTION END] Reenable interrupts
        SemaphoreSignal(mutex);
        SemaphoreSignal(full);
        
        // Update in pointer
        in = ((in == 2) ? (0) : (in + 1));
        // Compute new data
        next_data = ((next_data == 'Z') ? ('A') : (next_data + 1));
    }
}

void Consumer(void) 
{
    // Initialize Tx for polling
    TMOD |= 0x20;
    TH1 = (char)-6;
    SCON = 0x50;
    TR1 = 1;

    while (1)
    {
    // Wait for new data from producer
        while (!full); // {ThreadYield();} No voluntary yield, rely on preemption
            
        SemaphoreWait(full);
        SemaphoreWait(mutex);
        // [CRITICAL SECTION START] Disable interrupts
        EA = 0;
        // Get data, write to serial port Tx, and clear buffer full flag
        SBUF = shared_buffer[out];
        EA = 1;
        // [CRITICAL SECTION END] Reenable interrupts
        SemaphoreSignal(mutex);
        SemaphoreSignal(empty);
        
        // Update out pointer
        out = ((out == 2) ? (0) : (out + 1));

        // Poll for Tx to finish writing
        while(!TI); // {ThreadYield();} No voluntary yield, rely on preemption
        // Clear Tx flag
        TI = 0;
    }
}

void main(void)
{       
    // Initialize global variables
    SemaphoreCreate(mutex, 1);
    SemaphoreCreate(full, 0);
    SemaphoreCreate(empty, 3);
    in = 0;
    out = 0;
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