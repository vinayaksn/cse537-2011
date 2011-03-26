


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
	
  DDRC = 0b00100000;
  PORTC =0b00100000;
   USART_init(UBRRVAL);

 sei();	  

while(1)
{

	if((PINC & (0b00000001))==1)
	{
	USART_Transmit('F' );
	//ReceivedChar++;
	}

	if((PINC & (0b00000010))==(0b00000010))
	{
	USART_Transmit('B' );
	//ReceivedChar++;
	}

	if((PINC & (0b00000100))==(0b00000100))
	{
	USART_Transmit('L' );
	//ReceivedChar++;
	}
	
		if((PINC & (0b00001000))==(0b00001000))
	{
	USART_Transmit('R' );
	//ReceivedChar++;
	}

}
//	lcd_puts("finished");
	_delay_ms(5000);
	return 0;
}


ISR(USART_RX_vect)
{
//lcd_clrscr();
	
	ReceivedChar = UDR0;                       // Read data from the RX buffer
  //   lcd_putc(ReceivedChar);
	ReceivedChar++;
}

ISR(USART_TX_vect)
{
DDRC=0b11111111;
PORTC=0b11111111;
_delay_ms(2000);
PORTC=0b00000000;

}
