//------------------------------------------------------------------------------
//  File Name : switch.c
//
//  Description: This file contains the switch control functions
//
//  Mattia Muller
//  Sep 2014
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------


#include "macros.h"
#include "msp430.h"
#include "functions.h"

unsigned char SW1_Debounce = SET_0, SW2_Debounce = SET_0;
extern char *display_1;
extern char *display_2;

//=========================================================================== 
// Function name: Switches_Process
//
// Description: This function handles the detection of SW1 and SW2
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: SW1_Debounce -Dbounce counter for switch 1/ SW2_Debounce -Dbounce counter for switch 2
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) //===========================================================================
void Switches_Process(void){
//------------------------------------------------------------------------------
// Switch Configurations
//
// To debounce the switches we use a timer and a counter
// The counter is there to avoid that a simple vibration is perceived as the switch being pressed
// The timer is there to avoid that if the switch is pressed to long it turns on and off
//
//------------------------------------------------------------------------------
  if (!(P4IN & SW1)){ 						// Check for SW1 being pressed
    SW1_Debounce++;   						// Increment the SW1 counter
    if (SW1_Debounce == DEBOUNCE_COUNTER){  // Check that the counter is high enough to be considered a press					// Set Port 3 pin 5 to high
      P3OUT &= ~(L_FORWARD);
      P3OUT ^= (R_FORWARD);                                    // Deactivate the other port
      P3OUT |= TEST_PROBE;					// Turn the LCD screen on

      if (!(P3OUT & R_FORWARD)){			// Check the status of the ports to determine what the display will be showing.
          //           1234567890123456
          display_2 = "OFF          OFF";   // Set the display line 2
        } else {
          //           1234567890123456
          display_2 = "OFF           ON";   // Set the display line 2
      }
  //           1234567890123456
  	  display_1 = "Lt  Forward   Rt";       // Set the display line 1
      lcd_out(display_1,LCD_LINE_1);        // Show display line 1 on the LCD
      lcd_out(display_2,LCD_LINE_2);        // Show display line 2 on the LCD
      SW1_Debounce = SET_0;					// Reset the SW1 counter
      five_msec_sleep(DEBOUNCE_TIMER);		// Set the programm to sleep to avoid the recognition of any other input
    }
  }
  if (!(P4IN & SW2)) {						// Same procedure for SW2
    SW2_Debounce++;
    if (SW2_Debounce == DEBOUNCE_COUNTER){
      P3OUT &= ~(R_FORWARD);
      P3OUT ^= (L_FORWARD);                                  
      P3OUT |= TEST_PROBE;

      
        if (!(P3OUT & L_FORWARD)){
          //           1234567890123456
          display_2 = "OFF          OFF";
        } else {
          //           1234567890123456
          display_2 = "ON           OFF";
        }
   //            1234567890123456
    display_1 = "Lt  Forward   Rt";
      lcd_out(display_1,LCD_LINE_1);       
      lcd_out(display_2,LCD_LINE_2); 
      SW2_Debounce = SET_0;
      five_msec_sleep(DEBOUNCE_TIMER);
    }
  }
//------------------------------------------------------------------------------
}