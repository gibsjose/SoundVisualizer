//	|timer_driver.c|: Implementation of the Timer Driver
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

#include "timer_driver.h"

static int _TestVar;

//ISR For 1s Timer 0 Driver
void Timer0IntHandler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	_TestVar ^= 1;

}

//Initialize Timer Driver
int timer_d_init(void)
{
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);

	//Enable Timer 0 Peripheral
   	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

   	//Configure and Set Timer 0A
   	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
   	TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());

   	//Enable the Timer 0A interrupt
   	IntEnable(INT_TIMER0A);
   	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

   	//Enable Timer 0A
   	TimerEnable(TIMER0_BASE, TIMER_A);

	return 0;
}

int timer_d_get_test_var(void)
{
	return _TestVar;
}