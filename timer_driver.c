//	|timer_driver.c|: Implementation of the Timer Driver
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

#include "timer_driver.h"

static void (*_Timer0_fp)(void);

void Timer0IntHandler(void)
{
   //Clear Timer 0 interrupt flag
   TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

   //Call our custom function
   (*_Timer0_fp)();
}

//Initialize Timer Driver
void timer_d_init(void (*aFptr)(void))
{
   //Set the function pointer used to handle the timer 0 interrupt
   _Timer0_fp = aFptr;

   //Set the clocking to run at 20 MHz (200 MHz / 10) using the PLL.  When
   // using the ADC, you must either use the PLL or supply a 16 MHz clock
   // source.
   SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);

   //Enable Timer 0 Peripheral
   SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	//Configure and Set Timer 0A
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / 16000);

	//Enable the Timer 0A interrupt
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	//Enable Timer 0A
	TimerEnable(TIMER0_BASE, TIMER_A);
}