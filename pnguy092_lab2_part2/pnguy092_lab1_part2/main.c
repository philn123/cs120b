/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 2 Exercise 2
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs

	DDRC = 0xFF; PORTC = 0x00; //Port C is output of parking
	
    unsigned char tmpA0 = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpA1 = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpA2 = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpA3 = 0x00; // Temporary variable to hold the value of A
	unsigned char full = 0x00;
	
    while (1)
    {
		//4 available spots
		full = 0x00;
		unsigned char cntavail = 0x04;
		
		tmpA0 = PINA & 0x01;
		tmpA1 = PINA & 0x02;
		tmpA2 = PINA & 0x04;
		tmpA3 = PINA & 0x08;
		
		if(tmpA0 == 0x01){
			cntavail--;
		}
		if(tmpA1 == 0x02){
			cntavail--;
		}
		if(tmpA2 == 0x04){
			cntavail--;
		}
		if(tmpA3 == 0x08){
			cntavail--;
		}
		if(cntavail == 0x00){
			full = 0x80;
		}
		
		/*
		this outputs in binary how many spots
		are left in the parking spaces
		*/
		PORTC = cntavail | full;
	  

    }
    return 0;
}

