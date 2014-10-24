#include <avr/io.h>

int main (void)
{
   DDRB |= (1 << PINB0); // Set LED as output

   TCCR1B |= (1 << WGM12 | 1 << CS10); // Configure timer 1 for CTC mode

   TIMSK |= (1 << OCIE1A); // Enable CTC interrupt

   sei(); //  Enable global interrupts

   OCR1A   = 15624; // Set CTC compare value 

   for (;;)
   {

   }
}

ISR(TIMER1_COMPA_vect)
{
   PORTB ^= (1 << PINB0); // Toggle the LED
}