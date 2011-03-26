#define F_CPU 16000000UL

#define BAUD 9600UL
#define MYUBRR F_CPU/16/BAUD-1

#include <stdio.h>
#include <avr/io.h>
#include "delay_x.h"
#include "USART328.c"

unsigned long i;

int main()
{

USART_init(MYUBRR);
char buf[1024];
char c;

//to test
char *s = "    abcdefghijklmnopqrstuvwxyz    abcdefghijklmnopqrstuvwxyz    abcdefghijklmnopqrstuvwxyz";

for(;;)
{
	sprintf( buf, "%5ld %s\r\n", ++i, s );
	USART_String( buf );

	c=USART_Receive();
	sprintf( buf, "received : %c\r\n", c );
	USART_String( buf );

//	_delay_ms(200);
}



/*
while(1)
{

	USART_String( "\r\nread a byte\r\n" );
	c=USART_Receive();
	_delay_ms(2);

	USART_String( "\r\nwrite a byte\r\n" );
  	USART_Transmit(c);
  	_delay_ms(200);
}
*/

return 0;
}

