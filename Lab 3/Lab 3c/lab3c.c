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
PB1 ->        D09 ->          JP2_4 ->            DS4
PB2 ->        D10 ->          JP2_3 ->            DS3
PB3 ->        D11 ->          JP2_2 ->            DS2
PB4 ->        D12 ->          JP2_1 ->            DS1
*/

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void DELAY_ms (unit16_t_ms_count);

int main(void) {
  initUART(2400);
  DDRB = 0b00000000; //set to input
  PORTB = 0b11111111; //turn on internal pullups

  while(1) {
    if((PINB & 0b00000100) == 0) {
      PORTD = 0b00000100;
    } else if ((PINB & 0b00001000) == 0) {
      PORTD = 0b00001100;
    } else if ((PINB & 0b00010000) == 0) {
      PORTD = 0b00111100;
    } else if ((PINB & 0b00001100) == 0) {
      PORTD = 0b00011100;
    } else if ((PINB & 0b00011000) == 0) {
      PORTD = 0b11111100;
    } else if ((PINB & 0b00010100) == 0){
      PORTD = 0b01111100;
    } else if ((PINB & 0b00011100) == 0){
      PORTD = 0b11111100;
      PORTB = 0b00011110;
    } else {
      PORTD = 0b00000000;
      PORTB = 0b00011100;
    }
  }
  return 0;
}

void printDec(int num) {
  int n = num;
  char ascii[10];
  utoa(n,ascii, 10);
  transmitByte(ascii);
}s

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

    }
