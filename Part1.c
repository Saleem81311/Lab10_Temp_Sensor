#include "msp.h"
#include <stdio.h>
#include <stdlib.h>

void delaysetup(void);
void delayms(uint16_t delay);
void ADC14_init (void);
main(void)
{
 static volatile uint16_t result;
 float nADC;

  delaysetup ( );
  ADC14_init( );

  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; 	// stop watchdog timer
while(1)
      {
 ADC14->CTL0 |= 1; 				//start conversation
 while(!ADC14->IFGR0); 			//wait for conversation to complete
 result = ADC14->MEM[0]; 			// get the value from the ADC
 nADC = (result * 3.3) / 16384;
 printf("Value is:\n\t%d\n\t%f\n",result, nADC);
 delayms(2000);
}
}

void delaysetup (void) 					// sets up the countdown timer
{
SysTick-> CTRL = 0;
SysTick-> LOAD = 0x00FFFFFF;
SysTick-> VAL    = 0;
SysTick-> CTRL = 0x00000005;
}

void delayms(uint16_t delay) 				// timer function set to run a 1 ms increments
{
SysTick->LOAD = ((delay * 3000)-1);
SysTick->VAL = 0;
while((SysTick-> CTRL & 0x00010000) == 0);
}

void ADC14_init (void)
{
P5SEL0 |= 0X20; 					// configure pin 5.5 for A0 input
P5SEL1 |= 0X20;
   ADC14->CTL0 &=~ 0x00000002; 			// disable ADC14ENC during configuration
ADC14->CTL0   |=   0x04400110; 			// S/H pulse mode, SMCLK, 16 sample clocks
ADC14->CTL1    =   0x00000030; 			// 14 bit resolution
ADC14->CTL1   |=   0x00000000; 			// Selecting ADC14CSTARTADDx mem0 REGISTER
ADC14->MCTL[0] = 0x00000000;			// ADC14INCHx = 0 for mem[0]
// ADC14->MCTL[0] = ADC14_MCTLN_INCH_0;
ADC14->CTL0 |= 0x00000002;			// enable ADC14ENC, starts the ADC after configuration
}
