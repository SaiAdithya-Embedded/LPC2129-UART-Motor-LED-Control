#include <LPC21xx.h>
#include<string.h>
#include "uart_header.h"
#include "LCD header.h"
 
#define LED_indicator (1<<17)
#define motorin1 (1<<8)
#define motorin2 (1<<9)
 
 
volatile unsigned char rx_flag=0;
volatile unsigned char rx_data[12];
volatile int i=0;
void UART0_ISR(void) __irq
{
  char ch;
	ch=U0RBR;
	if (ch == '\r' || ch == '\n')  
    {
        rx_data[i] = '\0';
        rx_flag = 1;
        i = 0;
    }
		else
		{
	    if(i<10)
	    {
					rx_data[i++] = ch;         
			}
		}
			VICVectAddr = 0; 
}
 
void config_uart0_rx_int(void)
{
    VICIntSelect = 0;               
    VICVectCntl0 = (0x20) | 6;      
    VICVectAddr0 = (int)UART0_ISR;  
    VICIntEnable = (1 << 6);        
 
    U0IER = 1 << 0;                 
}
int main(void)
{
    IODIR0 = LED_indicator | motorin1 | motorin2;
 
    IOSET0 = LED_indicator;         
    IOCLR0 = motorin1 | motorin2; 	
	 lcd_init();
    UART0_CONFIG();
    config_uart0_rx_int();
 
    while(1)
    {
			if(rx_flag)
			{
				lcd_clear();
				lcd_string("Ready");
				rx_flag=0;
            if(strcmp((char *)rx_data,"LED OFF")==0)  
						{		
                IOSET0 = LED_indicator;
							  lcd_string("LED is OFF");
						}
 
            else if(strcmp((char *)rx_data,"LED ON")==0) 
						{						
                IOCLR0 = LED_indicator;
						    IOCLR0 = motorin1 | motorin2;
                lcd_string("LED is ON");
						}
 
            else if(strcmp((char *)rx_data,"MOTOR ON")==0)
						{
                IOSET0=LED_indicator;
						    IOSET0 = motorin1;
                IOCLR0 = motorin2;
                lcd_string("Motor is ON");
						}
 
            else if(strcmp((char *)rx_data,"MOTOR OFF")==0)
						{
                IOCLR0 = motorin1 | motorin2;
                lcd_string("Motor is OFF");
						}
 
        }
			}
}