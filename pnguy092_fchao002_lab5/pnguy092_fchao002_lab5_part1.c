/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 5 Exercise 1
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>

unsigned char SetBit( unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit( unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    unsigned char output = 0x00;
	
    /* Replace with your application code */
    while (1) 
    {
		output = 0x00;
		unsigned char val = PINA & 0x0F;
		
		if(val == 1 || val == 2){
			output = SetBit(output, 5, 1);
		}
		else if(val == 3 || val == 4){
			output = SetBit(output, 5, 1);
			output = SetBit(output, 4, 1);
		}
		else if(val == 5 || val == 6){
			output = SetBit(output, 5, 1);
			output = SetBit(output, 4, 1);
			output = SetBit(output, 3, 1);
		}
		else if(val == 7 || val == 8 || val == 9){
			output = SetBit(output, 5, 1);
			output = SetBit(output, 4, 1);
			output = SetBit(output, 3, 1);
			output = SetBit(output, 2, 1);
		}
		else if(val == 10 || val == 11 || val == 12){
			output = SetBit(output, 5, 1);
			output = SetBit(output, 4, 1);
			output = SetBit(output, 3, 1);
			output = SetBit(output, 2, 1);
			output = SetBit(output, 1, 1);
		}
		else if(val == 13 || val == 14 || val == 15){
			output = SetBit(output, 5, 1);
			output = SetBit(output, 4, 1);
			output = SetBit(output, 3, 1);
			output = SetBit(output, 2, 1);
			output = SetBit(output, 1, 1);
			output = SetBit(output, 0, 1);
		}
		
		if(val <= 4){
			output = SetBit(output, 6, 1);
		}
		
		
		PORTC = output;
		
		
		
    }
}

