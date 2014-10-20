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
extern volatile unsigned char what_to_do;
extern volatile unsigned int Time_Sequence;

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
  
  P3OUT |= R_REVERSE;
  P3OUT &= ~R_REVERSE;
  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                            // Can the Operating system run
	 Switches_Process(); 
	 switch(what_to_do){
		 case LED_STATE:
                        //Default_Process();
                        
			break;
	 	case RW_FOR_ON:
			if(!(P3IN & R_FORWARD)){
			P3OUT &= ~R_REVERSE;
			P3OUT |= R_FORWARD;
			}
	 		break;
	 	case RW_FOR_OFF:
			if(P3IN & R_FORWARD){
			P3OUT &= ~R_REVERSE;
			P3OUT &= ~R_FORWARD; 
			}
	 	break;
	 	case LW_FOR_ON:
			if(!(P3IN & L_FORWARD)){
			P3OUT &= ~L_REVERSE;
			P3OUT |= L_FORWARD;
			}
	 	break;
	 	case LW_FOR_OFF:
			if(P3IN & L_FORWARD){
			P3OUT &= ~L_REVERSE;
			P3OUT &= ~L_FORWARD;
			}
	 	break;
	 	case RW_REV_ON:
			if(!(P3IN & R_REVERSE)){
			P3OUT &= ~R_FORWARD;
			P3OUT |= R_REVERSE; 
			}
	 	break;
	 	case RW_REV_OFF:
			if(P3IN & R_REVERSE){
			P3OUT &= ~R_REVERSE;
			P3OUT &= ~R_FORWARD; 
			}
	 	case LW_REV_ON:
			if(!(P3IN & L_REVERSE)){
			P3OUT &= ~L_FORWARD;
			P3OUT |= L_REVERSE; 
			}
	 	break;
	 	case LW_REV_OFF:
			if(P3IN & L_REVERSE){
			P3OUT &= ~L_FORWARD;
			P3OUT &= ~L_REVERSE;
			}
	 	break;
		case STRAIGHT: // 1250 msec 
			STRAIGHT_TIME_Process();
		break;
                case PROJECT_04: // 1250 msec 
			//STRAIGHT_TIME_Process();
		break;
                case THUMB_WHEEL: // 1250 msec 
			CLOCK_TIME_Process();
		break;
		case CIRCLE: // 1250 msec 
			//CIRCLE_Process();
		break;
		case FIGURE_8: // 1250 msec 
		 	//FIGURE_8_Process();
		break;
		case TRIANGLE: // 1250 msec 
			//TRIANGLE_Process();
		break;
		default: 
		 	//Default_Process();
		break;
		}
         if(Time_Sequence > 250){
            Time_Sequence = 0;
         }
      	}
//------------------------------------------------------------------------------
}





