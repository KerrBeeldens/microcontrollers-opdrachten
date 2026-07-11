#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x) (1 << (x))

int main(void) {
	
	DDRD |= BIT(0) | BIT(1); // Make D0 and D1 output
	DDRC = 0b11111111; // Make C0 t/m C7 output
	
	EICRA = 0b00001111; // Set INT0 and INT1 to rising edge
	EIMSK |= BIT(0) | BIT(1);  // Enable interrupts INT0 and INT1
	sei(); // Enable global interrupts
	
	PORTD |= BIT(0); // Set D0 high to trigger the first interrupt

	while(1) {}
}

ISR(INT0_vect) {
	PORTD &= ~BIT(0); // Clear D0

	PORTC <<= 1; // Shift the LED one position to the left
	if (PORTC == 0) PORTC = BIT(0);           
	_delay_ms(150);          
	
	PORTD |= BIT(1); // Set D1 high to trigger INT1
}

ISR(INT1_vect) {
	PORTD &= ~BIT(1); // Clear D1

	PORTC <<= 1; // Shift the LED one position to the left
	if (PORTC == 0) PORTC = BIT(0);           
	_delay_ms(150);          
	
	PORTD |= BIT(0); // Set D0 high to trigger INT0
}