#ifndef _PORTD_H_
#define _PORTD_H_

/*0.Documentation Section
 * Author: Ahmed Haitham Ismael El-Ebidy
 * Date: May, 11th, 2023
 * Description: A header file containing functions related to port D in the TM4C123GH6PM microcontroller
*/

#include "tm4c123gh6pm.h"

void PortD_Init(void)
{
	SYSCTL_RCGCGPIO_R |=0x08;
	while(SYSCTL_PRGPIO_R==0);
	
	GPIO_PORTD_AMSEL_R &= ~(0xFF);
	GPIO_PORTD_AFSEL_R &= ~(0xFF);
	GPIO_PORTD_PCTL_R &= ~(0xFFFFFF);
	GPIO_PORTD_DIR_R |= 0x3F;
	GPIO_PORTD_DEN_R |=0x3F;
}

#endif
