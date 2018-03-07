#include <avr/io.h>
#include <stdint.h>            // has to be added to use uint8_t

#include <avr/interrupt.h>    // Needed to use interrupts    

volatile long motor_0_position; 
volatile long motor_1_position; 
volatile long motor_2_position; 
volatile long motor_3_position; 

int main(void)
{
    Serial.begin(115200);

    DDRD &= ~((1 << DDD2) | (1 << DDD3)); //Clear the PD2, PD3 pin for PINT, motor 0
    DDRB &= ~((1 << DDB0) | (1 << DDB1)); // Clear the PB0, PB1 pin for PCIF_0, motor 1
    DDRC &= ~((1 << DDC0) | (1 << DDC1)); // Clear the PC0, PC1 pin for PCIF_1, motor 2
    DDRD &= ~((1 << DDD4) | (1 << DDD7)); // Clear the PC0, PC1 pin for PCIF_1, motor 3
    // PB0,PB1,PB2 (PCINT0, PCINT1, PCINT2 pin) are now inputs

    PORTD |= ((1 << PORTD2) | (1 << PORTD3));
    PORTB |= ((1 << PORTB0) | (1 << PORTB1)); 
    PORTC |= ((1 << PORTC0) | (1 << PORTC1));   
    PORTD |= ((1 << PORTD4) | (1 << PORTD7)); // turn on the Pull-up resistor mode

    // PB0, PB1 and PB2 are now inputs with pull-up enabled
    EICRA |= 0x05; // Set interrupt to detect any change in pin, the register value should be 0101 
    EIMSK |= ((1 << INT0) );  //enable INT0 and INT1
    PCICR |= ((1 << PCIE0) | (1 << PCIE1) | (1 << PCIE2));     // enable all three PCINT interrupts   
    PCMSK0 |= (1 << PCINT0);   // enable PCINT from PB pins 
    PCMSK1 |= (1 << PCINT8);   // enable PCINT from PC pins  
    PCMSK2 |= (1 << PCINT20); // enable PCINT from PD pins 

    sei();                     // turn on interrupts
    
    while(1)
    {
      _delay_ms(10);
      Serial.print(motor_0_position); 
      Serial.print(",\t"); 
      Serial.print(motor_1_position); 
      Serial.print(",\t"); 
      Serial.print(motor_2_position); 
      Serial.print(",\t"); 
      Serial.println(motor_3_position); 
    }
}


ISR(INT0_vect) 
{
    if ( (((1<<PIND2) & PIND)>>PIND2) == (((1<<PIND3) & PIND)>>PIND3) ) motor_0_position += 1;
    else motor_0_position -= 1; 
}

ISR (PCINT0_vect)
{
    if ( (((1<<PINB0) & PINB)>>PINB0) == (((1<<PINB1) & PINB)>>PINB1) ) motor_1_position += 1;
    else motor_1_position -= 1; 
}

ISR (PCINT1_vect)
{
    if ( (((1<<PINC0) & PINC)>>PINC0) == (((1<<PINC1) & PINC)>>PINC1) ) motor_2_position += 1;
    else motor_2_position -= 1; 
}

ISR (PCINT2_vect)
{
    if ( (((1<<PIND4) & PIND)>>PIND4) == (((1<<PIND7) & PIND)>>PIND7) ) motor_3_position += 1;
    else motor_3_position -= 1; 
}