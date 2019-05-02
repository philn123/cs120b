/*
 * pnguy092_lab8_part2.c
 *
 * Created: 5/1/2019 9:40:11 PM
 * Author : Phillip
 */ 

#include <avr/io.h>

void ADC_init () {
    ADCSRA |= (1 << ADEN ) | (1 << ADSC ) | (1 << ADATE );
    // ADEN: setting this bit enables analog-to-digital conversion.
    // ADSC: setting this bit starts the first conversion.
    // ADATE: setting this bit enables auto-triggering. Since we are
    // in Free Running Mode, a new conversion will trigger whenever
    // the previous conversion completes.
}

unsigned short adc = 0x00;

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    
    ADC_init();
    /* Replace with your application code */
    while (1) 
    {
        adc = ADC;
        PORTB = (char)adc;
        PORTD = (char)(adc >> 8);
        
    }
}

