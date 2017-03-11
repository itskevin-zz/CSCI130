#include <avr/io.h>
#define F_CPU 16000000UL

//initilize ADC
void initADC( ) {
  ADCSRA = (1 << ADEN); // enable ADCSR
  ADMUX = (1 << REFS0) | (1 << ADLAR); // Vref internal connect to AVcc  and set 8 bits
  ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // set prescaler
  ADCSRA = (1 << ADSC); // start conversion
}

//convery analog to digital 10 bits
uint16_t analog( unit8_t channel ) {
  ADMUX &= 0xF0; // clear last 4 bits
  ADMUX |= channel; //select channel
  ADCSRA |= (1 << ADSC); //start conversion
  while (ADCSRA & (1 << ADSC));
  return ADC;
}


// initilize UART

int main(void) {
  //set DDRx,PORTx, etc
  while(1) {
    //application loop
  }
  return 0;
}
