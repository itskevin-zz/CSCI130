/*
Title: CSCI130 - Lab 2c
Author: Kevin K.D. Nguyen
Date Created: 16/02/2017
Last Modified: 16/02/2017
Pupose: Write a C program that uses the 8 LEDs as a binary display and 2
momentary switches as input. The program should keep a count. When one of the
two switches is pressed then released, the count should increase by 1 and if the
other is pressed then released, the count should decrease by 1. The count should
go from 0 to 255 and loop back
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
PB2 ->        D10 ->          JP2_8 ->            S4
PB3 ->        D11 ->          JP2_6 ->            S2
*/
/*Note : i couldn't get this to work. the var num didn't seem to be assigned
once in the do-while loop*/

#include <avr/io.h>
#define F_CPU 16000000UL

void main(void) {
  //declare n counter

  //declare DDRx
  DDRD = 0b11111100;  //set PD2-PD7 to output
  DDRB = 0b00000011; //set PB0-PB1 to output and rest to input
  PORTB = 0b00001100; // set internal pullups in PB2 and PB3 turn PB0 and PB1 off
  PORTD = 0b00000000;
  //declare num counter
 int num = 0;

  do {

    if ((PINB & 0b0000100) == 0) { //check if s4 is pressed
      num++;  //add 1 to n i.e. n = 1 on first loop
      PORTD &= 0b0000011; //clear bits 7 - 2
      PORTD |= (num << 2);  //shift bits

      PORTB &= 0b11111100; //clear bits 1 - 0
      PORTB |= (num >> 6);  //shit bits
    } else if ((PINB & 0b0001000) == 0) { //check if s2 is pressed
      num--; //minus 1 to n
      PORTD &= 0b00000011; //clear bits
      PORTD |= (num << 2); //shift bits

      PORTB &= 0b11111100;
      PORTB |= (num >> 6);
    }
  } while(1);
  return 0;
}
