/*
 * pnguy092_lab1_part1.c
 *
 * Created: 4/4/2019 8:13:00 AM
 * Author : Phillip
 */ 

#include <avr/io.h>


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; 
   
    unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
    unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpA1 = 0x00; // Temporary variable to hold the value of A1

    while (1)
    {
	    // 1) Read input
	    tmpA = PINA & 0x01;
		tmpA1 = PINA & 0x02;
	    // 2) Perform computation
		
	    if (tmpA == 0x01 && tmpA1 == 0x00) { // True if PA0 is 1 and PA1 is 0
		    tmpB = (tmpB & 0xFC) | 0x01;
	    }
	    else {
		    tmpB = (tmpB & 0xFC) | 0x00; // Sets tmpB to bbbbbb00
	    }
	    // 3) Write output
	    PORTB = tmpB;
    }
    return 0;
}

