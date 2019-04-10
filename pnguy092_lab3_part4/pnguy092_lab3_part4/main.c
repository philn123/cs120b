/*
 * pnguy092_lab3_part4.c
 *
 * Created: 4/9/2019 11:20:46 PM
 * Author : iiNza
 */ 

#include <avr/io.h>
// Bit-access function
unsigned char SetBit( unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit( unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	
    while (1) 
    {
		PORTB = (PINA & 0xF0) >> 4;
		PORTC = (PINA & 0x0F) << 4;
		
    }
}

