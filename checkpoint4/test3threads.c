#include <8051.h>
#include "preemptive.h"

// Global variable for preemptive scheduling
__data __at (0x28) char direction;

// Global variables for producer-consumer
__data __at (0x30) char mutex;
__data __at (0x31) char full;
__data __at (0x32) char empty;
__data __at (0x33) char in;
__data __at (0x34) char out;
__data __at (0x35) char shared_buffer[3];
__data __at (0x38) char next_data_1;
__data __at (0x39) char next_data_2;

void Producer1(void)
{
        // Initialize producer
        next_data_1 = 'A';
        while(1)
        {
                SemaphoreWait(empty);
                SemaphoreWait(mutex);
                // [CRITICAL SECTION START] Disable interrupts
                EA = 0;
                // Write new data
                shared_buffer[in] = next_data_1;
                // Update in pointer
                in = ((in == 2) ? (0) : (in + 1));
                EA = 1;
                // [CRITICAL SECTION END] Reenable interrupts
                SemaphoreSignal(mutex);
                SemaphoreSignal(full);
                // Compute new data
                next_data_1 = ((next_data_1 == 'Z') ? ('A') : (next_data_1 + 1));
        }
}

void Producer2(void)
{
        // Initialize producer
        next_data_2 = '0';
        while(1)
        {
                SemaphoreWait(empty);
                SemaphoreWait(mutex);
                // [CRITICAL SECTION START] Disable interrupts
                EA = 0;
                // Write new data
                shared_buffer[in] = next_data_2;
                // Update in pointer
                in = ((in == 2) ? (0) : (in + 1));
                EA = 1;
                // [CRITICAL SECTION END] Reenable interrupts
                SemaphoreSignal(mutex);
                SemaphoreSignal(full);
                
                // Compute new data
                next_data_2 = ((next_data_2 == '9') ? ('0') : (next_data_2 + 1));
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
                SemaphoreWait(full);
                SemaphoreWait(mutex);
                // [CRITICAL SECTION START] Disable interrupts
                EA = 0;
                // Get data, write to serial port Tx
                SBUF = shared_buffer[out];
                // Update out pointer
                out = ((out == 2) ? (0) : (out + 1));
                EA = 1;
                // [CRITICAL SECTION END] Reenable interrupts
                SemaphoreSignal(mutex);
                SemaphoreSignal(empty);
                
                // Poll for Tx to finish writing
                while(TI == 0); // {ThreadYield();} No voluntary yield, rely on preemption
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
        direction = 1;
        // Set up producer 1
        ThreadCreate(Producer1);
        // Set up producer 2
        ThreadCreate(Producer2);
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