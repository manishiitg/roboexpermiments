#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
   DDRD |= (1 << PIND4 | 1 << PIND5); // Set LED as output

   TCCR1B |= (1 << WGM12 | 1 << CS10 | 1 << CS11); // Configure timer 1 for CTC mode with 64 prescale

   OCR1A   = 15624; // Set CTC compare value 
   
   OCR1B = 3906; // Set CTC compare value 
   
   TCCR1A |= (1 << COM1A0 | 1 << COM1B0);

   for (;;)
   {

   }
}