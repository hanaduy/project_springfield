#include <avr/io.h>
#include <avr/interrupt.h>

int interrupt_flag_haha = 0; 
int main(void)
{
    DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
    // PD2 (PCINT0 pin) is now an input

    PORTD |= (1 << PORTD2);    // turn On the Pull-up
    // PD2 is now an input with pull-up enabled

  DDRB |= _BV(DDB5);

    EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
    EIMSK |= (1 << INT0);     // Turns on INT0

    sei();                    // turn on interrupts
    //Serial.begin(9600);
    //Serial.print("Seen interrupt");
    while(1)
    {
      _delay_us(1);
        if (interrupt_flag_haha) {
          PORTB |= _BV(PORTB5);
          interrupt_flag_haha = 0;
        }
    }
}

ISR (INT0_vect)
{
    interrupt_flag_haha = 1; 
}
