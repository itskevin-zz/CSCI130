/*
Title: CSCI130 - Lab 3a
Author: Kevin K.D. Nguyen
Date Created: 04/03/2017
Last Modified: 04/03/2017
Pupose: the program will read two momentary switches and used them to increase
or decrease a count by 1. The count can go from -9999 to 9999. The decimal
representation of the count will be output on the serial command. The program
will only display a new number when there is an increment or decrement in the count.
Connection Diagram:
Atmega328p    Romeo Board   IO Board Jumper   Component
PB2 ->        D10 ->          JP2_8 ->            S4
PB3 ->        D11 ->          JP2_6 ->            S2
GND -->                     GND
*/

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void DELAY_ms (unit16_t_ms_count);

int main(void) {
  initUART(2400);
  //declare DDRx
  DDRB = 0x00; //set all PBx to input
  PORTB = 0b1111111; //set PB0 and PB1 internal pullups
  int num = 0;
  while(1) {
        if ((PINB & 0b0000100) == 0) { //check if s4 is pressed
          delay_ms(100); //Provides required delay
          if ((PINB & 0b0000100) == 0) {
            num++;  //add 1 to n
            printDec(num);
          }
        } else if ((PINB & 0b0001000) == 0) { //check if s2 is pressed
          delay_ms(100); // delay_ms
          if ((PINB & 0b0001000) == 0) {
            num--;
            printDec(num);
          }
        }
  }
  return 0;
}

//function for counting printDec
void printDec(int num) {
  if (num <= 10) {
    char c = num + '0';
    transmitByte(c);
  } else if (num >= 10) {
    char n = num + 'A';
    transmitByte(n);
  }
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
      UDR0 = data;
      // Start transmission by writing to UDR0 register
    }

    void delay_ms (uint16_t ms) {
    	uint16_t i;
    	for (i = 0; i < ms; i++)
    		_delay_ms(1);

    }
