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
	unsigned char tmpC = 0x00; //temp var for C
	unsigned char cntavail;
	
    while (1)
    {
		
	  
	  
	  
    }
    return 0;
}

