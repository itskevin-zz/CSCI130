/*
Title: CSCI130 - Lab 2c
Author: Kevin K.D. Nguyen
Date Created: 16/02/2017
Last Modified: 16/02/2017
Pupose: Write a C program that uses the 8 LEDs as a number display and 3 DIP
switches as input. The program should read in the state of the 3 DIP switches
as a binary number where SW1_1 is the most significant bit and SW1_3 is the
least significant bit.
For example if SW1_1 = ON, SW1_2 = ON, SW1_3 = OFF then the number interpreted
by the program should be 0b00000110 = 6
Connection Diagram:
Atmega328p    Romeo Board   IO Board Jumper   Component

*/

#include <avr/io.h>
#define F_CPU 16000000UL



void main(void)
{
  //set all pins on PORTB to output
  DDRB = 0xff;

  //set PD2 on PORTD to input an leaves other pins untouched
  DDRD &= ~(1 << PD2);

  while (1)
  {
    if (PIND & (1<<PD2))
      PORTB |= (1<<PB2);
    else
    PORTB &= ~(1<<PB2);
  }
  return 0;
}
