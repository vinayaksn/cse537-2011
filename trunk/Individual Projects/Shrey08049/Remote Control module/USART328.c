#include<avr/io.h>
#include "USART328.h"


void USART_init(unsigned int ubrr) //see the value of baud from the datasheet
{
	/*Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;

/* Set frame format: 8data, 2stop bit */
//UCSR0C = (1<<USBS0)|(3<<UCSZ00);
UCSR0C=(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(0<<UCSZ02)|(1<<UCSZ01)|(1<<UCSZ00);	
/*Enable receiver and transmitter */

UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);

}


void USART_Transmit( unsigned char data)//Transmit a data byte
{
	/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );

/* Put data into buffer, sends the data */
UDR0 = data;

}

unsigned char USART_Receive( void )
{

/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) )
;
/* Get and return received data from buffer */
return UDR0;

}




void USART_String(char *s)
{
	while(*s)
	{
	USART_Transmit(*s);
	s++;
	}

}


