//	|timer_driver.c|: Implementation of the Timer Driver
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

#include "timer_driver.h"

static void (*_Timer_Fptr)(void);


void SysTickISR(void)
{
   (*_Timer_Fptr)();
}

//Initialize Timer Driver
int timer_d_init(void (*aFptr)(void))
{
   //save the function pointer used to handle the timer 0 interrupt
   _Timer_Fptr = aFptr;

   //
   // Set the clocking to run at 20 MHz (200 MHz / 10) using the PLL.  When
   // using the ADC, you must either use the PLL or supply a 16 MHz clock
   // source.
   // TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
   // crystal on your board.
   //
   
   /*SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                SYSCTL_XTAL_8MHZ);
	*/
   SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);

   //Enable Timer 0 Peripheral
   SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

   NVIC_ST_CTRL_R = 0;
   NVIC_ST_RELOAD_R = 128000;   //16ms period for timer
   NVIC_ST_CURRENT_R = 0;     //current counter value = 0
   NVIC_ST_CTRL_R = 0b111;    //clk source = cpu; enable SysTick exception; enable timer

/*
	//Configure and Set Timer 0A
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());

	//Enable the Timer 0A interrupt
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	//Enable Timer 0A
	TimerEnable(TIMER0_BASE, TIMER_A);
*/
	return 0;
}