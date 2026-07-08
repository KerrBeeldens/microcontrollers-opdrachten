#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define BIT(x) (1 << (x))

int main(void)
{
	
	DDRD = BIT(7); // Make pin D7 output
	bool buttonState = false;
	
	while (1)
	{
		if (PINC & BIT(0)) // Test if C0 is HIGH
		{
			buttonState = !buttonState; // Toggle button state
		}
		
		PORTD ^= BIT(7); // Toggle D7
		
		if (buttonState)
		{
			_delay_ms(250); // 4hz
		}
		else
		{
			_delay_ms(1000); // 1hz
		}
	}
}