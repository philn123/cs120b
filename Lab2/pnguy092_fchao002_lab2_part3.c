/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 2 Exercise 3
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
	
	
    while (1)
    {
		//4 available spots
		unsigned char full = 0x00;
		unsigned char tmpC0 = 0x01;
		unsigned char tmpC1 = 0x02;
		unsigned char tmpC2 = 0x04;
		unsigned char tmpC3 = 0x08;
		
		tmpA0 = PINA & 0x01;
		tmpA1 = PINA & 0x02;
		tmpA2 = PINA & 0x04;
		tmpA3 = PINA & 0x08;
		
		if(tmpA0 == 0x01){
			full++;
			tmpC0 = 0x00;
		}
		if(tmpA1 == 0x02){
			full++;
			tmpC1 = 0x00;
		}
		if(tmpA2 == 0x04){
			full++;
			tmpC2 = 0x00;
		}
		if(tmpA3 == 0x08){
			full++;
			tmpC3 = 0x00;
		}
		
		if(full == 0x04){
			PORTC = 0xFF;
		}
		else{
			PORTC = tmpC0 | tmpC1 | tmpC2 | tmpC3;	
		}
	  

    }
    return 0;
}

