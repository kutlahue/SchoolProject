//------------------------------------------------------------------------------
//  File Name : timers.c
//
//  Description: This file contains the timer control functions
//
//  Mattia Muller
//  Sep 2014
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------


#include "macros.h"

volatile unsigned int Time_Sequence;
volatile unsigned int five_msec_count;
volatile char one_time;


//=========================================================================== 
// Function name: usleep10
//
// Description: This function is comparable to a classical sleep function
//
// Passed : usec - the amount of usec we want to sleep
// Locals: no variables declared
// Returned: no values returned
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) 
//===========================================================================
void usleep10(unsigned int usec){
//******************************************************************************
//------------------------------------------------------------------------------
// At the current clock rate this yields about 10usec per value passed
// A value of  0 yields 1.37 uSec
// A value of  1 yields 1.87 uSec
// A value of  2 yields 2.36 uSec
// A value of  3 yields 2.86 uSec
// A value of  4 yields 3.36 uSec
// A value of  5 yields 3.86 uSec
// A value of  6 yields 4.36 uSec
// A value of  7 yields 4.85 uSec
// A value of  8 yields 5.354 uSec
// A value of  9 yields 5.854 uSec
// A value of 10 yields 6.353 uSec
// A value of 11 yields 6.851 uSec
// A value of 12 yields 7.351 uSec
// A value of 13 yields 7.849 uSec
// A value of 14 yields 8.350 uSec
// A value of 15 yields 8.849 uSec
// A value of 16 yields 9.342 uSec
// A value of 17 yields 9.84 uSec
// A value of 18 yields 10.34 uSec
// A value of 19 yields 10.84 uSec
  int i,j;
  for(j=SET_0;j<usec;j++){
    for(i=SET_0;i<USLEEP_TIMER;i++);
  }
//------------------------------------------------------------------------------
//******************************************************************************
}

//=========================================================================== 
// Function name: five_msec_sleep
//
// Description: This function is comparable to a classical sleep function
//
// Passed : fivemsec - the amount of 5 msec we want to sleep
// Locals: no variables declared
// Returned: no values returned
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) 
//===========================================================================
void five_msec_sleep(unsigned int fivemsec){
//------------------------------------------------------------------------------
//Each count passed is at least x times 5 milliseconds
  five_msec_count = SET_0;
  while(fivemsec > (five_msec_count+SET_1));
//------------------------------------------------------------------------------
}

//=========================================================================== 
// Function name: TimerB0code
//
// Description: This function interrupts the timer B0
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) 
//===========================================================================
void TimerB0code(void){
//------------------------------------------------------------------------------
// Timer B0 interrupt code
//------------------------------------------------------------------------------
  Time_Sequence++;
  one_time = 1;
  if (five_msec_count < B0_COUNTER){
    five_msec_count++;
  }
//------------------------------------------------------------------------------
}