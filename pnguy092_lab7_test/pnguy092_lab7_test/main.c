/*
 * pnguy092_lab7_test.c
 *
 * Created: 4/25/2019 8:59:37 AM
 * Author : Phillip
 */ 


#include <avr/io.h>
#include "io.c"

int main(void)
{
    DDRC = 0xFF; PORTC = 0x00; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
    
    // Initializes the LCD display
    LCD_init();
    
    // Starting at position 1 on the LCD screen, writes Hello World
    LCD_DisplayString(1, "Hello World");
    
    while(1) {continue;}
}


