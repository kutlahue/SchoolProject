//------------------------------------------------------------------------------
//  File Name: main.c
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"


// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];

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
   
    
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                            // Can the Operating system run
  
  Switches_Process();                       // Check for switch state change 

 }
//------------------------------------------------------------------------------
}





