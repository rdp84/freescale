/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

int main(void)
{
	unsigned int ftm0_sc;

	// Enable the clocks on Port A, D and Flex-Timer Module (FTM)
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTD_MASK;
	SIM_SCGC6 = SIM_SCGC6_FTM0_MASK;

	// Configure the multiplexers for each pin to be GPIO. Pin Control Register (PCR)
	PORTA_PCR11 = PORT_PCR_MUX(0x01);   // E1 (Orange LED)
	PORTD_PCR0  = PORT_PCR_MUX(0x01) |
			PORT_PCR_PE_MASK |
			PORT_PCR_PS_MASK;           // Enable input from SW1
	
	// Configure PTA11 as output pin. Port Data Direction Register (PDDR).
	GPIOA_PDDR = (1 << 11);
	
	// Configure FTM - set the overflow to max value
	FTM0_MOD = 0xffff;
	// Set clock source to internal, prescale factor to divide by 128
	// and enable interrupts on time overflow by updating
	// Status Control (SC) register
	FTM0_SC = FTM_SC_CLKS(1) | FTM_SC_PS(7) | FTM_SC_TOIE_MASK;
	
	// Nested Vector Interrupt Controller (NVIC) for FTM0
	// FTM0 = vector 78, IRQ = 78 - 16 = 62
	// NVIC non-IPR register = 62 div 32 = 1
	// NVIC bit field in non-IPR register = 62 mod 32 = 30
	// NVIC IPR register = 62 div 4 = 15
	// NVIC bit field in IPR register = ((62 mod 4) * 8) + 4 = 20
	// therefore priority set by bit fields 20-23
	
	// Clear any pending interrupts for FTM0
	NVICICPR1 = (1 << 30);
	
	// Enable the interrupt in the NVIC for FTM0
	NVICISER1 = (1 << 30);
	
	for(;;)
	   	ftm0_sc = FTM0_SC;
	
	return 0;
}
