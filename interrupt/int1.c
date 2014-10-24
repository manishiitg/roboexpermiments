#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

ISR(INT0_vect){
	PORTB ^= 1 << PINB0;
	_delay_ms(50); //debouce so that ISR is not called many times in a single button press
}

int main(void){

   DDRB |= (1 << PINB0); //set pin0 as output
   PORTB |= 1 << PINB0;
   DDRD=0b11100111; //interrupt pins inputs, rest outputs

   cli();  //clear global interrupts
   GICR = 1 << INT0; //enable intrupt on INT0
   SREG = 1 << 7;
   
   MCUCR = 1<<ISC01 | 1 <<ISC00;  // on rising edge
   
   sei(); //enable global interrupts
   
   while(1){
   
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
	  }
   }
   

}