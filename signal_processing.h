//	|timer_driver.h|: Header for the Timer Driver
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

#ifndef SIGNAL_PROCESSING_H
#define SIGNAL_PROCESSING_H

#include <math.h>

#define ADC_MAX (1023)

int get_average_power(unsigned long *buf, unsigned len);

#endif