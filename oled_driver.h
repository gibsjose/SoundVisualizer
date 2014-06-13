//	|oled_driver.h|: Header for the OLED Display Driver
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

#include "drivers/rit128x96x4.h"

#define MAX_BRIGHTNESS 	15	//Maximum brightness

//Initialize OLED Display Driver
int oled_d_init(void);

//Print at 0,0 with full brightness
int oled_d_print_origin(char *str);

//Print at x,y with full brightness
int oled_d_print_xy(char *str, unsigned long x, unsigned long y);

//Print at x,y with given brightness
int oled_d_print_xyb(char *str, unsigned long x, unsigned long y, unsigned long b);

//Clear the screen
int oled_d_clear(void);

#endif