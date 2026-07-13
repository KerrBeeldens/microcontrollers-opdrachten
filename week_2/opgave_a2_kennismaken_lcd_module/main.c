#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define BIT(x) (1 << (x))
#define LCD_E 3
#define LCD_RS 2

void toggleEnableBit() {
	PORTC |= BIT(LCD_E);
	PORTC &= ~BIT(LCD_E);
}

void sendCommand(uint8_t command) {
	PORTC = 0xf0 & command; // First nibble
	PORTC &= ~BIT(LCD_RS); // Clear RS
	toggleEnableBit();
	_delay_us(40);

	PORTC = command << 4; // Second nibble
	PORTC &= ~BIT(LCD_RS); // Clear RS
	toggleEnableBit();
	_delay_us(40);
}

void sendData(uint8_t data) {
	PORTC = 0xf0 & data; // First nibble
	PORTC |= BIT(LCD_RS); // Set RS
	toggleEnableBit();
	_delay_us(40);

	PORTC = data << 4; // Second nibble
	PORTC |= BIT(LCD_RS); // Set RS
	toggleEnableBit();
	_delay_us(40);
}

void clearDisplay() {
	sendCommand(0b00000001);
	_delay_ms(2);
}

void shiftDisplay(int8_t amount) {
	// If larger than 0, shift right, else left
	uint8_t command = amount > 0 ? 0b00011100 : 0b00011000;
	
	for (int i = 0; i < abs(amount); i++) {
		sendCommand(command);
	}
}

void initDisplay() {
	DDRC = 0xff; // Set C0 t/m 7 to output

	_delay_ms(50); // wait for LCD power to stabilize

	// Initializing by Instruction (see figure 24)
	PORTC = 0b00110000;
	toggleEnableBit();
	_delay_ms(5);

	PORTC = 0b00110000;
	toggleEnableBit();
	_delay_us(150);

	PORTC = 0b00110000;
	toggleEnableBit();
	_delay_us(40);

	// Switch to 4-bit mode
	PORTC = 0b00100000;
	toggleEnableBit();
	_delay_us(40);

	// Set remaining settings
	sendCommand(0b00101000); // 4-bit, 2 line, 5x8 font
	sendCommand(0b00001100); // display on, cursor off, blink off
	sendCommand(0b00000110); // entry mode
	
	clearDisplay();
}

void displayString(char *string) {
	while(*string) {
		sendData(*string++);
	}
}

int main(void) {
	initDisplay();
	char text[] = "HOI";
	displayString(text);
	
	while(1) {
		for(int i = 0; i < 13; i++) {
			shiftDisplay(1);
			_delay_ms(250);
		}
		
		for(int i = 0; i < 13; i++) {
			shiftDisplay(-1);
			_delay_ms(250);
		}
	}
}