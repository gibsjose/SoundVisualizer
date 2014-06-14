//	|oled_driver.c|: Implementation of the OLED Display Drivers
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

#include "oled_driver.h"

//Initialize OLED Display Driver
void oled_d_init(void)
{
	//Initialize OLED Display
	RIT128x96x4Init(1000000);
}

//Print at 0,0 with full brightness
void oled_d_print_origin(char *str)
{
	IntMasterDisable();

	RIT128x96x4StringDraw(str, 0, 0, MAX_BRIGHTNESS);

	IntMasterEnable();
}

//Print at x,y with full brightness
void oled_d_print_xy(char *str, unsigned long x, unsigned long y)
{
	IntMasterDisable();

	RIT128x96x4StringDraw(str, x, y, MAX_BRIGHTNESS);

	IntMasterEnable();
}

//Print at x,y with given brightness
void oled_d_print_xyb(char *str, unsigned long x, unsigned long y, unsigned long b)
{
	IntMasterDisable();

	RIT128x96x4StringDraw(str, x, y, b);

	IntMasterEnable();
}

//Clear the screen
void oled_d_clear(void)
{
	IntMasterDisable();

	RIT128x96x4Clear();

	IntMasterEnable();
}