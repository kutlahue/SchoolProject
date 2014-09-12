//------------------------------------------------------------------------------
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

extern char *display_1;


//------------------------------------------------------------------------------

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
// 
//------------------------------------------------------------------------------
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();
  PJOUT |= LED1;                            // Turn LED 1 on to indicate boot
  Init_Timers();                            // Initialize Timers
  five_msec_sleep(50);                      // 250 msec delay for the clock to settle
  Init_LCD();                               // Initialize LCD
  five_msec_sleep(75);                      // 375 msec delay for the clock to settle
  Init_LEDs();                              // Initialize LEDs
   
    
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                            // Can the Operating system run
  
  Switches_Process();                       // Check for switch state change 

 }
//------------------------------------------------------------------------------
}





