//	|signal_processing.c|: Implementation of the signal processing functions
//
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

#include "signal_processing.h"

int get_average_power(unsigned long *buf, unsigned len)
{
	/*
	//To calculate the actual power of the audio signal:
	1) Take absolute value of each datum (optional)
	2) Normalize each datum (0-1) and cast as double: divide by max ADC value (1023)
	3) Calculate power in db = 20 * log10(amplitude) of each datum
	4) Calculate the average power of the 200ms sample
	*/

	int total = 0;
	
	for(int i = 0; i < len; i++)
	{
		//NOTE: For some reason, there is an issue when using floating point
		// operations at this line. Specifically, dividing buf[i] by ADC_MAX (1023)
		// produces unexpected results, like stopping the processor, presumably in 
		// a fault condition. In additon, the log10 function, for which a function
		// prototype does exist, does not appear to be implemented
		//total += 20 * log10(buf[i] / ADC_MAX);

		//In lieu of the issues above, we decided to calculate the average voltage
		// instead of average power
		total += buf[i];
	}
	
	return (total / len);
}