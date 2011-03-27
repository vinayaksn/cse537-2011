#define F_CPU 16000000UL

//#define BAUD 9600
//#define MYUBRR F_CPU/16/BAUD-1

#define LOGFILENAME "log.txt"

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
#include <math.h>

int init_sdcard();
int create_file( const char* fname );
int delete_file( const char* fname );
int display_file(const char* fname);
int write_data(const char* fname, unsigned int data);
int write_data_block(const char* fname, uint8_t *data, int length);

double sum=0,temp=0;
int j=0,k=0;

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
	uart_puts_p(PSTR("Deleted prevuoius Log\r\n"));
	while( create_file (LOGFILENAME) != 0 ) //new log created
	   ;
	uart_puts_p(PSTR("New Log Created\r\n"));
	 sei(); //enable global interrupt
	 uart_puts_p(PSTR("Global interrupt enabled\r\n"));

while(1)  // Loop Forever 
   { 
   }
        		 
			//	_delay_ms(100);
			//	  uart_puts_p(PSTR("SD Off \r\n"));

}


// interrupt handler fuction
ISR (ADC_vect)
{
	int x=-1;
 	x= ADCL; 
	x |= (ADCH<<8);

  
  	sum=sum+ (x-512)* (x-512); //square
	j++;
//	uart_putw_dec(j);
	//uart_puts_p(PSTR("\r\n"));

  if(j==192)
  {
 //  uart_puts_p(PSTR("one rms done\r\n"));
	  k++;

	sum=sum/(double)192; //mean
	sum=sqrt(sum);  //root //rms
	//sum=sum-2;
	sum=sum *27 *220; //current in mA * Voltage
	sum=sum/1000;     //power in Watt
//	char buf1[10];
//	sprintf( buf1, "%d\n", (int)sum);
//	 uart_puts(buf1);
//	  uart_puts_p(PSTR("\r\n"));
	//x=sum;
	temp=temp+sum;
	sum=0;
	j=0;
  if(k==50)
  {

  temp=temp/50; //power averaged to get 1 value in 1 sec
  k=0;
  	//char buf[10];
	//sprintf( buf, "%d\n", (int)temp);
	//uart_puts(buf);
	//
	uart_putw_dec(temp);
	uart_puts_p(PSTR("\r\n"));
	write_data(LOGFILENAME, temp);//writing data in file
	temp=0;

}
}
	                                                                
}

