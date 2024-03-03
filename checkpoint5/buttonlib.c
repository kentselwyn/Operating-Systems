#include <8051.h>
#include "buttonlib.h"

char AnyButtonPressed(void)
{
    return ~P2;
}

char ButtonToChar(void) 
{
    if ((~P2) & 0x80) {return '7';} 
    if ((~P2) & 0x40) {return '6';}
    if ((~P2) & 0x20) {return '5';}
    if ((~P2) & 0x10) {return '4';}
    if ((~P2) & 0x08) {return '3';}
    if ((~P2) & 0x04) {return '2';}
    if ((~P2) & 0x02) {return '1';}
    if ((~P2) & 0x01) {return '0';}
    return '\0';
}

