#include <8051.h>
#include "lcdlib.h"

__data __at (0x29) unsigned char lcd_ready;

#define DB7 P1_7
#define DB6 P1_6
#define DB5 P1_5
#define DB4 P1_4
#define DB P1
#define RS P1_3
#define E P1_2

void delay(unsigned char n);
#define DELAY_AMOUNT 40

unsigned char LCD_ready(void)
{
    return lcd_ready;
}

void LCD_Init(void)
{
	LCD_functionSet();
	LCD_entryModeSet(1, 1); // No increment with shift
	LCD_displayOnOffControl(1, 1, 1); // Display on, cursor on, and blinking on
	lcd_ready = 1;
}
void LCD_IRWrite(char c)
{
	lcd_ready = 0;
	DB = (c & 0xf0); // High nibble, keep RS low
	E = 1;  // Pulse E
	E = 0;
	DB = (c << 4); // Low nibble, keep RS low
	E = 1;
	E = 0;
	delay(DELAY_AMOUNT);
	lcd_ready = 1;
}

void LCD_functionSet(void)
{
	lcd_ready = 0;
	// The high nibble for the function set is actually sent twice
	// because this is how 4-bit mode works for the HD44780 controller.
	DB = 0x20;  // DB<7:4> = 0010, <RS,E,x,x>=0
	E = 1;
	E = 0;
	delay(DELAY_AMOUNT);
	E = 1;
	E = 0;
	delay(DELAY_AMOUNT); // Added to ensure sufficient delay
	DB7 = 1; // 2-line model
	// DB6 defaults to 0 = 5x7, DB5, DB4 are don't-cares
	E = 1;
	E = 0;
	delay(DELAY_AMOUNT);
	lcd_ready = 1;
}

void LCD_write_char(char c)
{
	lcd_ready = 0;
	DB = (c & 0xf0) | 0x08; // Keep the RS
	RS = 1;
	E = 1;
	E = 0;
	DB = (c << 4) | 0x08; // Keep the RS
	E = 1;
	E = 0;
	delay(DELAY_AMOUNT);
	lcd_ready = 1;
}

void LCD_write_string(char* str)
{
	while (*str++)
    {
		LCD_write_char(*str);
	}
}

void delay(unsigned char n)
{
	__asm
	    dhere:
		    djnz dpl, dhere
	__endasm;
}
