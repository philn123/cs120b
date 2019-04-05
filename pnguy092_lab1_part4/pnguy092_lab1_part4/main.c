/*
 * pnguy092_lab1_part4.c
 *
 * Created: 4/5/2019 1:55:33 PM
 * Author : Phillip
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	unsigned char tempC = 0x00;
	
    while (1) 
    {
		unsigned char pd0 = 0x00;
		unsigned char pd1 = 0x00;
		unsigned char total_weight = 0x00;
		
		//temp variables hold value of PIN's A-C
		tempA = PINA;
		tempB = PINB;
		tempC = PINC;
		
		total_weight = tempA | tempB | tempC;
		if(total_weight > 0x8C){
			pd0 = 0x01;
		}
		if(tempA - tempC > 0x50){
			pd1 = 0x02;
		}
		
		
		
		PORTD = pd0 | pd1;
		
		
    }
}

