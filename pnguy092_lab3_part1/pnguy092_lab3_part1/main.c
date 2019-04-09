/*
 * pnguy092_lab3_part1.c
 *
 * Created: 4/8/2019 8:37:25 PM
 * Author : iiNza
 */ 

#include <avr/io.h>


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0x00;
	
	unsigned char count = 0x00;
	unsigned char temp = 0x00;
	
	while(1){
	
		for(unsigned char i = 0; i <0x08; i++){
			temp = (PINA >> i) & 0x01;
			if(temp == 0x01){
				count++;
			}
			
		}	
		for(unsigned char j = 0; j < 0x08; j++){
			temp = (PINB >> j) & 0x01;
			if(temp == 0x01){
				count++;
			}
			
		}
		
		PORTC = count;
		count = 0;
		
		
	}
	
	
}

