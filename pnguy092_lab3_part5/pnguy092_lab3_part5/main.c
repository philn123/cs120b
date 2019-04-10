/*
 * pnguy092_lab3_part5.c
 *
 * Created: 4/9/2019 11:37:59 PM
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
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFE; PORTB = 0x01; //1 means input, 0 means output
	
	unsigned short weight_sensor = 0x0000;
	
    while (1) 
    {
		unsigned char output = 0x00;
		weight_sensor = PIND << 1;
		unsigned char temp = PINB & 0x01;
		weight_sensor = weight_sensor | temp;
		
		if(weight_sensor >= 70){
			output = SetBit(output, 1, 1);
			
		}
		else if(weight_sensor > 5 && weight_sensor < 70){
			output = SetBit(output, 1, 0);
			output = SetBit(output, 2, 1);
		}
		PORTB = output;
		weight_sensor = 0x0000;
		
    }
}

