
#include <lpc21xx.h>
#include"delay.h"

#define lcd_d (0xF << 20)
#define rs (1 << 17)
#define rw (1 << 18)
#define e  (1 << 19)

/* ---------------- LCD COMMAND ---------------- */
void lcd_cmd(unsigned char c)
{
    unsigned char m, n;

    m = (c & 0xF0);
    IOCLR1 = lcd_d;
    IOSET1 = (m << 16);//upper 4-bits
    IOCLR1 = rs;
    IOCLR1 = rw;
    IOSET1 = e;
    delay_ms(2);
	  IOCLR1 = e;

    n = (c & 0x0F);
    IOCLR1 = lcd_d;
    IOSET1 = (n << 20);//lower 4-bits
    IOCLR1 = rs;
    IOCLR1 = rw;
    IOSET1 = e;
    delay_ms(2);
	  IOCLR1 = e;
}

/* ---------------- LCD DATA ---------------- */
void lcd_data(unsigned char d)
{
    unsigned char m, n;

    m = (d & 0xF0);
    IOCLR1 = lcd_d;
    IOSET1 = (m << 16);//upper 4-bits
    IOSET1 = rs;
    IOCLR1 = rw;
    IOSET1 = e;
    delay_ms(2);
	  IOCLR1 = e;

    n = (d & 0x0F);
    IOCLR1 = lcd_d;
    IOSET1 = (n << 20);//lower 4-bits
    IOSET1 = rs;
    IOCLR1 = rw;
    IOSET1 = e;
    delay_ms(2);
	  IOCLR1 = e;
}

/* ---------------- LCD INIT ---------------- */
void lcd_init(void)
{
    IODIR1 = lcd_d | rs | rw | e;//P1.17 to P1.23 pins are
	//selected as Output pins
    
  lcd_cmd(0x01);//To clear the display
	lcd_cmd(0x02);//Return cursor to home position
	lcd_cmd(0x28);//4-bit interface
	lcd_cmd(0x0C);//Display ON,Cursor OFF
	lcd_cmd(0x80);//Select starting address of DDRAM
}

/* ---------------- LCD STRING ---------------- */

void lcd_string(unsigned char *s)
{
	 char pos=0;
    while (*s)
		{
    lcd_data(*s++);
    pos++;
    if(pos==16)
    lcd_cmd(0xC0);			
		}
}
