
#include "stm32f4xx.h"
#include "lcd.h"


int main(void)
{
	lcd_init();
    lcd_locate(1,0);
	lcd_str("Wellcome");               
		      
  while (1);
}
