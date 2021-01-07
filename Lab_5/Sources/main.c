/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

int main(void)
{
	int counter = 0;
	int ftm0_sc;

	mcg_fei_blpe();
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK;
	SIM_SCGC6 = SIM_SCGC6_FTM0_MASK;

	PORTA_PCR11 = PORT_PCR_MUX(0x01);
	GPIOA_PDDR = (1 << 11);

	// Configure Flex Timer Module (FTM)
	// Set the overflow to 37136
	FTM0_MOD = 0xffff;
	// Set clock source to internal and prescale factor to divide by 128
	// by updating Status Control (SC) register
	FTM0_SC = FTM_SC_CLKS(1) | FTM_SC_PS(7);

	for(;;) {
		// Read SC register. This means we can clear the Timer Overflow (TOF)
		// bit later if it is set to 1.
		ftm0_sc = FTM0_SC;

		// Poll to see if TOF bit is set to 1 and overflow has occurred
		if (ftm0_sc & FTM_SC_TOF_MASK) {

			// Flicker LED by updating Port Toggle Output Register
			GPIOA_PTOR = (1 << 11);

			// Now write 0 to TOF bit in SC register. We previously read
			// the SC register so we can now clear the bit, as per
			// the instructions in the manual
			FTM0_SC = !FTM_SC_TOF_MASK;

			// Reinitialise in case other fields have been updated
			FTM0_SC = FTM_SC_CLKS(1) | FTM_SC_PS(7);
		}
	}
	return 0;
}
