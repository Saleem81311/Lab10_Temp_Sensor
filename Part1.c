#include "msp.h"
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************************************************
 * Editors: Saleem Griggs-Taylor, Kevin Figurski, Tennison Hoffmann
 * Start Date: 11/4/2021
 * Last modified: 11/4/2021
 * Description: This program is developed to interface a temperature sensor with the MSP432 while also
 * displaying the values to a LCD and using a potentiometer to control output of the temperature sensor.
 *****************************************************************************************************************/

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
}
