/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

int main(void)
{
	int i = 0;
	// Enable the clock on Port A
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK;
	
	// Configure the multiplexers for each pin to be GPIO. Pin Control Register (PCR)
	PORTA_PCR11 = PORT_PCR_MUX(0x01); // E1 (Orange LED)
	PORTA_PCR28 = PORT_PCR_MUX(0x01); // E2 (Yellow LED)
	PORTA_PCR29 = PORT_PCR_MUX(0x01); // E3 (Green LED)
	PORTA_PCR10 = PORT_PCR_MUX(0x01); // E4 (Blue LED)
	
	// Configure PTA11, PTA28, PTA29 & PTA10 as output pins. Port Data Direction Register (PDDR)
	GPIOA_PDDR = (1 << 11) |
			(1 << 28) |
			(1 << 29) |
			(1 << 10);
		
	for (i; i < 10; ++i) {
		if ((i % 2) == 0)
			GPIOA_PSOR = (1 << 11) |
			(1 << 28) |
			(1 << 29) |
			(1 << 10); // Turn LEDs off. Port Set Output Register
		else
			GPIOA_PCOR = (1 << 11) |
			(1 << 28) |
			(1 << 29) |
			(1 << 10); // Turn LEDs on. Port Clear Output Register
	}
	return 0;
}
