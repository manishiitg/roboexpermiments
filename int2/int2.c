#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


ISR(INT2_vect){
	PORTB ^= 1 << PINB3;
}
ISR(INT1_vect){
	PORTB ^= 1 << PINB1;
}
ISR(INT0_vect){
	PORTB ^= 1 << PINB0;
   
}
int main(void){

   DDRB |= ((1 << PINB0) | (1 << PINB1) | (1 << PINB3)); //set pin0 as output
   DDRB &= ~(1 << PINB2);
   DDRD=0b11001111; //interrupt pins inputs, rest outputs

   cli();  //clear global interrupts
   GICR = (1 << INT0 | 1 << INT1 | 1 << INT2); //enable intrupt on INT0
   SREG = 1 << 7;
   //MCUCR = 1<<ISC01 | 1<<ISC00;  // on rising edge
   
   MCUCR = (1<<ISC01 | 0<<ISC00 | 1 << ISC11 | 1 << ISC10 | 1 << ISC2);  // on rising edge
   
   sei(); //enable global interrupts
   
   while(1){
   }
   

}