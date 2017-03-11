#include <avr/io.h>
#define F_CPU 16000000UL

//convery analog to digital 10 bits
uint16_t analog(uint8_t channel) {
  ADMUX &= 0xF0; // clear last 4 bits
  ADMUX |= channel; //select channel
  ADCSRA |= (1 << ADSC); //start conversion
  while (ADCSRA & (1 << ADSC));
  return ADC;
}

//initilize ADC
void initADC() {
  ADCSRA = (1 << ADEN); // enable ADCSR
  ADMUX = (1 << REFS0); // Vref internal connect to AVcc
  ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // set prescaler
  ADCSRA = (1 << ADSC); // start conversion
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
    int main(void) {
      uint16_t pot_result; //create variable to store pot result
      initADC(); //initilize ADC
      initUART(2400);

      // initialize Ports, DDR
      DDRC = 0x00; //set all PBx to input
      PORTC = 0b1111111; //set PB0 and PB1 internal pullups
      while(1) {
        //application loop
        pot_result = analog(0);
        transmitByte(pot_result);
      }
      return 0;
    }
