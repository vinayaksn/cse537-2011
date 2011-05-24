#ifndef _ADC_H_
#define _ADC_H_ 1

/*
#include <inttypes.h>
#ifndef F_CPU
# warning "Macro F_CPU must be defined"
#endif
*/

#include <stdio.h>
#include <avr/io.h>
#include "delay_x.h"
//#include "USART328.c"
#include <avr/interrupt.h>
#include <math.h>

volatile double number_of_samples = 192 ;  // ADC clock / (AC current freq * Cycles for 1 ADC ) 
volatile double sensor_sensitivity = 185 ; // in mV/ A
volatile unsigned long adc_sum = 0;
volatile int adc_tick = 0 ;
volatile unsigned long temp1;
volatile unsigned long temp2;
volatile  double f1;
volatile  double f2;

char buf[20];
volatile unsigned int data, addr, eeprom_addr = 0;
//unit16_t data[E2END]

void adc_init()
{

   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz
   ADCSRA |= (1<<ADIE);
   ADCSRB&=~((1<<ADTS0)|(1<<ADTS1)|(1<<ADTS2));
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC


   // No MUX values needed to be changed to use ADC0

   ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
   ADCSRA |= (1 << ADEN);  // Enable ADC
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions
//  / sei();
}


void EEPROM_write(unsigned int data)
{
    eeprom_write_word( (uint16_t*)eeprom_addr, data );
    sprintf( buf, "EEPROM RW %3d @ %d\r\n", data, eeprom_addr  );
    uart_puts(buf);

    eeprom_addr += sizeof(data);

  if( eeprom_addr > E2END )
  {
 	 uart_puts_p(PSTR("Writing data to SDcard..\r\n"));
 	 for(addr=0; addr<=E2END; addr += sizeof(data) )
 	 {
 		 data = eeprom_read_word((uint16_t*)addr);
 		 write_data(LOGFILENAME, data );
 	 }
 	 //write_data_block(LOGFILENAME, eeprom_data, E2END+1 );
 	 uart_puts_p(PSTR("..Done!\r\n"));
 	 //_delay_s(1);
 	 eeprom_addr = 0;
  }


}

//adc isr for CT sensor
ISR (ADC_vect)
{
       
        adc_sum = adc_sum + (ADC-512)*(ADC-512);
      	adc_tick++;

       if(adc_tick==number_of_samples)
       {   
          //USART_Transmit('a');
          //temp1= adc_sum  / number_of_samples;
          //temp1 = sqrt(temp1);
		  //temp2 = temp1*100*26;

		  f1 = ((double)(adc_sum))/number_of_samples;
		  f1 = sqrt(f1);
		  f2 = f1 * 2639.35810810811;
  
		  //sprintf( buf, "%03ld \t %03ld\r\n",temp2, (long)f2 );
          	  //USART_String("Squared value is ");

		  //sprintf( buf, "%03d\r\n", (int)(f2/100));
		  //uart_puts(buf);

		  EEPROM_write((int)(f2/100));

          adc_tick=0;
          adc_sum=0;
             }  
 
   

 }



#endif /* _AVR_DELAY_X_H_ */
