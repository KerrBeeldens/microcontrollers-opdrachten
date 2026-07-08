#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BIT(x) (1 << (x))

int main(void)
{
	
	DDRD = 0b11111111; // Make pins D0 t/m D7 output
	
	while (1)
	{
		// Bit shift 1 from D0 to D7
		for (int i = 0; i < 8; i++)
		{
			PORTD = 1 << i;
			_delay_ms(50);
		}
	}
}