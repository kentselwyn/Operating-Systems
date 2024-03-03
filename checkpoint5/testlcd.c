#include <8051.h>
#include "keylib.h"
#include "lcdlib.h"
#include "buttonlib.h"
#include "preemptive.h"

// Global variable for preemptive scheduling
__data __at (0x28) char direction;

// Global variable for display
__data __at (0x29) unsigned char lcd_ready;

// Global variables for button and keypad buffer
__data __at (0x30) char mutex;
__data __at (0x31) char full;
__data __at (0x32) char empty;
__data __at (0x33) char in;
__data __at (0x34) char out;
__data __at (0x35) char shared_buffer[3];
__data __at (0x38) char next_data_1;
__data __at (0x39) char next_data_2;
__data __at (0x3A) char out_data;

// Producer 1 reads from the button bank
void Producer1(void)
{
    // Initialize producer
    next_data_1 = 'X';
    while(1)
    {
        // Poll for button press
        while(!AnyButtonPressed());
        // Obtain new data
        next_data_1 = ButtonToChar();
        // Poll for button release 
        while(AnyButtonPressed());
        
        SemaphoreWait(empty);
        SemaphoreWait(mutex);
        // Write new data
        shared_buffer[in] = next_data_1;
        // Update in pointer
        in = ((in == 2) ? (0) : (in + 1));
        SemaphoreSignal(mutex);
        SemaphoreSignal(full);

    }
}

// Producer 2 reads from the keypad
void Producer2(void)
{
    // Initialize producer
    next_data_2 = 'X';
    while(1)
    {
        // Poll for keypad press
        while(!AnyKeyPressed());
        // Obtain new data
        next_data_2 = KeyToChar();
        // Poll for keypad release
        while(AnyKeyPressed());

        SemaphoreWait(empty);
        SemaphoreWait(mutex);
        // Write new data
        shared_buffer[in] = next_data_2;
        // Update in pointer
        in = ((in == 2) ? (0) : (in + 1));
        SemaphoreSignal(mutex);
        SemaphoreSignal(full);
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
        out_data = shared_buffer[out];
        // Update out pointer
        out = ((out == 2) ? (0) : (out + 1));
        SemaphoreSignal(mutex);
        SemaphoreSignal(empty);
        
        // Poll for ldc_ready
        while(!lcd_ready); 
        // Write output
        LCD_write_char(out_data);
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
    // Initialize Keypad
    Init_Keypad();
    // Initialize LCD
    LCD_Init();
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