//	|visualizer.c|: Implementation of the Sound Visualizer
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

//Include standard C libs
#include "utils/ustdlib.h"

//Include driver headers
#include "adc_driver.h"
#include "timer_driver.h"
#include "oled_driver.h"
#include "signal_processing.c"

//Defines
#define LEN 			128			//Length of string

//16kHz sample frequency
#define SAMPLES_PER_MS 16
#define SAMPLE_LEN_MS 200
#define BUF_1 0
#define BUF_2 1

unsigned long Test = 0;
unsigned long TimerCount = 0;

//Static prototypes
static void timer_init(void);
static void adc_init(void);
static void oled_init(void);
static void interrupt_init(void);

//Sound buffer variables
static volatile unsigned long _Buf_1[SAMPLES_PER_MS * SAMPLE_LEN_MS];
static volatile unsigned long _Buf_2[SAMPLES_PER_MS * SAMPLE_LEN_MS];
static volatile unsigned _BufCurIndex = 0;	//current array index of the buffers
static volatile unsigned _CurBuf = BUF_1;	//0 == _Buf_1; 1 == _Buf_2

static void loading_bar(void)
{
	//Implement loading bar...
}

static void startup_screen(void)
{
	oled_d_print_xy("Gibson", 20, 30);
	oled_d_print_xy("Luckenbaugh", 20, 40);

	loading_bar();
}

//Main
int main()
{
	char str[LEN];
	int lastCurBuffer = BUF_1;

	//Initialize peripherals
	timer_init();
	adc_init();
	oled_init();

	//Initialize interrupts
	interrupt_init();

	//Display startup screen
	startup_screen();

	//Loop
	while(1)
	{
		/*
		if(Test)
		{
			oled_d_print_xy("Test ain't 0!", 20, 40);
		}
		
		//oled_d_clear();
		oled_d_print_xy("_BufCurIndex = ", 20, 60);
		usprintf(str, "%u", _BufCurIndex);
		oled_d_print_xy(str, 20, 80);
		*/

		if(lastCurBuffer != _CurBuf)
		{
			//The last current buffer was changed,
			//so do the power computations and display the results
			
			usprintf(str, "New buf[0] = %d", (_CurBuf == BUF_1) ? _Buf_1[0] : _Buf_2[0]);
			oled_d_clear();
			oled_d_print_xy(str, 20, 50);

			lastCurBuffer = _CurBuf;
		}
	}

	return 0;
}

void processTimer0(void)
{
	TimerCount++;
	adc_d_triggerConversion();
}

void processADC0(void)
{
	//ADC Value
	unsigned long value;

    //Read ADC Value
    ADCSequenceDataGet(ADC0_BASE, 3, &value);

    //store the value in the current buffer
    if(_CurBuf == BUF_1)
    {
    	//use _Buf_1
    	_Buf_1[_BufCurIndex] = value;
    }
    else
    {
    	//use _Buf_2
    	_Buf_2[_BufCurIndex] = value;
    }

    //increment the current buffer index, wrapping around and changing buffers if necessary
    _BufCurIndex++;

    Test = 1;

    if(_BufCurIndex >= (SAMPLES_PER_MS * SAMPLE_LEN_MS - 1))
    {
    	_BufCurIndex = 0;
    	if(_CurBuf == BUF_1)
    	{
    		_CurBuf = BUF_2;
    	}
    	else
    	{
    		_CurBuf = BUF_1;
    	}
    }
}

static void timer_init(void)
{
	timer_d_init(processTimer0);
}

static void adc_init(void)
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