/*
 * pnguy092_lab7.c
 *
 * Created: 4/24/2019 9:40:20 PM
 * Author : iiNza
 */ 

#include <avr/io.h>
#include "io.c"

int main(void)
{
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	
	const unsigned char *string = "Hello";
	
	// Initializes the LCD display
	LCD_init();
	
	// Starting at position 1 on the LCD screen, writes Hello World
	LCD_DisplayString(1, string);
	
	while(1) {continue;}
}

