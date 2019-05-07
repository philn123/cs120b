/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 8 Exercise 3
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
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
unsigned short max = 0x57;

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
        if(adc >= max/2){
            PORTB = 0x01;
        }
        else{
            PORTB = 0x00;
        }
        
    }
}

