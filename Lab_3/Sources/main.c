/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

int main(void)
{
	// Enable the clocks on Port A, D and E
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK |
			SIM_SCGC5_PORTD_MASK |
			SIM_SCGC5_PORTE_MASK;
	
	// Configure the multiplexers for each pin to be GPIO. Pin Control Register (PCR)
	PORTA_PCR11 = PORT_PCR_MUX(0x01);  // E1 (Orange LED)
	PORTA_PCR28 = PORT_PCR_MUX(0x01);  // E2 (Yellow LED)
	PORTD_PCR0  = PORT_PCR_MUX(0x01) |
			PORT_PCR_PE_MASK |
			PORT_PCR_PS_MASK;          // Enable input from SW1
	PORTE_PCR26 = PORT_PCR_MUX(0x01) |
			PORT_PCR_PE_MASK |
			PORT_PCR_PS_MASK;          // Enable input from SW2 

	// Configure PTA11 and PTA28 as output pins. Port Data Direction Register (PDDR).
	GPIOA_PDDR = (1 << 11) | (1 << 28);

	for (;;) {	
		// Check if SW1 is pressed (PTA19)
		if ((GPIOD_PDIR & 1) == 0)
			GPIOA_PSOR = (1 << 11); // Turn off Orange LED
		else
			GPIOA_PCOR = (1 << 11); // Turn on Orange LED
	
		// Check if SW2 is pressed (PTA26)
		if ( (GPIOE_PDIR & (1 << 26)) == 0)
			GPIOA_PSOR = (1 << 28); // Turn off Yellow LED
		else
			GPIOA_PCOR = (1 << 28); // Turn on Yellow LED
	}
}
