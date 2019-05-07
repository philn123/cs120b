/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 8 Exercise 4
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
unsigned short threshold = 0x00;
unsigned short max = 0x57;

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    threshold = (max / 8);
    
    ADC_init();
    /* Replace with your application code */
    while (1) 
    {
        adc = ADC;
        if(adc < threshold){
            PORTB = 0x01;
        }
        else if(adc < threshold*2){
            PORTB = 0x03;
        }
        else if(adc < threshold*3){
            PORTB = 0x07;
        }
        else if(adc < threshold*4){
            PORTB = 0x0F;
        }
        else if(adc < threshold*5){
            PORTB = 0x1F;
        }
        else if(adc < threshold*6){
            PORTB = 0x3F;
        }
        else if(adc < threshold*7){
            PORTB = 0x7F;
        }
        else if(adc < threshold*8){
            PORTB = 0xFF;
        }
       
        
        
        
        
    }
}

