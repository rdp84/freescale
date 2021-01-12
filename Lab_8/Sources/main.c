/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

int main(void)
{
	int counter = 0;

	mcg_fei_blpe();
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK;
	SIM_SCGC3 = SIM_SCGC3_FTM2_MASK;

	// Set the MUX to alternative 3 - this is FTM2_CH1
	PORTA_PCR11 = PORT_PCR_MUX(0x03);
	PORTA_PCR28 = PORT_PCR_MUX(0x01);
	GPIOA_PDDR = (1 << 11) | (1 << 28);

	
	
	// Nested Vector Interrupt Controller (NVIC) for FTM2
	// FTM2 = vector 80, IRQ = 80 - 16 = 64
	// NVIC non-IPR register = 64 div 32 = 2
	// NVIC bit field in non-IPR register = 64 mod 32 = 0
	// NVIC IPR register = 64 div 4 = 16
	// NVIC bit field in IPR register = ((64 mod 4) * 8) + 4 = 4
	// therefore priority set by bit fields 4-7	

	// Clear any pending interrupts for FTM2
	NVICICPR2 = 1;
	setup_lab();
	
	for(;;)	   
	   	counter++;
	
	return 0;
}
