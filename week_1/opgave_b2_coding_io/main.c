#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BIT(x) (1 << (x))

int main(void) {
	DDRD |= BIT(6) | BIT(7); // Make pin D6 and D7 output
	PORTD |= BIT(6); // Turn pin D6 on (D7 stays off)
	
    while(1) {
        PORTD ^= BIT(6) | BIT(7); // Toggle pin D6 and D7
		_delay_ms(500);
    }
}