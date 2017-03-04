/*
Title: CSCI130 - Lab 3a
Author: Kevin K.D. Nguyen
Date Created: 04/03/2017
Last Modified: 04/03/2017
Pupose: Write a C program that waits for input from the serial terminal, when an
input is received, transmit the next character on the ASCII table on a new line.
For Example:
Input: A
Output: B
Input: s
Output: t
*/


#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void) {
  initUART(2400);
  while (1)
    {
      transmitByte();
    }
	return 0;
}

//Initialize settings for UART
void initUART(unsigned int baud) {
    unsigned int ubrr = F_CPU/8/baud-1;
    // shift MSB and store in UBRR0H
    UBRR0H = (unsigned char) (ubrr >> 8);
   // store LSB in UBRR0L
    UBRR0L = (unsigned char) ubrr;
    // enable double speed mode
    UCSR0A = (1 << UDRE0) | (1 << U2X0);
    // Enable transmitter/receiver
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    //8-Bit Characters, 0 Stop bits, No parity
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
  }

    // Read byte from UART
    unsigned char receiveByte ( void ) {
       while ( !(UCSR0A &  (1 << RXC0)) );
       // Wait for incoming byte
       return UDR0;
       // Return the byte
    }

   // Write byte to UART
    void transmitByte (unsigned char data) {
      while ( !(UCSR0A & (1 << UDRE0)) );
      // Wait for empty transmit buffer
      UDR0 = receiveByte() + 1;
      // Start transmission by writing to UDR0 register
    }
