//	|adc_driver.c|: Implementation of the Analog-to-Digital Converter Driver
//
//	@author: Joe Gibson
//	@author: Adam Luckenbaugh

#include "adc_driver.h"

//Pointer to the function that will be called
// by the ADC interrupt handler
static void (*_ADC0_fp)(void);

//ADC interrupt handler
void ADC0IntHandler()
{
    //Clear the ADC interrupt flag
    ADCIntClear(ADC0_BASE, 3);

    //Call the ADC function pointer
    (*_ADC0_fp)();
}

//Initialize ADC Driver
void adc_d_init(void (*aFptr)(void))
{
	//Set the function pointer
	_ADC0_fp = aFptr;

    //Enable the ADC0 peripheral
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    //Enable the GPIO Peripheral for Port B.
    // The AIN0 pin is connected to Port B, Pin 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    //Select the ADC pin to be AIN0, on Port B, Pin 1
    GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_1);

    //Disable Sequence 3 for ADC CH0 while
    // configuring the sequence
    ADCSequenceDisable(ADC0_BASE, 3);

    //Configure ADC Sequence 3 (the only sequence with one single step).
    // This selects sequence 3, processor triggering, and sets the 
    // priority to level 0, the highest level
    ADCSequenceConfigure(ADC_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    //Configure the single sequence step, step 0.
    // This configures step 0 to sample channel 0 (ADC_CTL_CH0), enable
    // interrupts for this step (ADC_CTL_IE), and indicates that this is
    // the last step (and in fact the only step) in the sequence (ADC_CTL_END)
    ADCSequenceStepConfigure(ADC_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);

    //Since sample sequence 3 is now configured, it must be enabled
    ADCSequenceEnable(ADC0_BASE, 3);

    //Enable the ADC interrupt for sequence 3
    ADCIntEnable(ADC0_BASE, 3);
    IntEnable(INT_ADC0SS3);

    //Clear the interrupt status flag.  This is done to make sure the
    // interrupt flag is cleared before we sample the first time
    ADCIntClear(ADC0_BASE, 3);
}

//This method triggers a processor conversion of ADC sequence 3
void adc_d_triggerConversion(void)
{
    //Trigger ADC Sequence 0
    ADCProcessorTrigger(ADC0_BASE, 3);
}