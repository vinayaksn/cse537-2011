#define F_CPU 16000000UL

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define DEBOUNCE_TIME 25        /* time to wait while "de-bouncing" button */
#define LOCK_INPUT_TIME 250     /* time to wait after a button press */

#define FILENAME "vibration.txt"

#include <stdio.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include "delay_x.h"
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


int init_sdcard();
int create_file( const char* fname );
int delete_file( const char* fname );
int display_file(const char* fname);
int write_data(const char* fname, unsigned int data);
int write_data_block(const char* fname, uint8_t *data, int length);

int main (void)
{
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADMUX |= (0 << MUX1) | (0 << MUX0)|(0 << MUX2);
   
    ADMUX |= (1 << REFS0);
    ADMUX |= (0 << ADLAR);
   
    ADCSRA |= (1 << ADATE);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADSC);
    unsigned int x=0;
	unsigned int counter=0;

  	uart_init();
	uart_puts_p(PSTR("uart initialised \r\n"));

 
   	init_sdcard();

	uart_puts_p(PSTR("MicroSDcard initialised \r\n"));
   	delete_file( FILENAME );

	uart_puts_p(PSTR("A new file will be created\r\n"));
   

   DDRD=255;
   PORTD=11111111;
   
   while( create_file (FILENAME) != 0 )
	   ;


	   /*write_data(FILENAME, 50);
	uart_puts_p(PSTR("please \r\n"));
	write_data(FILENAME, 54);
	uart_puts_p(PSTR("please \r\n"));
	write_data(FILENAME, 58);
	uart_puts_p(PSTR("please \r\n"));
	write_data(FILENAME, 19);
	uart_puts_p(PSTR("please \r\n"));
	write_data(FILENAME, 20);
	uart_puts_p(PSTR("please \r\n"));
	*/


 while (1)
    {

     
        x=ADCL;
        x|=(ADCH<<8);
       
        
		write_data(FILENAME, x);
		_delay_ms(100);
		uart_puts_p(PSTR("SD Off \r\n"));

        //char str[10];
        //sprintf( str, "%d", x );
   
        //_delay_ms(500);
        
		
     	//strcat(str, "\r\n");
    	//uart_puts(str);
   		//uart_puts("\r\n");

	}
	write_data(FILENAME, 100);
	uart_puts_p(PSTR("junk last value written \r\n"));

}

