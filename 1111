#include <avr/io.h>
#include <util/delay.h>

int pressedButton[2];
int releaseButton[2];
int ledLevel[2];
int processButton[2];



void blinkAll(int buttonType){
	if(buttonType == 0){
	    PORTB = 0b00000000;
		_delay_ms(20);
		PORTB = 0b11111111;
		_delay_ms(20);
		PORTB = 0b00000000;
		_delay_ms(20);
		PORTB = 0b11111111;
		_delay_ms(20);
		PORTB = 0b00000000;
		_delay_ms(20);
		PORTB = 0b11111111;
		_delay_ms(20);
		PORTB = 0b00000000;
		_delay_ms(20);
		PORTB = 0b11111111;
		_delay_ms(20);
		PORTB = 0b00000000;
	}else{
	    PORTA = 0b00000000;
		_delay_ms(20);
		PORTA = 0b11111111;
		_delay_ms(20);
		PORTA = 0b00000000;
		_delay_ms(20);
		PORTA = 0b11111111;
		_delay_ms(20);
		PORTA = 0b00000000;
		_delay_ms(20);
		PORTA = 0b11111111;
		_delay_ms(20);
		PORTA = 0b00000000;
		_delay_ms(20);
		PORTA = 0b11111111;	
		_delay_ms(20);
		PORTA = 0b00000000;	
		
	}
	
}


void processButtonPressed(int buttonType){
    if(processButton[buttonType] == 1){
		pressedButton[buttonType]++;
		if(pressedButton[buttonType] > 200){
			if(ledLevel[buttonType] >= 8){
				ledLevel[buttonType] = 1;
				blinkAll(buttonType);
			}else{
				if(buttonType == 0){		    
					PORTB |= 1 << ledLevel[buttonType];
					ledLevel[buttonType]++;	
				}else{
					PORTA |= 1 << ledLevel[buttonType];
					ledLevel[buttonType]++;
				}
			}
			pressedButton[buttonType] = 0;
			processButton[buttonType] = 0;
		}
	}

}

void processButtonReleased(int buttonType){
	releaseButton[buttonType]++;
	if(releaseButton[buttonType] > 200){
	   pressedButton[buttonType] = 0;
	   releaseButton[buttonType] = 0;
	   processButton[buttonType] = 1;
	}
}

void resetAll(){

    PORTB = 0b00000000;  //initalize all pins to low
	PORTA = 0b00000000;  //initalize all pins to low
	
	ledLevel[0] = 1;
	ledLevel[1] = 1;
	pressedButton[0] = 0;
	pressedButton[1] = 0;
	releaseButton[0] = 0;
	releaseButton[1] = 0;
	processButton[0] = 1;
	processButton[1] = 1;
	blinkAll(0);
	blinkAll(1);
}

int main(void){


    DDRB = 0b11111110;  //set direction register for portb
	DDRA = 0b11111110;  //set direction register for porta
	DDRD &= ~(1 << PINB0); // set pin1 input
	
	PORTB = 0b00000000;  //initalize all pins to low
	PORTA = 0b00000000;  //initalize all pins to low
	
	resetAll();

	while(1){
	
	    if(bit_is_set(PIND,0)){
		   resetAll();
		   //3Push Button to Restet
		}
		
		if(bit_is_set(PINB,0)){
		   processButtonPressed(0);
		   //1Push Button is Pressed
		
		}else{
		   processButtonReleased(0);
		   //1Push Button is Released
		   
		}
		
		if(bit_is_set(PINA,0)){
		   processButtonPressed(1);
		   //2Push Button is Pressed
		
		}else{
		   processButtonReleased(1);
		   //2Push Button is Released
		   
		}
		
		
	}
}