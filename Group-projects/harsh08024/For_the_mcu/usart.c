#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <util/delay.h>
#include "lcd.c"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>


#define FOSC F_CPU // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void USART_Init( unsigned int ubrr)
{
/*Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;

/*Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
// Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) )
;
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

int semantic(int val,int flag){
int result=-1;
if (flag==0)
	switch(val){
	case 0x00:	PORTB=0b00000000;
	 return 1;

	case 0x10: PORTB=7;
	 return 1;
	case 0x01: PORTB=PORTB^1;
	 return 1;
	case 0x02: PORTB=PORTB^2;
	 return 1;
	case 0x03: PORTB=PORTB^4;
	 return 1;
	case 0x09: //PORTB=0b00000000;
	 return 0;
	 default: return 21;	
	 	}
		else if (flag==1){

	switch(val){
	case 0x00:	PORTB=0b00000000;
	 return 1;

	case 0x10: PORTB=0;
	 return 1;
	case 0x01: PORTB=PORTB&(~1);
	 return 1;
	case 0x02: PORTB=PORTB&(~2);
	 return 1;
	case 0x03: PORTB=PORTB&(~4);
	 return 1;
	case 0x09: //PORTB=0b00000000;
	 return 0;
	 default: return 21;	
	 	}	
		}
	return result;
 }

int main( void )
{
unsigned char ch;
char arr[10];
ch=22;
int valRec;
DDRB=0b11111111;
PORTB=0;
USART_Init(MYUBRR);
					//lcd_init(LCD_DISP_ON);
    				//lcd_clrscr();  _delay_ms(50);
		
				//lcd_puts("here");    
				//_delay_ms(1000);

while(1){

				//lcd_puts("in");    
				//_delay_ms(50);

ch=USART_Receive();
    //lcd_clrscr();  _delay_ms(50);
	if (ch=='n'){
	ch=USART_Receive();
valRec=semantic(ch,1);
	}else
valRec=semantic(ch,0);
if (valRec==0){

				//lcd_puts("out");    
				//_delay_ms(50);

USART_Transmit(PORTB);
}
				//sprintf(arr,"%u ",ch);

					//lcd_puts(arr);    
				//_delay_ms(50);
	
	}
}
