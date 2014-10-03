#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



ISR(INT0_vect){
   //press++;
   //if(press > 200){
       //software debouce
	   PORTB ^= 1 << PINB0;
	//   press = 0;
   //}
   
}
int press = 0;
int main(void){

   DDRB |= (1 << PINB0); //set pin0 as output
   PORTB |= 1 << PINB0;
   DDRD=0b11100111; //interrupt pins inputs, rest outputs

   cli();  //clear global interrupts
   GICR = 1 << INT0; //enable intrupt on INT0
   SREG = 1 << 7;
   //MCUCR = 1<<ISC01 | 1<<ISC00;  // on rising edge
   
   MCUCR = 1<<ISC01 | 0<<ISC00;  // on rising edge
   
   sei(); //enable global interrupts
   
   while(1){
   }
   

}