//	|visualizer.c|: Implementation of the Sound Visualizer
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

//Include standard C libs
#include <stdio.h>

//Include driver headers
#include "adc_driver.h"
#include "timer_driver.h"
#include "oled_driver.h"

//Debug Mode
#define DEBUG 1

//Defines
#define LEN 			128			//Length of string
#define SAMPLE_FREQ 	16000		//ADC Sampling frequency

//Static prototypes
static void timer_init(void);
static void adc_init(void);
static void oled_init(void);
static void interrupt_init(void);

//Main
int main()
{
	char str[LEN];
	int adc_value;

	//Initialize peripherals
	timer_init();
	adc_init();
	oled_init();

	interrupt_init();

	while(1)
	{
		if(timer_d_get_test_var())
		{
			oled_d_print_origin("TestVar = 1");
		}

		else
		{
			oled_d_print_origin("TestVar = 0");
		}

		//Obtain the current ADC value
		adc_value = adc_d_getCurrentADC();

		sprintf(str, "ADC = %d", adc_value);
		oled_d_print_xy(str, 20, 40);
	}

	return 0;
}

static void timer_init(void)
{
	timer_d_init();
}

static void adc_init(void)
{
	adc_d_init();
}

static void oled_init(void)
{
	oled_d_init();
}

static void interrupt_init(void)
{
	//Enable global interrupts
	IntMasterEnable();
}