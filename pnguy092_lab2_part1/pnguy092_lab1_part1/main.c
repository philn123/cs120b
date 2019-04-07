/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 2 Exercise 1
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
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

