#include <avr/io.h>
#include <stdint.h>            // has to be added to use uint8_t

#include <avr/interrupt.h>    // Needed to use interrupts    


volatile uint8_t portbhistory = 0xFF;     // default is high because the pull-up


int main(void)
{
    Serial.begin(250000);
    DDRB &= ~((1 << DDB0) | (1 << DDB1) | (1 << DDB2)); // Clear the PB0, PB1, PB2 pin
    // PB0,PB1,PB2 (PCINT0, PCINT1, PCINT2 pin) are now inputs

    PORTB |= ((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2)); // turn On the Pull-up
    // PB0, PB1 and PB2 are now inputs with pull-up enabled
    
    PCICR |= (1 << PCIE0);     // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT0);   // set PCINT0 to trigger an interrupt on state change 
    PCMSK0 |= (1 << PCINT1); 
    PCMSK0 |= (1 << PCINT2); 
    sei();                     // turn on interrupts
    
    while(1)
    {
        /*main program loop here */
    }
}



ISR (PCINT0_vect)
{
    uint8_t changedbits;


    changedbits = PINB ^ portbhistory;
    portbhistory = PINB;

    
    if(changedbits & (1 << PINB0))
    {
        if( (PINB & (1 << PINB0)) == 1 )
        {
            Serial.println("0 high");
        }
        else
        {
            Serial.println("0 low");
        }
    }
    
    if(changedbits & (1 << PINB1))
    {
        if( (PINB & (1 << PINB1)) == 1 )
        {
            Serial.println("1 high");
        }
        else
        {
            Serial.println("1 low");
        }
    }

    if(changedbits & (1 << PINB2))
    {
        Serial.println(2);
    }

}
