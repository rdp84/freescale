/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

int main(void)
{
	// Enable the clock on Port A
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK;
	
	// Configure the multiplexers for each pin
	PORTA_PCR11 = PORT_PCR_MUX(0x01); // E1 (Orange LED)
	PORTA_PCR28 = PORT_PCR_MUX(0x01); // E2 (Yellow LED)
	
	// Configure PTA11 and PTA28 as output pins
	GPIOA_PDDR = (1 << 11) | (1 << 28);
	
	for(;;) {
		
		GPIOA_PSOR = (1 << 11); // Clear PTA11
		GPIOA_PCOR = (1 << 28); // Clear PTA11
	}
	
	return 0;
}
