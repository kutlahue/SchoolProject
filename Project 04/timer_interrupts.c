//------------------------------------------------------------------------------
//  File Name: timer_interupts.c
//
//  Description: This file contains the interupts for the timers
//
//  Mattia Muller
//  Oct 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------


#include "macros.h"
#include "msp430.h"

//------------------------------------------------------------------------------
// Interrupt Configurations
// The following interrupt service routine shells are for the MSP430FR5739
// Other family members of the MSP430 may contain a different mix of timers.
//=============================================================================
// timerA0
// This block is generically refered to as timerA0 which contains 3 capture
// compare interrupts and 1 overflow interrupt. 
// timerA0-0 has its own interrupt.
// timerA0-1,2,overflow share an interrupt vector
// timerA0-0 Interrupt handler
volatile unsigned int time = SET_0;
extern volatile unsigned char what_to_do, stop, straight_direction, state = SET_0;
#pragma vector = TIMER0_A0_VECTOR      // Note the vector name is misleading


//=========================================================================== 
// Function name: Timer0_A0_ISR
//
// Description: This function handles the timer interupt for A0
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: what_to_do, stop, straight_direction, state, time, vector
//
// Author: Mattia Muller
// Date: Oct 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) 
//===========================================================================
__interrupt void Timer0_A0_ISR(void){
// timerA0-0 interrupt service routine used ???
// *** add your code here *** 
  time++;
  
  if (time >TWOSEC)
     time = SET_0;
  
  if (stop) {
    P3OUT&=~R_REVERSE;
    P3OUT&=~L_REVERSE;
    P3OUT&=~R_FORWARD;
    P3OUT&=~L_FORWARD;
    if (time==HALFSEC) {
      stop = SET_0;
      time = SET_0;
    }  
  } else {
      if (time==TWOSEC && what_to_do == PROJECT_04){
        what_to_do = STRAIGHT;
        straight_direction = SET_1;
        stop = SET_1;
        time = SET_0;
        state = SET_0;
       } else if (time==ONESEC && what_to_do == STRAIGHT && straight_direction == SET_1 && state == SET_0){
        straight_direction = SET_0;
        stop = SET_1;
        time = SET_0;
        state = SET_1;
      } else if (time==TWOSEC && what_to_do == STRAIGHT && straight_direction == SET_0){
        straight_direction = SET_1;
        stop = SET_1;
        time = SET_0;
        state = SET_1;
      } else if (time==ONESEC && what_to_do == STRAIGHT && straight_direction == SET_1  && state == SET_1){
        straight_direction = SET_0;
        stop = SET_1;
        time = SET_0;
        state = SET_1;
        what_to_do = THUMB_WHEEL;
      } else if (time==ONESEC && what_to_do == THUMB_WHEEL && straight_direction == SET_0){
        straight_direction = SET_1;
        stop = SET_1;
        time = SET_0;
        what_to_do = THUMB_WHEEL;
      } else if (time==ONESEC && what_to_do == THUMB_WHEEL && straight_direction == SET_1){
        straight_direction = SET_0;
        stop = SET_1;
        time = SET_0;
        what_to_do = LED_STATE;
      }
  }
  TA0CCR0 += TA0CCR0_INTERVAL;         // Add Offset to TACCR0 [continuous up mode]
}
