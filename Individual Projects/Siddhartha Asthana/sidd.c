#define F_CPU 16000000UL
#define LOGFILENAME "log.txt"
#define LOG "log1.txt"
#include <stdio.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include "uart.h"
#include "uart.c"
#include "sdcard.c"
#include "fat.c"
#include "fat.h"
#include "sd_raw.c"
#include "sd_raw.h"
#include "partition.c"
#include "partition.h"
#include <avr/sfr_defs.h>
#include <math.h>

int init_sdcard();
int create_file( const char* fname );
int delete_file( const char* fname );
int display_file(const char* fname);
int write_data(const char* fname, unsigned int data);
int write_data_block(const char* fname, uint8_t *data, int length);

int flag=0, freq=200, count=0, time=0;
int main (void)
{ 
 
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz
    ADCSRA |= (1<<ADIE); //Interrupt Enabled
    ADCSRB&=~((1<<ADTS0)|(1<<ADTS1)|(1<<ADTS2)); //interrupt source selected to ADC conversion complete
    ADMUX |= (1 << REFS0); // Set ADC reference to AVCC


   // No MUX values needed to be changed to use ADC0

    ADCSRA |= (1 << ADATE);  
    ADCSRA |= (1 << ADEN);  // Enable ADC
    ADCSRA |= (1 << ADSC);  // Start A2D Conversions

	uart_init();  //Uart initialized
	uart_puts_p(PSTR("Uart initialized\r\n"));

    init_sdcard(); //SDcard initialized
	uart_puts_p(PSTR("SD-CARD  initialized\r\n"));
	delete_file( LOGFILENAME ); //old log deleted
	delete_file( LOG );
	uart_puts_p(PSTR("Deleted prevuoius Log\r\n"));
	while( create_file (LOGFILENAME) != 0 ) //new log created
	while( create_file (LOG) != 0 )   ;
	uart_puts_p(PSTR("New Log Created\r\n"));
	sei(); //enable global interrupt
	uart_puts_p(PSTR("Global interrupt enabled\r\n"));

	while(1)  // Loop Forever 
   	{ 
   	}
        

}


// interrupt handler fuction
ISR (ADC_vect)
{ if (count%freq==0)
	{
		if(flag==0){
			int x=-1;
 			x= ADCL; 
			x |= (ADCH<<8);
    		ADMUX |= 1;
 			uart_putw_dec(x);
			uart_puts_p(PSTR("\r\n"));
			write_data(LOGFILENAME, x);//writing data in file
			write_data(LOGFILENAME, time);
			time++;
			flag=1;
		}
		else if(flag==1){
			int x=-1;
 			x= ADCL; 
			x |= (ADCH<<8);
    		ADMUX &= 254;
 			uart_putw_dec(x);
			uart_puts_p(PSTR("\r\n"));
			write_data(LOG, x);//writing data in file
			write_data(LOG, time); // writting Time stamp
			time++;
			flag=0;
		}
		count=0;
	}
	count++;
}
