#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BIT(x) (1 << (x))

int main(void)
{
	DDRD |=  BIT(7); // Make D7 output
	
	while(1)
	{
		
		if(PIND & BIT(0)) // Test if D0 is HIGH
		{
			PORTD ^= BIT(7); // Toggle D7
		} 
		else
		{
			PORTD &= ~BIT(7); // turn off D7
		}
		
		_delay_ms(500);
	}
}