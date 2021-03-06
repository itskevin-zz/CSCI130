/*
Title: CSCI130 - Lab 2a
Author: Kevin K.D. Nguyen
Date Created: 12/02/2017
Last Modified: 12/02/2017
Pupose: Displays Displays 0 to 255 in binary at 1Hz interval on the I/O
Trainer. When the number reaches 255, loop back to 0.
Connection Diagram:
Atmega328p    Romeo Board   IO Board Jumper   Component
PD2 -->       D2 -->        JP3_1 -->         D1A
PD3 -->       D3 -->        JP3_2 -->         D1B
PD4 -->       D4 -->        JP3_3 -->         D1C
PD5 -->       D5 -->        JP3_4 -->         D1D
PD6 -->       D6 -->        JP3_5 -->         D1E
PD7 -->       D7 -->        JP3_6 -->         D1F
PB0 -->       D8 -->        JP3_7 -->         D1G
PB1 -->       D9 -->        JP3_8 -->         D1H
GND -->                     GND
*/

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void DELAY_us (unit16_t_us_count);
void DELAY_ms (unit16_t_ms_count);

//Declare Gloval Variables
int num = 0;

int main(void) {
  //declare DDRx
  DDRD = 0b11111100;
  DDRB = 0b00000011;

  while (1) {
    num++;
    delay_ms(500);

    PORTD &= 0b00000011;
    PORTD |= num << 2;

    PORTB &= 0b11111100;
    PORTB |= num >> 6;
  }
  return 0;
}

void delay_ms (uint16_t ms) {
	uint16_t i;
	for (i = 0; i < ms; i++)
		_delay_ms(1);

}
