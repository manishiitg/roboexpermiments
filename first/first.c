#include <avr/io.h>
#include <util/delay.h>

int pressed = 0;

int main(void){
   DDRB |= (1 << PINB0 | 1 << PINB2); //set pin0 as output
   DDRB &= ~(1 << PINB1); // set pin1 input
   PORTB |= 1 << PINB0;
   PORTB |= 1 << PINB2;
   while(1){
       if(bit_is_set(PINB,1)){
	      pressed++;
		  if(pressed > 400){
		    //bounce fix
			PORTB = 0b00000001;
			pressed = 0;
		  }
	   }else{
	      pressed = 0;
	      PORTB = 0b00000100;
	   }
   }
}