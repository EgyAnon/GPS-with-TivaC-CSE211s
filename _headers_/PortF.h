/*0.Documentation Section
 * Author:Ahmed Ibrahim Ali Aboshanab 2000267 
 * Date: April, 8th, 2023
 * Description: A header file containing functions related to port F in
 * the TM4C123GH6PM microcontroller
 */

#ifndef PORTF_H_
#define PORTF_H_

#include "tm4c123gh6pm.h"

void PortF_Init(void)			//initializes Port F
{
	SYSCTL_RCGCGPIO_R |= 0x20;	//enabling clock for port F
	while(SYSCTL_PRGPIO_R==0);	//checking status bit to ensure clock is running
	GPIO_PORTF_LOCK_R |= 0x4C4F434B;	//unlock port F
	GPIO_PORTF_CR_R |= 0x1F;					//enabling commit register for desired bits
	GPIO_PORTF_AMSEL_R &= ~(0x1F);		//disabling analog functionality
	GPIO_PORTF_AFSEL_R &= ~(0x1F);		//choosing GPIO functionality - no alternate function selected
	GPIO_PORTF_PCTL_R &= ~(0xFFFFF);	//choosing GPIO functionality - no alternate function selected
	GPIO_PORTF_PUR_R &= ~(0x0E);			//disabling pull-up resistors for LEDs
	GPIO_PORTF_PUR_R |= (0x11);				//enabling pull-up resistors for switches 
	GPIO_PORTF_DEN_R |=(0x1F);				//enabling digital functionality for all bits
	GPIO_PORTF_DIR_R &= ~(0x11);			//setting the direction of the switches to input
	GPIO_PORTF_DIR_R |= (0x0E);				//setting the direction of LEDs to input
	GPIO_PORTF_DATA_R |= (0x11);
}
unsigned char Read_SW1 (void)
{
	//returns 1 if switch 1 is pressed, 0 otherwise
	return ((GPIO_PORTF_DATA_R&0x10)>>4)^0x01;
}
unsigned char Read_SW2 (void)
{
	//returns 1 if switch 2 is pressed, 0 otherwise
	return (GPIO_PORTF_DATA_R&0x01)^0x01;
}

void Toggle_Red(void)
{
	GPIO_PORTF_DATA_R ^= 0x02;
}

void SetRed(void)
{
	GPIO_PORTF_DATA_R |= 0x02;
}

void ClearRed(void)
{
	GPIO_PORTF_DATA_R &= ~(0x02);
}

void SetBlue(void)
{
	GPIO_PORTF_DATA_R |= 0x04;
}

void ClearBlue(void)
{
	GPIO_PORTF_DATA_R &= ~(0x04);
}

void SetGreen(void)
{
	GPIO_PORTF_DATA_R |= 0x08;
}

void ClearGreen(void)
{
	GPIO_PORTF_DATA_R &= ~(0x08);
}

void ClearLEDs(void)
{
	GPIO_PORTF_DATA_R &= ~(0x0E);
}

#endif
