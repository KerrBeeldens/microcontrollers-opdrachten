#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BIT(x) (1 << (x))

int main(void)
{
	DDRA |= BIT(6) | BIT(7); // Make pin 6 and 7 output
	
    while(1)
    {
        PORTA ^= BIT(6) | BIT(7); // Toggle pin 6 and 7
		_delay_ms(1500);
    }
}