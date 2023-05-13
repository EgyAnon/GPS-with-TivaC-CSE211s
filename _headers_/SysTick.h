#ifndef _SYSTICK_TIME_H_
#define _SYSTICK_TIME_H_

/*0.Documentation Section*/
//Description: a file containing all time-related functions.
//Author:  x


#include "tm4c123gh6pm.h"
void PLL_init(void);
void SysTick_Init(void);
void SysTick_1ms(unsigned int n_ms);
void Delay_1s(unsigned int seconds);


void PLL_init(void)     //configures the frequency to 80MHz
{
	SYSCTL_RCC2_R |= 0x80000000; // USERCC2
	SYSCTL_RCC2_R |= 0x00000800; // BYPASS2, PLL bypass
	SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x000007C0) // clear bits 10-6
	+ 0x00000540; // 10101, configure for 16 MHz crystal
	SYSCTL_RCC2_R &= ~0x00000070; // configure for main oscillator source
	SYSCTL_RCC2_R &= ~0x00002000;
	SYSCTL_RCC2_R |= 0x40000000; // use 400 MHz PLL
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000)+(4<<22); // 80 MHz
	while((SYSCTL_RIS_R&0x00000040)==0){}; // wait for PLLRIS bit
	// 6) enable use of PLL by clearing BYPASS
	SYSCTL_RCC2_R &= ~0x00000800;
}

void SysTick_Init(void) //initializes SysTick
{
	NVIC_ST_CTRL_R  &= ~(0x01);
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x05;
}

void SysTick_1ms(unsigned int n_ms) //executes a blocking delay for n milliseconds, where n is a parameter.
{
	//maximum value is 0x00FFFFFF
	NVIC_ST_RELOAD_R = n_ms * 80000;
	if(n_ms*80000>0x00FFFFFF)
	{
		NVIC_ST_RELOAD_R = 0x00FFFFFF;
	}
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R & 0x00010000)==0);
}

void Delay_1s(unsigned int seconds) //executes a blocking delay for n seconds, where n is a parameter.
{
	unsigned int i = 0;
	
	for (i = 0; i< 5*seconds;  i++)
	{
		SysTick_1ms(200);
	}
}

#endif
