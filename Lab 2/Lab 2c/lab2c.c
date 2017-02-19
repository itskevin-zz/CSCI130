/*
Title: CSCI130 - Lab 2b
Author: Kevin K.D. Nguyen
Date Created: 16/02/2017
Last Modified: 16/02/2017
Pupose: Write a C program that uses the 8 LEDs as a binary display and 2
momentary switches as input. The program should keep a count. When one of the
two switches is pressed then released, the count should increase by 1 and if
the other is pressed then released, the count should decrease by 1. The count
should go from 0 to 255 and loop
Connection Diagram:
Atmega328p    Romeo Board   IO Board Jumper   Component

*/

#include <avr/io.h>
#define F_CPU 16000000UL



void main(void)
{
   DDRB = 0xff;   //PORTB output
   PORTB = 0x00;  //PORTB '0'
   DDRD = 0x00;   //PORTD input
   PORTD = 0xff;  //PORTD internall pullup

/*   while(1)
   {
		if(!(PIND & (1<<PD0))) PORTB = PORTD;    //when button pressed, turn ON led
		else PORTB = 0x00; 						    //when not pressed, turn OFF led
  }*/
}
