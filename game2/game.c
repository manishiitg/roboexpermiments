#include <avr/io.h>
#include <util/delay.h>

int buttonGamePressed = 0;
int ledLight = 1;
int i = 1;

void startLedSeq(){
 
    for(i = 1;i<=16;i++){
	    legLight = i;
		if(i > 8){
		   ledLight = i - 8;
		    PORTC = 1 << ledLight;
		}else{
			PORTB = 1 << ledLight;
		}
		_delay_ms(100);
	}
}

void checkGameStart(){
    buttonGamePressed++;
    if(buttonGamePressed > 300){
		buttonGamePressed = 0;
		startLedSeq();
	}
}

int main(void){
   
   DDRA = 0xff;
   DDRC = 0xff;
   
   DDRB &=  (~(1 << PINB0) | ~(1 << PINB1)); // set pin1 input for speed and pin2 for respond
   
   while(1){
       
	   if(bit_is_set(PINB,0){
	      
		  checkGameStart();
	   
	   }else{
	   
	   }
	   
   }
}