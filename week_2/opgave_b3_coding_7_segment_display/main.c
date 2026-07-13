#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define BIT(x) (1 << (x))

const unsigned char numbers [17] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F
	0b11111001, // E. (error)
};


void displayDigit(int digit) {
	int digitLocal = digit;
	if (digit > 15 || digit < 0) digitLocal = 16;
	
	PORTB = numbers[digitLocal];
}

int main(void) {
	DDRB = 0b11111111;  // Make B0 t/m B7 output
	
	int count = 0;
	displayDigit(count);
	int previousButtons = 0;

	while (1) {
		int buttons = PINA & (BIT(0) | BIT(1));

		// Both buttons pressed
		if (buttons == (BIT(0) | BIT(1))) {
			count = 0;
		}
		
		// Button 0 pressed
		if ((buttons & BIT(0)) && !(previousButtons & BIT(0))) {
			if (count < 15) count++;
		}
		
		// Button 1 pressed
		if ((buttons & BIT(1)) && !(previousButtons & BIT(1))) {
			if (count > 0) count--;
		}
		
		displayDigit(count);
		previousButtons = buttons;
		_delay_ms(50); // debounce
	}
}