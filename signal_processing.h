//	|signal_processing.h|: Header for the signal processing functions
//
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

#ifndef SIGNAL_PROCESSING_H
#define SIGNAL_PROCESSING_H

#include <math.h>

//Max ADC value for 10-bit ADC is 1023
#define ADC_MAX (1023)

//Determine the average power of the audio signal
int get_average_power(unsigned long *buf, unsigned len);

#endif