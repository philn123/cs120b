/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 2 Exercise 4
* 
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	unsigned char tempC = 0x00;
	
	unsigned char pd0 = 0x00;
	unsigned char pd1 = 0x00;
	unsigned short total_weight = 0x00;
	
    while (1) 
    {
		pd0 = 0x00;
		pd1 = 0x00;
		total_weight = 0x00;
		
		//temp variables hold value of PIN's A-C
		tempA = PINA;
		tempB = PINB;
		tempC = PINC;
		
		total_weight = tempA + tempB + tempC;
		if(total_weight > 0x8C){
			pd0 = 0x01;
		}
		if(abs(tempA - tempC) > 0x50){
			pd1 = 0x02;
		}
		
		
		
		PORTD = pd0 | pd1;
		
		
    }
}

