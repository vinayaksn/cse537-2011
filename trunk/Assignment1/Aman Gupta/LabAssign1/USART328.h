#ifndef USART_H //if already included don't do it again
#define USART_H

//Declare the prototypes
void  USART_init(unsigned int ubrr);
void USART_Transmit( unsigned char data);
void USART_String(char *s);
unsigned char USART_Receive(void);

#endif
