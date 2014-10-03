#include <avr/io.h>
#include <util/delay.h>

int pressedButton[2];  //checking bouce for button Pressed
int releaseButton[2];  //checking bouce for button Released
int processButton[2];  //variable to prevent multiple processing

void processButtonPressed(int buttonType){
	pressedButton[buttonType]++;
	if(pressedButton[buttonType] > 200){
	    //bounce fix, checking 200 times
		if(processButton[buttonType] == 1){
		    //if function is called, don't call it again till button is released
			pressedButton[buttonType] = 0; //reset variable
			processButton[buttonType] = 0; //reset variable
			
			//do LED Processing
			
			if(ledLevel[buttonType] >= 8){
			     // if all LEDs are lit up blink All and reset LED Level
				ledLevel[buttonType] = 1;
				blinkAll(buttonType);
			}else{
				if(buttonType == 0){		    
					PORTB |= 1 << ledLevel[buttonType];
					//shift LED by level
					ledLevel[buttonType]++;	
				}else{
					PORTA |= 1 << ledLevel[buttonType];
					ledLevel[buttonType]++;
					//shift LED by level
				}
			}
		}
	}

}

void processButtonReleased(int buttonType){
	releaseButton[buttonType]++;
	if(releaseButton[buttonType] > 200){
	   //bounce fix
	   pressedButton[buttonType] = 0;  //reset variable
	   releaseButton[buttonType] = 0;  //reset variable
	   processButton[buttonType] = 1;  //reset variable
	}
}

int main(void){


    DDRB = 0b11111110;  //set direction register for portb
	DDRA = 0b11111110;  //set direction register for porta
	
	PORTB = 0b00000000;  //initalize all pins to low
	PORTA = 0b00000000;  //initalize all pins to low
	

	while(1){
	
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