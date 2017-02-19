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
Atmega328p    Romeo Board     IO Board Jumper     Component
PD2 ->        D2 ->           JP3_1 ->            D1A
PD3 ->        D3 ->           JP3_2 ->            D1B
PD4 ->        D4 ->           JP3_3 ->            D1C
PD5 ->        D5 ->           JP3_4 ->            D1D
PD6 ->        D6 ->           JP3_5 ->            D1E
PD7 ->        D7 ->           JP3_6 ->            D1F
PB0 ->        D8 ->           JP3_7 ->            D1G
PB1 ->        D9 ->           JP3_8 ->            D1H
PB2 ->        D10 ->          JP2_3 ->            DS3
PB3 ->        D11 ->          JP2_2 ->            DS2
PB4 ->        D12 ->          JP2_1 ->            DS1
*/
/*Note : i couldn't get this to work. COuln't read two PINs at once.*/

#include <avr/io.h>
#define F_CPU 16000000UL

void main(void)
{
  DDRD = 0b11111100;  //set PD2-PD7 to output
  DDRB = 0b00000011; //set PB0-PB1 to output and rest to input
  PORTB = 0b00011100; //turn on internal pullups for PB4-PB2

  while (1){
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
}
