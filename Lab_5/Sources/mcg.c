/*
 * mcg.c
 *
 *  Created on: Jan 4, 2021
 *      Author: Bobby
 *
 * Functions for setting clock via Multipurpose Clock Generator (MCG) module.
*/

#include "derivative.h"
#include "mcg.h"

/*
 * Function to transition from Frequency-Locked Loop Engaged Internal (FEI)
 * to Bypassed Low Power External (BLPE)
 * 
 * FEI is default mode of operation.
*/
void mcg_fei_blpe(void)
{	
	// Clock Source Select set to external.
	// This switches us to Frequency-Locked Loop Bypassed External (FBE) mode.
	MCG_C1 = MCG_C1_CLKS(2);

	// Poll for Internal Reference Status to flip to 0 (External)
	while (MCG_S & MCG_S_IREFST_MASK);

	// Wait for MCGOUT to switch over to the external reference clock
	while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2);

	// Transition to BLPE by setting C2[LP] to 1
	MCG_C2 = MCG_C2_LP_MASK;
}

