#include <8051.h>
#include "keylib.h"
#include "lcdlib.h"
#include "buttonlib.h"
#include "preemptive.h"

// Read-only data
const char dinosaur[] = {0x07, 0x05, 0x06, 0x07, 0x14, 0x17, 0x0E, 0x0A};
const char cactus[] = {0x04, 0x05, 0x15, 0x15, 0x16, 0x0C, 0x04, 0x04};

// Global variable for preemptive scheduling
__data __at (0x28) char direction;

// Global variables for display
__data __at (0x29) unsigned char lcd_ready;
__data __at (0x2A) char temp_map;
__data __at (0x2B) char map_mutex;
__data __at (0x2C) char map0_l;
__data __at (0x2D) char map0_r;
__data __at (0x2E) char map1_l;
__data __at (0x2F) char map1_r;
__data __at (0x3F) char render_it;

// Global variables for keypad buffer
__data __at (0x30) char buffer_mutex;
__data __at (0x31) char buffer_full;
__data __at (0x32) char shared_buffer;
__data __at (0x33) char out_data;

// Global variables for dinosaur and game state
__data __at (0x34) char dinosaur_row;
__data __at (0x35) char difficulty;
__data __at (0x36) char score;
__data __at (0x37) char current_phase;
__data __at (0x38) char current_pass;

// Keeps track of the button state for the keypad and writes the
// ASCII code to the shared buffer for the `game_ctrl` thread to 
// interpret.
void keypad_control(void)
{
    while(1)
    {
        // Poll for keypad press
        while(!AnyKeyPressed());
        SemaphoreWait(buffer_mutex);
        // Obtain new data
        shared_buffer = KeyToChar();
        SemaphoreSignal(buffer_mutex);
        // Poll for keypad release
        while(AnyKeyPressed());


        // Update flag
        buffer_full = 1;
        ThreadYield();
    }
}

// Tracking commands from the `game_ctrl` thread and updates the 
// contents of display.
void render_task(void)
{
    while(1)
    {
        if (current_phase == 0)
        {
            LCD_cursorGoTo(0, 0);
            LCD_write_char('C');
            LCD_write_char('S');
            LCD_write_char('3');
            LCD_write_char('4');
            LCD_write_char('2');
            LCD_write_char('3');
            LCD_write_char(' ');
            LCD_write_char('O');
            LCD_write_char('S');
            LCD_write_char(' ');
            LCD_write_char('F');
            LCD_write_char('I');
            LCD_write_char('N');
            LCD_write_char('A');
            LCD_write_char('L');
        
            LCD_cursorGoTo(1, 0);
            LCD_write_char(' ');
            LCD_write_char('D');
            LCD_write_char('I');
            LCD_write_char('N');
            LCD_write_char('O');
            LCD_write_char('S');
            LCD_write_char('A');
            LCD_write_char('U');
            LCD_write_char('R');
            LCD_write_char(' ');
            LCD_write_char('G');
            LCD_write_char('A');
            LCD_write_char('M');
            LCD_write_char('E');
        }
        else if (current_phase == 1)
        {
            LCD_cursorGoTo(0, 0);
            SemaphoreWait(map_mutex);
            // Render row 0
            temp_map = map0_l;
            for(render_it = 0; render_it < 8; ++render_it)
            {
                __asm
                    PUSH ACC
                    MOV A, _temp_map
                    ANL A, #0x80
                    RLC A
                    ADDC A, #0
                    RL A
                    MOV DPL, A
                    LCALL _LCD_write_char
                    MOV A, _temp_map
                    RL A
                    MOV _temp_map, A
                    POP ACC
                __endasm;
            }
            temp_map = map0_r;
            for(; render_it < 15; ++render_it)
            {
                __asm
                    PUSH ACC
                    MOV A, _temp_map
                    ANL A, #0x80
                    RLC A
                    ADDC A, #0
                    RL A
                    MOV DPL, A
                    LCALL _LCD_write_char
                    MOV A, _temp_map
                    RL A
                    MOV _temp_map, A
                    POP ACC
                __endasm;
            }
            // Render row 1
            LCD_cursorGoTo(1, 0);
            temp_map = map1_l;
            for(render_it = 0; render_it < 8; ++render_it)
            {
                __asm
                    PUSH ACC
                    MOV A, _temp_map
                    ANL A, #0x80
                    RLC A
                    ADDC A, #0
                    RL A
                    MOV DPL, A
                    LCALL _LCD_write_char
                    MOV A, _temp_map
                    RL A
                    MOV _temp_map, A
                    POP ACC
                __endasm;
            }
            temp_map = map1_r;
            for(; render_it < 15; ++render_it)
            {
                __asm
                    PUSH ACC
                    MOV A, _temp_map
                    ANL A, #0x80
                    RLC A
                    ADDC A, #0
                    RL A
                    MOV DPL, A
                    LCALL _LCD_write_char
                    MOV A, _temp_map
                    RL A
                    MOV _temp_map, A
                    POP ACC
                __endasm;
            }
            SemaphoreSignal(map_mutex);

            // Render dinosaur
            LCD_cursorGoTo(dinosaur_row, 0);
            LCD_write_char('\1');
        }
        else if (current_phase == 2)
        {
            LCD_cursorGoTo(0, 0);
            LCD_write_char(' ');
            LCD_write_char(' ');
            LCD_write_char(' ');
            LCD_write_char('G');
            LCD_write_char('A');
            LCD_write_char('M');
            LCD_write_char('E');
            LCD_write_char(' ');
            LCD_write_char('O');
            LCD_write_char('V');
            LCD_write_char('E');
            LCD_write_char('R');
            LCD_write_char(' ');
            LCD_write_char(' ');


            LCD_cursorGoTo(1, 0);
            LCD_write_char(' ');
            LCD_write_char(' ');
            LCD_write_char(' ');
            LCD_write_char('S');
            LCD_write_char('C');
            LCD_write_char('O');
            LCD_write_char('R');
            LCD_write_char('E');
            LCD_write_char(':');
            LCD_write_char(' ');
            
            LCD_write_char('0' + (score / 10));
            LCD_write_char('0' + (score % 10));
            LCD_write_char(' ');
            LCD_write_char(' ');
            LCD_write_char(' ');
        }
        
        ThreadYield();
    }
}

// Responsible for:
// [1] Initializing the game state, including the score, the level
//     difficulty, dinosaur's row, the map of current cacti and their
//     positions, etc.
// [2] Adding cacti from the right and shifting them left each time.
// [3] Moving the dinosaur on every valid key press.
// [4] Update the score when successfully avoiding a collision.
// [5] End the game and display the score when the game is over.
void game_control(void) 
{
    while(1)
    {
        // [PHASE 0] GAME INITIALIZATION
        if (current_phase == 0)
        {
            // Query difficulty
            difficulty = (char)-1;
            while(1)
            {
                if (buffer_full == 1)
                {
                    SemaphoreWait(buffer_mutex);
                    out_data = shared_buffer;
                    buffer_full = 0;
                    SemaphoreSignal(buffer_mutex);

                    // User inputs '#', check for valid difficulty
                    if ((out_data == '#') && (difficulty >= 0) && (difficulty <= 9)) {break;}
                    // otherwise, keep querying
                    difficulty = out_data - '0';
                }

                ThreadYield();
            }

            // Compute the number of passes until the next map update
            current_pass = (10 - difficulty);
            // Transition to PHASE 1
            current_phase = 1;
            continue;
        }
        else if (current_phase == 1)
        {
            // Initial game state
            dinosaur_row = 0;
            score = 0;
            map0_l = 0x0C;
            map0_r = 0x51;
            map1_l = 0x61;
            map1_r = 0x04;

            while(current_phase == 1)
            {
                // Update dinosaur position
                if(buffer_full == 1)
                {
                    SemaphoreWait(buffer_mutex);
                    __asm
                        PUSH ACC
                        MOV A, _shared_buffer
                        ADD A, #-48
                        ANL A, #8
                        RR A
                        RR A
                        RR A
                        MOV _dinosaur_row, A
                        MOV _buffer_full, #0
                        POP ACC
                    __endasm;
                    SemaphoreSignal(buffer_mutex);
                }

                // Update map
                if (current_pass == 0)
                {
                    // Compute the number of passes until the next map update
                    current_pass = (10 - difficulty);
                    // Update map and score
                    SemaphoreWait(map_mutex);
                    __asm
                        PUSH ACC
                        MOV A, _map0_r
                        CLR C
                        RLC A
                        MOV _map0_r, A
                        MOV A, _map0_l
                        RLC A
                        MOV _map0_l, A
                        MOV A, _map0_r
                        ADDC A, #0
                        MOV _map0_r, A
                        MOV A, _map1_r
                        CLR C
                        RLC A
                        MOV _map1_r, A
                        MOV A, _map1_l
                        RLC A
                        MOV _map1_l, A
                        MOV A, _map1_r
                        ADDC A, #0
                        MOV _map1_r, A
                        CLR C
                        MOV A, _map0_l
                        ORL A, _map1_l
                        RLC A
                        CLR A
                        ADDC A, #0
                        ADD A, _score
                        MOV _score, A
                        POP ACC
                    __endasm;
                    SemaphoreSignal(map_mutex);
                }
                else
                {
                    --current_pass;
                }

                // Check for collision. If the dinosaur dies, transition to PHASE 2
                if (((dinosaur_row == 0) && (map0_l & 0x80)) || ((dinosaur_row == 1) && (map1_l & 0x80)))
                {
                    --score;
                    current_phase = 2;
                    continue;
                }
                
                ThreadYield();
            }
        }
        else if (current_phase == 2)
        {
            // Stay in PHASE 2 for 10 cycles
            current_pass = 10;
            while(current_pass--) {ThreadYield();}
            
            // Transition back to PHASE 0
            current_phase = 0;
            continue;
        }
    }
}

void main(void)
{       
    // Initialize global variables
    SemaphoreCreate(map_mutex, 1);
    SemaphoreCreate(buffer_mutex, 1);
    direction = 1;
    // Initialize Keypad
    Init_Keypad();
    // Initialize LCD
    LCD_Init();
    LCD_set_symbol('\10', dinosaur);
    LCD_set_symbol('\20', cactus);
    // Set up keypad control
    ThreadCreate(keypad_control);
    // Set up render task
    ThreadCreate(render_task);
    // Set up game control (use the current task)
    game_control();
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