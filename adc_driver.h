//	|adc_driver.h|: Header for the Analog-to-Digital Converter Driver
//
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "oled_driver.h"

//Initialize ADC Driver
void adc_d_init(void (*aFptr)(void));

//Trigger an ADC conversion
void adc_d_triggerConversion(void);

#endif