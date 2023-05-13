/*0.Documentation Section
Author: Mohamed Gamal El-Din Abduljalil Mohamed  2001078
Date: 29,April,2023
Description: functions to provide an interface with UART protocol services in the TM4C123GH6PM microcontroller
*/

#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdio.h>

#define elif else if

/*================================================================
					UART 1 Function Prototypes
================================================================*/
void UART1_Init(unsigned long frequency, unsigned long BaudRate);
unsigned char UART1_InChar(void);
void UART1_OutChar(char UART_CHAR);
void UART1_InString(char *ptr, int size);
void UART1_CRLF(void);
/*=================================================================
				       //UART 1 FUNCTIONS//
==================================================================*/

///WARNING: MODIFIED USE FOR GPS MODULE FUNCTIONALITY - DOESN'T WORK WITH SERIAL MONITORS
void UART1_Init(unsigned long frequency, unsigned long BaudRate)
{
	unsigned long BRD = ((frequency<<2)+BaudRate)/BaudRate;

	//Enabling UART1 Clock
	SYSCTL_RCGCUART_R |= 0x02;
	
	//Enabling PORT B's clock and waiting for it
	SYSCTL_RCGCGPIO_R |= 0x02;
	while(SYSCTL_PRGPIO_R == 0);
	
	//Disable UART1
	UART1_CTL_R &= ~(0x01);
	
	//Setting the baudrate divisor
	UART1_IBRD_R = (BRD>>6);
	UART1_FBRD_R = BRD&0x2F;
	
	//Setting Preferred Line Controls
	UART1_LCRH_R = 0x0070;
	
	//Enabling Tx0 and Rx0 and UART0
	UART1_CTL_R |= 0x301;
	
//_________________________________
	
	//Initializing Port B pins B0 and B1
	GPIO_PORTB_AFSEL_R |= 0x03;
	GPIO_PORTB_AMSEL_R &= ~(0x03);
	
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00) + 0x00000011;
	GPIO_PORTB_DEN_R |= 0x03;
}

unsigned char UART1_InChar(void)
{
	while(UART1_FR_R& 0x10);		//while UART1 Recieving FIFO empty, Do nothing
	return UART1_DR_R;					//once you get data, return it
}

void UART1_OutChar(char UART_CHAR)
{
	while(UART1_FR_R&0x20);		//while UART1 Transmission FIFO full, do nothing
	UART1_DR_R = UART_CHAR;		//once its not FULL, output the given character
}

//reads a string of characters untill the size limit is exceeded or a linefeed character is input.
void UART1_InString(char *string, int size)
{
	int current;		//current index in the given string
	char temp;
	
	if(size<=0)
	{
		return;
	}
	
	for(current = 0; current<size ;current++)
	{
		temp = UART1_InChar();
		if(temp == '\r')
		{
			continue;
		}
		if(temp == '\n')
		{
			string[current]=0;
			return;
		}

		if(temp == '\b')
		{
			if(current == 0)
			{
				string[current] = 0;
				current--;
			}
			else
			{
				current--;
				string[current] = 0;
				current--;
			}
			continue;
		}
		string[current] = temp;
	}
	string[size] = 0;
	
}

void UART1_CRLF(void)
{
		UART1_OutChar('\r');
		UART1_OutChar('\n');
}

