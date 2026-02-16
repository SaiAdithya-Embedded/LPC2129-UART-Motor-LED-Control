
#include<LPC21xx.h>
void UART0_CONFIG(void);
void UART0_TX(unsigned char);
void UART0_STRING(unsigned char *);
unsigned char UART0_RX(void);

void UART0_CONFIG(void)
{
	PINSEL0=0x00000005;
	U0LCR=0x83;
	U0DLL=97;
	U0LCR=0x03;
	
}

void UART0_TX(unsigned char d)
{
	while((U0LSR&(1<<5))==0);
	U0THR=d;
	
}

void UART0_STRING(unsigned char *s)
{
	while(*s)
	{
		UART0_TX(*s++);
	}
	
}

unsigned char UART0_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
	
}
