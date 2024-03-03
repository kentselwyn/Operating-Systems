#include <8051.h>

void Init_Keypad(void)
{
	// Input mode from AND gate
	P3_3 = 1;
	// Configure column top 3 bits as input, columns as pull-down.
	P0 = 0xF0;
}

char AnyKeyPressed(void)
{
	// Set all rows to pull-down
	P0 = 0xF0;
	// Return true if any button is connected to pull-down
	__asm
		MOV C, _P3_3
		CPL C
		CLR A
		RLC A
		MOV DPL, A
		RET
	__endasm;
}

char KeyToChar(void)
{
	P0 = 0xF7; // test the top row
	if (P0 == 0xB7) { return '1'; }
	if (P0 == 0xD7) { return '2'; }
	if (P0 == 0xE7) { return '3'; }
	P0 = 0xFB; // test the next row
	if (P0 == 0xBB) { return '4';}
	if (P0 == 0xDB) { return '5'; }
	if (P0 == 0xEB) { return '6'; }
	P0 = 0xFD;  // test the 3rd row
	if (P0 == 0xBD) { return '7';}
	if (P0 == 0xDD) { return '8'; }
	if (P0 == 0xED) { return '9'; }
	P0 = 0xFE;  // test the last row
	if (P0 == 0xBE) { return '*'; }
	if (P0 == 0xDE) { return '0'; }
	if (P0 == 0xEE) { return '#'; }
	return 0;
}
