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
#include "functions.h"

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
extern volatile unsigned char okay_to_look_at_switch1, okay_to_look_at_switch2, what_to_do, stop, straight_direction, state = SET_0, sw1_position, sw2_position;
extern volatile unsigned int five_msec_count_timer_A0, fifty_msec_count_timer_A1, count_debounce_SW1, count_debounce_SW2, ADC_Left_Detector;
extern volatile int time_limit;
volatile unsigned char ten_msec_count_timer_A2;

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
  five_msec_count_timer_A0++;
  
 
  
  if (time > time_limit && time_limit != SET_NEG_1) {
  	
  	stop = SET_1;	
  	
  }
  
  
  
   if (stop) {
    P3OUT&=~R_REVERSE;
    P3OUT&=~L_REVERSE;
    P3OUT&=~R_FORWARD;
    P3OUT&=~L_FORWARD;
  }
  
//    if (time==HALFSEC) {
//      stop = SET_0;
//      time = SET_0;
//    }  
//  } else {
//      if (time==TWOSEC && what_to_do == PROJECT_04){
//        what_to_do = STRAIGHT;
//        straight_direction = SET_1;
//        stop = SET_1;
//        time = SET_0;
//        state = SET_0;
//       } else if (time==ONESEC && what_to_do == STRAIGHT && straight_direction == SET_1 && state == SET_0){
//        straight_direction = SET_0;
//        stop = SET_1;
//        time = SET_0;
//        state = SET_1;
//      } else if (time==TWOSEC && what_to_do == STRAIGHT && straight_direction == SET_0){
//        straight_direction = SET_1;
//        stop = SET_1;
//        time = SET_0;
//        state = SET_1;
//      } else if (time==ONESEC && what_to_do == STRAIGHT && straight_direction == SET_1  && state == SET_1){
//        straight_direction = SET_0;
//        stop = SET_1;
//        time = SET_0;
//        state = SET_1;
//        what_to_do = THUMB_WHEEL;
//      } else if (time==ONESEC && what_to_do == THUMB_WHEEL && straight_direction == SET_0){
//        straight_direction = SET_1;
//        stop = SET_1;
//        time = SET_0;
//        what_to_do = THUMB_WHEEL;
//      } else if (time==ONESEC && what_to_do == THUMB_WHEEL && straight_direction == SET_1){
//        straight_direction = SET_0;
//        stop = SET_1;
//        time = SET_0;
//        what_to_do = LED_STATE;
//      }
//  }
  TA0CCR0 += TA0CCR0_INTERVAL;         // Add Offset to TACCR0 [continuous up mode]
}


// timerA0-1,2,overflow Interrupt Vector (TAIV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
  switch(__even_in_range(TA0IV,14)){
    case  0: break;                    // No interrupt
    case  2:                           // CCR1 used for fifity msec
      fifty_msec_count_timer_A1++;
      count_debounce_SW1++;
      count_debounce_SW2++;
      
      if (count_debounce_SW1 > SET_10 && okay_to_look_at_switch1) {
              sw1_position = PRESSED;
              PJOUT &=~LED3;
              enableInput();
      }
      if (count_debounce_SW2 > SET_10 && okay_to_look_at_switch2) {
              sw2_position = PRESSED;
              PJOUT &=~LED3;
              enableInput();
      }
      
      if (fifty_msec_count_timer_A1%DEBOUNCE_TIME  == SET_0){

        

      }
      TA0CCR1 += TA0CCR1_INTERVAL;     // Add Offset to TACCR1
      break;
    case  4:                           // CCR2 used for ???
    ten_msec_count_timer_A2++;
    ten_msec_timer_code_switch();
    TA0CCR2 += TA0CCR2_INTERVAL;     // Add Offset to TACCR2
      break;
    case  6: break;                    // reserved
    case  8: break;                    // reserved
    case 10: break;                    // reserved
    case 12: break;                    // reserved
    case 14:                           // overflow used for ???
// *** add your code here *** 
     break;
    default: break; 
  }
}
// timerA0
//=============================================================================




void ten_msec_timer_code_switch(void){
	
	switch (ten_msec_count_timer_A2){
                 case 101:
                ten_msec_count_timer_A2 = SET_0;
                break;
                case 100:
		
		  	// Do the 200 msec stuff
                  if (!(ADC10IE & ADC10IE0)) { // if ADC is disabled
				enableADC();
			}
                  break;
                  case 20:
		case 19: break;
		case 18: break;
		case 17: break;
		case 16: break;
		case 15:
			
                        break;
		case 14:
		case 13:
		case 12:
		case 11:
		case 10:
               
			// Do the 100 msec stuff
		case  9:
		case  8:
		case  7:
		case  6:
                case  5:
		case  4:
		case  3:
		case  2:
		case  1:
		  // Do the 10 msec stuff
		  break;
		default:
			
		  break;
	}	

}
