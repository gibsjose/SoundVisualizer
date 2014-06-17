#include "math.h"

#define ADC_MAX 	1023

double get_average_power(unsigned long *buf, unsigned len)
{
	/*
	1) Take absolute value of each datum
	2) Normalize each datum (0-1) and cast as double: divide by max ADC value... (8bit? 16-bit?)
	3) Calculate power in db = 20 * log10(amplitude) of each datum
	4) Calculate the average power of the 200ms sample
	*/

	double total = 0;

	for(int i = 0; i < len; i++)
	{
		total += 20 * log(((double)abs(buf[i])) / ADC_MAX);
	}

	return total / len;
}