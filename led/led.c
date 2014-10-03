/*
 * GccApplication1.c
 *
 * Created: 20-09-2014 22:34:03
 *  Author: Manish
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define sbi(x,y) x |= _BV(y) //set bit - using bitwise OR operator 
#define cbi(x,y) x &= ~(_BV(y)) //clear bit - using bitwise AND operator
#define tbi(x,y) x ^= _BV(y) //toggle bit - using bitwise XOR operator
#define is_high(x,y) (x & _BV(y) == _BV(y)) //check if the y'th bit of register 'x' is high ... test if its AND with 1 is 1

int main(void)
{
	DDRB |= 1 << PINB0; //set pin0 output
	DDRB &= ~(1 << PINB1); // set pin1 input
	DDRB |= (1 << PINB2); // set pin2 output
	DDRB |= (1 << PINB3); // set pin2 output
	DDRB |= (1 << PINB4); // set pin2 output
	
	
	PORTB |= 1 << PINB0;	
	PORTB &= ~(1 << PINB2);
	PORTB |= 1 << PINB3;
	PORTB |= 1 << PINB4;
	
	
	int press = 0;
	while(1){
		if(bit_is_clear(PINB,1)){
		    PORTB |= 1 << PINB3;
			PORTB &= ~(1 << PINB4);
			if(press == 0){
			   PORTB ^= 1 << PINB0; //toggle pin
			   PORTB ^= 1 << PINB2; //toggle pin
			   press = 1;
		   }
		}else{
		   press = 0;
		   PORTB |= 1 << PINB4;
		   PORTB &= ~(1 << PINB3);
		}
	}
}