/*
Title: CSCI130 - Lab 2a
Author: Kevin K.D. Nguyen
Date Created: 12/02/2017
Last Modified: 12/02/2017
Pupose: Displays Displays 0 to 255 in binary at 1Hz interval on the I/O
Trainer. When the number reaches 255, loop back to 0.
Connection Diagram:
Atmega328p        Romeo Board       IO Board Jumper       Component
*/

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void DELAY_us (unit16_t_us_count);
void DELAY_ms (unit16_t_ms_count);

int main(void) {
  //declare DDRx
  DDRD = 0b11111100; /* (1<<2)|(1<<3)}(1<<4)|(1<<5)|(1<<6)|(1<<7); */
  DDRB = 0b00000111;
}
