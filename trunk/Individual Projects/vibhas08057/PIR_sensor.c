#define F_CPU 16000000UL // This is the frequency of the compiler.
#include <avr/io.h> //For input and output
#include "lcd.h"
#include "delay_x.h" //"" means that it will search in the current directory

//uint8_t readButton(void);    //Declaration of the readButton function

int main(void)
{
	lcd_init(LCD_DISP_ON);
	DDRD = 0b00000010;    //Configure PORTD pin 2 as an input
	PORTD = 0b00000100;    //Activate pull-ups in PORTD pin 2
	//DDRD |= (1<<PD1);    //Configure PORTB pin 5 an output, this is the digital 13 in the Arduino that as the built-in led
    int flag = 0;    

 	while(1)
	{                //Infinite loop
 	//if(readButton()==1){        //Verify the button state
 		if((PIND & 0b00000100) == 0b00000100)
 		{
 			PORTD = 0b00000110; 
			lcd_clrscr();
 			lcd_puts("Movement");
 			_delay_ms(10);   //This is the above mentioned XOR that toggles the led
 		}
  
 		else
 		{
		    flag = 0;
		    for(int i = 1; i < 12000; i++)
			{
			   if((PIND & 0b00000100) == 0b00000100)
			   {
			      flag = 1;
			      break;
			   }
               _delay_ms(10); 
			}

			if(flag!=1)
			{
			   PORTD = 0b00000100;
			   lcd_clrscr();
			   lcd_puts("No Movement");
			   _delay_ms(10);
			}

    		/*PORTD = 0b00000100;
			lcd_clrscr();
			lcd_puts("No Movement");
			_delay_ms(10);*/
 		}
	 //_delay_ms(250);            //Delay between consecutive button presses
 	}
}


 
