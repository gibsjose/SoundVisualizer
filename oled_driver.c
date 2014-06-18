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


void oled_d_display_bar(int aHeight)
{
	char * cDarkStr = "#####################";
	char * cClearStr = "                     ";

	unsigned charHeight = 8;

	unsigned rowInc = OLED_ROWS / charHeight;

	//display a vertical bar with a variable height
	
	for(unsigned rows = 0; rows < OLED_ROWS / charHeight; rows++)
	{
		if( rowInc - rows < (rowInc * (aHeight / 1023.0) ))
		{
			oled_d_print_xy(cDarkStr, 0, rows * charHeight);
		}
		else
		{
			oled_d_print_xy(cClearStr, 0, rows * charHeight);
		}
	}
}

//Clear the screen
void oled_d_clear(void)
{
	IntMasterDisable();

	RIT128x96x4Clear();

	IntMasterEnable();
}