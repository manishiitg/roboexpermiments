#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int buttonGamePressed = 0;
int ledStarted = 0;
int ledLight = 1;
int speedSelect = 0;
volatile int i = 1;
volatile int stopSeq= 0;

int speed[10];

/**
THE DEFAULT _DELAY_MS FUNCTION CASUSES THE ATMEGA TO FREEZE
THIS CAUSES ISSUE IN LED SEQUENCE, I.E WHEN THE INTERRUPT BUTTON IS 
PRESSED, THE LED SEQUENCE ALSO STOPPED. SO THIS NEW DELAY HAS BEEN
USED. THIS DOESN'T CAUSE THE ATMEGA TO FREEZE 
**/
void delay(unsigned long delay) {
  volatile unsigned long i = 0;
  for (i = 0; i < delay; i++) {
      __asm__ __volatile__ ("nop");
  }
}


void startLedSeq(){
    /**
	START LED SEQUENCE ON THE 16 LED's
	SELECT A DIFFERENT SPEED LEVEL EACH TIME
	A SPECIAL DELAY FUNCTION IS USED FOR DELAY
	**/
    PORTB = 0x00;
    PORTA = 0x00;
	int speedToRun = speed[speedSelect];
	PORTD &= ~(1 << PIND0);
	PORTD &= ~(1 << PIND1);
    for(i = 0;i<=16;i++){
	    if(stopSeq == 1){
		   break;
		}
	    ledLight = i;
		if(i >= 7){
		   ledLight = i - 8;
		    PORTA = 1 << ledLight;
			PORTB = 0x00;
		}else{
			PORTB = 1 << ledLight;
		}
		//delay(speedToRun);
		_delay_ms(speedToRun);
	}
	if(i==16){
	   PORTB = 0x00;
	   PORTA = 0x00;
	}
	i=0;
	ledLight = 0;
	stopSeq = 0;
	ledStarted = 0;
	speedSelect++;
	if(speedSelect >= 9){
	   speedSelect = 0;
	}
}

void checkGameStart(){
    /**
	SOFTWARE LEVEL BOUNCE CHECK
	START LED SEQ IF BUTTON ACTUALLY PRESSED
	**/
    buttonGamePressed++;
    if(buttonGamePressed > 100 && ledStarted == 0){
		ledStarted = 1;
		buttonGamePressed = 0;
		startLedSeq();
	}
}


/**
WHEN INT0 PIN IS DETECTED, CHECK THE VALUE OF "i" AND SEE
WHERE IT HAS REACHED. IF "i" HAS REACHED 15TH OR 16TH LED,
ENABLE LED ACCORDINGLY
**/
ISR(INT0_vect){
	if(i == 15){
		PORTD |= (1 << PIND0);
        PORTD &= ~(1 << PIND1);
	}else if(i == 16){
		PORTD |= (1 << PIND0);
        PORTD |= (1 << PIND1);
	}else{
		PORTD |= ((1 << PIND0) | (1 << PIND1));
		delay(200);
		PORTD &= ~(1 << PIND0);
		PORTD &= ~(1 << PIND1);
		delay(200);
		PORTD |= ((1 << PIND0) | (1 << PIND1));
		delay(200);
		PORTD &= ~(1 << PIND0);
		PORTD &= ~(1 << PIND1);
	}
	
}

int main(void){
   
   /*** 
   INITIALIZE PORTS 
   two LED from PORTD are used as output LEDs
   i.e to measure your reaction time
   ***/
   DDRA = 0xff;   //PORTA as output
   DDRB = 0xff;   //PORTB as output   
   DDRD = 0b11000011; //interrupt pins inputs
   
   
   /*** 
   INITIALIZE INTERRUPTS 
   USING INT0 i.e PD2 on RISING EDGE
   THESE SETTINGS HAVE ALREADY BEEN DISCUSSED IN EARLIER BLOGS
   ***/
   cli();  //clear global interrupts
   GICR = 1 << INT0; //enable intrupt on INT0
   SREG = 1 << 7;
   MCUCR = 1 <<ISC01 | 1 <<ISC00;  // on rising edge
   sei(); //enable global interrupts
   
   /*** 
   LIGHT UP ALL LEDS FOR 500ms 
   JUST TO TEST YOUR CONNECTION 
   ***/
   PORTB = 0xff;  //light up all leds when you start
   PORTA = 0xff;  //light up all leds when you start
   PORTD |= ((1 << PIND0) | (1 << PIND1)); // light up the output led
   _delay_ms(500);
   PORTB = 0x00;
   PORTA = 0x00;
   PORTD &= ~(1 << PIND0);
   PORTD &= ~(1 << PIND1);
   
   
   /** 
   INITIALIZE ALL VARIABLES AND SET SPEED LEVELS 
   SETTING UP 10 SPECIFIED SPEED LEVELS WHICH CAN BE INCREASED AS WELL 
   ***/
   ledStarted = 0;
   speed[0] = 100;
   speed[1] = 50;
   speed[2] = 75;
   speed[3] = 85;
   speed[4] = 40;
   speed[5] = 125;
   speed[6] = 60;
   speed[7] = 80;
   speed[8] = 90;
   speed[9] = 110;
   
   while(1){
       
	   if(bit_is_set(PIND,6)){
	      /**
		  AS SOON AS PUSH BUTTON CONNECTED TO PD6 IS PRESSED
		  START LED SEQUENCE
		  **/
		  checkGameStart();
	   
	   }else{
	   
	   }
	   
   }
}