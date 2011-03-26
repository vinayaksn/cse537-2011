#define F_CPU 16000000UL

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define DEBOUNCE_TIME 25        /* time to wait while "de-bouncing" button */
#define LOCK_INPUT_TIME 250     /* time to wait after a button press */

#define FILENAME "sumit.txt"

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

// from fat main.c
int init_sdcard();
int create_file( const char* fname );
int delete_file( const char* fname );
int display_file(const char* fname);
int write_data(const char* fname, unsigned int data);
int write_data_block(const char* fname, uint8_t *data, int length);

int main (void)
{
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    
   
    ADMUX |= (1 << REFS0);
    ADMUX |= (0 << ADLAR);
   
    ADCSRA |= (1 << ADATE);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADSC);
    unsigned int x=0;
	unsigned int y=0;
	unsigned int z=0;
	unsigned int acc=0;

  	uart_init();
	uart_puts_p(PSTR("SD Off1 \r\n"));

 
   	//init_sdcard();

	uart_puts_p(PSTR("SD Off2 \r\n"));
   	//delete_file( FILENAME );
	uart_puts_p(PSTR("SD Off3 \r\n"));
   //create file

   DDRD=255;
   PORTD=11111111;
   
  
 while (1)
    {
		char str_x[10];
        char str_y[10];
		
		x=0;
		y=0;
		z=0;
		acc=0;

		ADMUX |= (0 << MUX1) | (0 << MUX0)|(0 << MUX2);
	
     // lcd_clrscr();
     // _delay_ms(1000);
        x=ADCL;
        x|=(ADCH<<8);
       
        //x=ADC;
       

		//write_data(FILENAME, x);
		_delay_ms(100);
		uart_puts_p(PSTR("SD Off \r\n"));
	
		x=(((5*x)/1023*0.8)*9.8) - 220;
        sprintf( str_x, "%d", x );
   
        _delay_ms(500);
        
		//lcd_puts(str);
        //_delay_ms(1000);
     	//strcat(str, "\r\n");
    	uart_puts(str_x);
   		uart_puts("x\r\n");
/*
ADMUX = 1;
	
     // lcd_clrscr();
     // _delay_ms(1000);
        y=ADCL;
        y|=(ADCH<<8);
       
        //x=ADC;
       //str=null;

		//write_data(FILENAME, x);
		_delay_ms(100);
		uart_puts_p(PSTR("SD Off \r\n"));

        //str[10];
        y=((5*y)/1023*0.8)*9.8;
        
		sprintf( str_y, "%d", y );
   
        _delay_ms(500);
        
		//lcd_puts(str);
        //_delay_ms(1000);
     	//strcat(str, "\r\n");
    	uart_puts(str_y);
   		uart_puts("y\r\n");
/*
ADMUX = 2;
	
     // lcd_clrscr();
     // _delay_ms(1000);
        z=ADCL;
        z|=(ADCH<<8);
       
        //x=ADC;
       
	
		//write_data(LOGFILENAME, x);
		_delay_ms(100);
		uart_puts_p(PSTR("SD Off \r\n"));

		z=((5*z)/1023*0.8)*9.8;
        
        //str[10];
        sprintf( str, "%d", z );
   
        _delay_ms(500);
        
		//lcd_puts(str);
        //_delay_ms(1000);
     	//strcat(str, "\r\n");
    	uart_puts(str);
   		uart_puts("z\r\n");
*/

	}
	//write_data(LOGFILENAME, 100);
	//uart_puts_p(PSTR("please \r\n"));

}
