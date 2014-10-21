//------------------------------------------------------------------------------
//  File Name: adc.c
//
//  Description: This file contains the adc converters
//
//  Mattia Muller
//  Oct 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

volatile unsigned int ADC_Thumb, ADC_Right_Detector, ADC_Left_Detector;
volatile unsigned char ADC_Channel, sample;
unsigned char black_space = SET_0;
extern volatile unsigned char ten_msec_count_timer_A2;
unsigned int tresholds[3];


//------------------------------------------------------------------------------ // Configure ADC10_B
void Init_ADC(void){
ADC10CTL0 = RESET_STATE; // Clear ADC10CTL0
ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
ADC10CTL0 &= ~ADC10MSC; // Single Sequence
ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled

ADC10CTL1 = RESET_STATE; // Clear ADC10CTL1
ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer 
ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
ADC10CTL1 |= ADC10SSEL_0; // MODCLK
ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion

ADC10CTL2 = RESET_STATE; // Clear ADC10CTL2
ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
ADC10CTL2 |= ADC10RES; // 10-bit resolution
ADC10CTL2 &= ~ADC10DF; // Binary unsigned
ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps

ADC10MCTL0 = RESET_STATE; // Clear ADC10MCTL0
ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
ADC10MCTL0 |= ADC10INCH_3; // Channel A3 Thumb Wheel

ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt
} //------------------------------------------------------------------------------

//------------------------------------------------------------------------------ 
// ADC10 interrupt service routine
// ADC_Right_Detector;   // A00 ADC10INCH_0 - P1.0 - Righ
// ADC_Left_Detector;    // A01 ADC10INCH_1 - P1.1 - Left
// ADC_Thumb;            // A03 ADC10INCH_3 - P1.3 - Thumb Wheel
// ADC_Temp;             // A10 ADC10INCH_10 – Temperature REF module 
// ADC_Bat;              // A11 ADC10INCH_11 - Internal
#pragma vector=ADC10_VECTOR 
__interrupt void ADC10_ISR(void){
	switch(__even_in_range(ADC10IV,12)) {
		case 0:  break;    // No interrupt
		case 2:  break;    // conversion result overflow
		case 4:  break;    // conversion time overflow
		case 6:  break;    // ADC10HI
		case 8:  break;    // ADC10LO
		case 10: break;    // ADC10IN
		case 12:
               // Need this to change the ADC10INCH_x value.
                    ADC10CTL0 &= ~ADC10ENC;             // Toggle ENC bit.
                    switch (ADC_Channel++){ 
                      case Right_Detector:
                         ADC10MCTL0 = ADC10INCH_0; // Next channel A1 
                         ADC_Right_Detector = ADC10MEM0; // Read Channel A0 
                      break;
                      case Left_Detector:
                         ADC10MCTL0 = ADC10INCH_3; // Next channel A3 
                         ADC_Left_Detector = ADC10MEM0; // Read Channel A1 
                      break;
                      case Thumbwheel:
                        ADC10MCTL0 = ADC10INCH_1;
                        ADC_Thumb = ADC10MEM0;
                        ADC_Channel=SET_0;
                        break;
                    default:
                    break; 
                }
                ADC10CTL0 |= ADC10ENC | ADC10SC;
                break;                    
		default: break;
	} 
}
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------ 
void ADC_Process(void){
  while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
    ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start 
}
//------------------------------------------------------------------------------




// Function taken from stdlib.h
char* itoa(int val){
    register char *ptr;
    static char buffer[16];	/* result is built here */
    				/* 16 is sufficient since the largest number
				   we will ever convert will be 2^32-1,
				   which is 10 digits. */
    ptr = buffer + sizeof(buffer);
    *--ptr = '\0';
    if (val == 0){
	*--ptr = '0';
    } else while (val != 0) {
	*--ptr = (val % 10) + '0';
	val /= 10;
    }
    return(ptr);
}



void sample_process(void){
  
  if (sample == ON) {
    P1OUT |= IR_LED;
    
  } else {
    P1OUT &= ~IR_LED;

  }
}

void black_line_detect(void) {
	int ADC_detect_average = (ADC_Right_Detector + ADC_Left_Detector) >> SET_1;
	
	if(ADC_Left_Detector > tresholds[SET_0]) {
	    black_space = ON;
            P3OUT |= TEST_PROBE;
	} else if (ADC_Left_Detector < tresholds[SET_0]) {
	    //black_space = OFF;
            P3OUT &= ~TEST_PROBE;
	}		
}





//=========================================================================== 
// Function name: disableADC
//
// Description: This function disables the ADC
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: none
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) //===========================================================================
//******************************************************************************
//------------------------------------------------------------------------------
void disableADC(void)
{

  ADC10IE &= ~ADC10IE0;  
  ten_msec_count_timer_A2=SET_0;   
}


//=========================================================================== 
// Function name: enableADC
//
// Description: This function enables the ADC
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: none
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) //===========================================================================
//******************************************************************************
//------------------------------------------------------------------------------
void enableADC(void)
{

ADC10IE |= ADC10IE0; 
}


void IR_calibration(unsigned char state){
  
  unsigned int base_value_right, base_value_left;

  sample = ON;
  
  if (state == SET_0) {
    sample = OFF;
  }
  
  sample_process();
  ADC_Process();
  five_msec_sleep(SET_10);
  base_value_right = ADC_Right_Detector;
  base_value_left = ADC_Left_Detector;
  
  
  //tresholds[state] = (base_value_left +  base_value_right) >> SET_1; 
  
  tresholds[state] = base_value_left;
  
   char* ascii_value = itoa(tresholds[state]);
   lcd_out(ascii_value,LCD_LINE_2);
           
           
           
  if (state == STEP_2)
    set_treshold();
}

void set_treshold(void){
  
  tresholds[SET_0]= tresholds[SET_1]+((tresholds[STEP_2]-tresholds[SET_1])>>SET_1) + SET_100;// - 100;
}