//------------------------------------------------------------------------------
//  File Name: main.c
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Mattia Muller
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"


// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
extern volatile unsigned char what_to_do, sample;
extern volatile unsigned int Time_Sequence, ADC_Thumb, ADC_Right_Detector, ADC_Left_Detector;

//=========================================================================== 
// Function name: Main
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to // initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: control_state[CNTL_STATE_INDEX]
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) 
//===========================================================================
void main(void){
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();
  PJOUT |= LED1;                            // Turn LED 1 on to indicate boot
  Init_Timers();                            // Initialize Timers
  five_msec_sleep(INIT_TIMER);              // 375 msec delay for the clock to settle
  Init_LCD();                               // Initialize LCD
  five_msec_sleep(INIT_TIMER);              // 375 msec delay for the clock to settle
  Init_LEDs();                              // Initialize LEDs
  Init_ADC(); 

  
   int old_value;
   char* ascii_value;
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                            // Can the Operating system run
 
        // if (Time_Sequence%3 == 0){
           sample = ON;
        // } else {
        //   sample = OFF;
        // }
        black_line_detect(); // Are we on a black line
        sample_process();    // Are we sampling or not?
        Switches_Process();  // Switches YEAH!
        ADC_Process();		// Let' sample the ADC values
         if (ADC_Thumb != old_value){
           //lcd_out("               ",LCD_LINE_2);
           ascii_value = itoa(ADC_Thumb);
           menu_process(ADC_Thumb);
           //lcd_out(ascii_value,LCD_LINE_2);
           five_msec_sleep(50);
         }
         old_value = ADC_Thumb;
	 
         if(Time_Sequence > 250){
            Time_Sequence = 0;
            
         }
         
         if (what_to_do == PROJECT_05 || what_to_do == STRAIGHT || what_to_do ==  THUMB_WHEEL){
          project_5_process(); 
         }
         
         
      	}
//------------------------------------------------------------------------------
}





