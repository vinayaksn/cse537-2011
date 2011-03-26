#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>

#define BAUD_RATE 19200

// SPI I/O
#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define SPI_CS   PORTB2

// Wiznet W5100 (Ehternet Shield) OpCode
//Page-61
#define WIZNET_WRITE_OPCODE 0xF0
#define WIZNET_READ_OPCODE 0x0F

// Wiznet W5100 Register Addresses initialized with starting addresses
// Datasheet page-14 (names) + page-20(addresses)
#define MR   0x0000   // Mode Register
#define GAR  0x0001   // Gateway Address://-- 0x0001 to 0x0004
#define SUBR 0x0005   // Subnet mask Address://-- 0x0005 to 0x0008
#define SAR  0x0009   // Source hardware address (MAC) //--: 0x0009 to 0x000E
#define SIPR 0x000F   // Source IP Address://-- 0x000F to 0x0012
#define RMSR 0x001A   // RX Memory Size Registe r
#define TMSR 0x001B   // TX Memory Size Register

void uart_init(void)
{
  UBRR0H = (((F_CPU/BAUD_RATE)/16)-1)>>8;	// set baud rate
  UBRR0L = (((F_CPU/BAUD_RATE)/16)-1);
  UCSR0B = (1<<RXEN0)|(1<<TXEN0); 		// enable Rx & Tx
  UCSR0C=  (1<<UCSZ01)|(1<<UCSZ00);  	       // config USART; 8N1
}

void uart_flush(void)
{
  unsigned char dummy;

  while (UCSR0A & (1<<RXC0)) dummy = UDR0;
}

int uart_putch(char ch,FILE *stream)
{
   if (ch == '\n')
    uart_putch('\r', stream);

   while (!(UCSR0A & (1<<UDRE0)));
   UDR0=ch;

   return 0;
}

int uart_getch(FILE *stream)
{
   unsigned char ch;

   while (!(UCSR0A & (1<<RXC0)));
   ch=UDR0;  

   /* Echo the Output Back to terminal */
   uart_putch(ch,stream);       

   return ch;
}

void ansi_cl(void)
{
  // ANSI clear screen: cl=\E[H\E[J
  putchar(27);
  putchar('[');
  putchar('H');
  putchar(27);
  putchar('[');
  putchar('J');
}

void ansi_me(void)
{
  // ANSI turn off all attribute: me=\E[0m
  putchar(27);
  putchar('[');
  putchar('0');
  putchar('m');
}

void SPI_Write(unsigned int addr,unsigned char data)
{
  // Activate the CS pin
  SPI_PORT &= ~(1<<SPI_CS);

  // Start Wiznet W5100 Write OpCode transmission
  //SPDR contains the value that has to be transmitted
  SPDR = WIZNET_WRITE_OPCODE;

  // Wait for transmission complete
  while(!(SPSR & (1<<SPIF)));

  // Start Wiznet W5100 Address High Bytes transmission
  SPDR = (addr & 0xFF00) >> 8;

  // Wait for transmission complete
  while(!(SPSR & (1<<SPIF)));

  // Start Wiznet W5100 Address Low Bytes transmission
  SPDR = addr & 0x00FF;

  // Wait for transmission complete
  while(!(SPSR & (1<<SPIF)));   

  // Start Data transmission
  SPDR = data;

  // Wait for transmission complete
  while(!(SPSR & (1<<SPIF)));

  // CS pin is not active
  SPI_PORT |= (1<<SPI_CS);
}


void W5100_Init(void)
{
  // Ethernet Setup
  unsigned char mac_addr[] = {0x00,0x16,0x36,0xDE,0x58,0xF6};
  unsigned char ip_addr[] = {192,168,1,10};
  unsigned char sub_mask[] = {255,255,255,0};
  unsigned char gtw_addr[] = {192,168,1,1};

  // Setting the Wiznet W5100 Mode Register: 0x0000
  SPI_Write(MR,0x80);            // MR = 0b10000000;
  _delay_ms(1);


  // Setting the Wiznet W5100 Gateway Address (GAR): 0x0001 to 0x0004
  SPI_Write(GAR + 0,gtw_addr[0]);
  SPI_Write(GAR + 1,gtw_addr[1]);
  SPI_Write(GAR + 2,gtw_addr[2]);
  SPI_Write(GAR + 3,gtw_addr[3]);
  _delay_ms(1);

  // Setting the Wiznet W5100 Source Address Register (SAR): 0x0009 to 0x000E
  SPI_Write(SAR + 0,mac_addr[0]);
  SPI_Write(SAR + 1,mac_addr[1]);
  SPI_Write(SAR + 2,mac_addr[2]);
  SPI_Write(SAR + 3,mac_addr[3]);
  SPI_Write(SAR + 4,mac_addr[4]);
  SPI_Write(SAR + 5,mac_addr[5]);
  _delay_ms(1);

  // Setting the Wiznet W5100 Sub Mask Address (SUBR): 0x0005 to 0x0008
  SPI_Write(SUBR + 0,sub_mask[0]);
  SPI_Write(SUBR + 1,sub_mask[1]);
  SPI_Write(SUBR + 2,sub_mask[2]);
  SPI_Write(SUBR + 3,sub_mask[3]);
  _delay_ms(1);

  // Setting the Wiznet W5100 IP Address (SIPR): 0x000F to 0x0012
  SPI_Write(SIPR + 0,ip_addr[0]);
  SPI_Write(SIPR + 1,ip_addr[1]);
  SPI_Write(SIPR + 2,ip_addr[2]);
  SPI_Write(SIPR + 3,ip_addr[3]);
  _delay_ms(1);

  // Setting the Wiznet W5100 RX and TX Memory Size, we use 2KB for Rx/Tx 4 channels
  SPI_Write(RMSR,0x55);
  SPI_Write(TMSR,0x55);

}

// Assign I/O stream to UART
FILE uart_str = FDEV_SETUP_STREAM(uart_putch, uart_getch, _FDEV_SETUP_RW);

int main(void){
  // Set the PORTD as Output:
  DDRD=0xFF;
  PORTD=0x00;

   // Define Output/Input Stream
  stdout = stdin = &uart_str;

  // Initial UART Peripheral
  uart_init();

  // Clear Screen
  ansi_me();
  ansi_cl();
  ansi_me();
  ansi_cl();
  uart_flush();

  // Initial the AVR ATMega328 SPI Peripheral
  // Set MOSI (PORTB3),SCK (PORTB5) and PORTB2 (SS) as output, others as input
  SPI_DDR = (1<<PORTB3)|(1<<PORTB5)|(1<<PORTB2);

  // CS pin is not active
  SPI_PORT |= (1<<SPI_CS);

  // Enable SPI, Master Mode 0, set the clock rate
  SPCR = (1<<SPE)|(1<<MSTR);
  SPSR |= (1<<SPI2X);

  // Initial the Wiznet W5100
  W5100_Init();

  // Loop forever
  for(;;){
  	//sockets here
  }
  return 0;
}

