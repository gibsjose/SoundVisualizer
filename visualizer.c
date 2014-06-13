//	|visualizer.c|: Implementation of the Sound Visualizer
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

//Include standard C libs
#include "utils/ustdlib.h"

#include <utils/ustdlib.c>

//Include driver headers
#include "adc_driver.h"
#include "timer_driver.h"
#include "oled_driver.h"

//Defines
#define LEN 			128			//Length of string

//16kHz sample frequency
#define SAMPLES_PER_MS 16
#define SAMPLE_LEN_MS 200
#define BUF_1 0
#define BUF_2 1

//Static prototypes
static void timer_init(void);
static void adc_init();
static void oled_init(void);
static void interrupt_init(void);

//sound buffer variables
static unsigned long _Buf_1[SAMPLES_PER_MS * SAMPLE_LEN_MS];
static unsigned long _Buf_2[SAMPLES_PER_MS * SAMPLE_LEN_MS];
static unsigned _BufCurIndex = 0;	//current array index of the buffers
static unsigned _CurBuf = BUF_1;		//0 == _Buf_1; 1 == _Buf_2

//Main
int main()
{
	char str[LEN];
	int lLastCurBuffer = BUF_1;

	//Initialize peripherals
	timer_init();
	adc_init();
	oled_init();

	interrupt_init();

	oled_d_print_xy("hello", 20, 40);

	while(1)
	{
		if(lLastCurBuffer != _CurBuf)
		{
			//the last current buffer was changed,
			//so do the power computations and display the results
			
			usprintf(str, "New buf[0] = %d", (_CurBuf == BUF_1) ? _Buf_1[0] : _Buf_2[0]);
			oled_d_clear();
			oled_d_print_xy(str, 20, 40);

			lLastCurBuffer = _CurBuf;
		}
	}

	return 0;
}

void processTimer0()
{
	adc_d_triggerConversion();
}

void processADC0()
{	
	//
	// This array is used for storing the data read from the ADC FIFO. It
	// must be as large as the FIFO for the sequencer in use.  This example
	// uses sequence 3 which has a FIFO depth of 1.  If another sequence
	// was used with a deeper FIFO, then the array size must be changed.
	//
	unsigned long ADC0_Value[1];


    //
    // Read ADC Value.
    //
    ADCSequenceDataGet(ADC0_BASE, 3, ADC0_Value);

    //store the value in the current buffer
    if(_CurBuf == 0)
    {
    	//use _Buf_1
    	_Buf_1[_BufCurIndex] = ADC0_Value[0];
    }
    else
    {
    	//use _Buf_2
    	_Buf_2[_BufCurIndex] = ADC0_Value[0];
    }

    //increment the current buffer index, wrapping around and changing buffers if necessary
    if(++_BufCurIndex == SAMPLES_PER_MS * SAMPLE_LEN_MS)
    {
    	_BufCurIndex = 0;
    	_CurBuf ^= 1;
    }
}

static void timer_init(void)
{
	timer_d_init(processTimer0);
}

static void adc_init()
{
	adc_d_init(processADC0);
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