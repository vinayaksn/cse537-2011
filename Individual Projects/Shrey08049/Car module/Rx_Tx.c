


#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"
#include <avr/interrupt.h>
#include"USART328.h"
#include"USART328.c"



//set desired baud rate
#define BAUDRATE 1200
//calculate UBRR value
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)


volatile char ReceivedChar = 'A';

int main()
{
	
   lcd_init(LCD_DISP_ON);
   _delay_ms(1000);
   lcd_clrscr();
   _delay_ms(1000);
   _delay_ms(10);
    lcd_puts("lcd.... ");
	_delay_ms(1000);
	 lcd_clrscr();

   USART_init(UBRRVAL);

    sei();	  

	while(1)
	{

	DDRB=0b11111111;
		PORTB=0b00000000;
	}

	lcd_puts("finished");
	_delay_ms(5000);
	return 0;
}


ISR(USART_RX_vect)
{
lcd_clrscr();
	
	ReceivedChar = UDR0;                       // Read data from the RX buffer
	if(ReceivedChar=='F')
	{
	//lcd_puts("here");
		//both wheels move forward
		DDRB=0b11111111;
		PORTB=0b00001010;
	}
    if(ReceivedChar=='B')
	{
		//both wheels move backward
		DDRB=0b00001111;
		PORTB=0b00000101;
	}
    if(ReceivedChar=='L')
	{
		//left wheel -stop
		//right wheel -move frwrd
		DDRB=0b00001111;
		PORTB=0b00000010;
	}
    if(ReceivedChar=='R')
	{
		DDRB=0b00001111;
		PORTB=0b00001000;
	}
    
	 lcd_putc(ReceivedChar);
	 
	_delay_ms(100);
	 
}


/*ISR(USART_TX_vect)
{
lcd_clrscr();
lcd_puts("transmitted");
_delay_ms(100);
}*/
