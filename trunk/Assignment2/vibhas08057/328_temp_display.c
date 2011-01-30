#define F_CPU 16000000UL // This is the frequency of the compiler.
#include <avr/io.h> //For input and output
#include "lcd.h"
#include "delay_x.h" //"" means that it will search in the current directory


int main()
{
   int val_x;
   int vol_x;
   char value[10];
   char voltage[10];
   char * value1;
   char * voltage1;
   lcd_init(LCD_DISP_ON);   
   DDRD = 3;
   PORTD = 1;
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
   
   //ADMUX |= (1 << ADLAR);
   //ADMUX |= 1;
   //ADCSRA |= (1 << ADFR); 
   
   ADCSRA = ADCSRA | (1<<ADEN); // Enable ADC 
   
       while (1)              
       {       
	       ADCSRA = ADCSRA | (1<<ADSC); // Start A2D Conversions 
		   if((ADCSRA & 0x40)!=0)
		   {
		      lcd_clrscr(); 
              lcd_puts("Started \nConversion ");
			  _delay_ms(500);
		      
            }

		   _delay_ms(500);
           
		   val_x=ADCL;
		   val_x = val_x | (ADCH<<8);
		   itoa(val_x,value,10);
		   value1 = value;             
           vol_x = val_x * 5;
           itoa(vol_x,voltage,10);
		   voltage1 = voltage;
		         
           if((ADCSRA & 0x40)==0)
		   {
		      lcd_clrscr(); 
              lcd_puts("Conversion \nComplete "); 
		      
            }

			_delay_ms(500);

            lcd_clrscr(); 
			lcd_puts("Value: "); 
		    lcd_puts(value1); 
		    lcd_puts("\nVoltage: "); 
		    lcd_puts(voltage1); 
            lcd_puts(" mV"); 
			_delay_s(2);

		   
        }    
   return 1;
}
 
