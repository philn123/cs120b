/*
 * pnguy092_lab1_part2.c
 *
 * Created: 4/4/2019 9:16:32 AM
 * Author : Phillip
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
		
		/*
		this outputs in binary how many spots
		are left in the parking spaces
		*/
		PORTC = cntavail;
	  

    }
    return 0;
}

