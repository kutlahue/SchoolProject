//------------------------------------------------------------------------------
//File Name: shape.c
//
//Description: This file contains the different preprogrammed shapes
//
//Mattia Muller
//Aug 2013
//Built with IAR Embedded Workbench Version:V4.10A/W32(5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"


extern volatile unsigned char what_to_do;
extern char *display_1;
extern char *display_2;
extern volatile unsigned int Time_Sequence;
volatile unsigned int cycle_time, complete;
char count_time,  left_wheel_on = SET_0, right_wheel_on = SET_0, left_wheel_count, right_wheel_count, next_move = SET_0;
volatile unsigned char straight_direction = SET_0, stop = SET_0;



//=========================================================================== 
// Function name: STRAIGHT_TIME_Process
//
// Description: This functions makes the car go forward or backwards
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: stop, straight_direction, left_wheel_on, left_wheel_count, right_wheel_on, right_wheel_count
//
// Author: Mattia Muller
// Date: Oct 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) 
//===========================================================================
void STRAIGHT_TIME_Process(void){
	if(straight_direction){
		if(left_wheel_on++<left_wheel_count){
			if(!(P3IN&L_FORWARD)){
                                P3OUT&=~L_REVERSE;
				P3OUT|=L_FORWARD;
			}
		}else{
			if(left_wheel_on<WHEEL_COUNT){
				left_wheel_on=SET_0;
				if(P3IN&L_FORWARD){
					P3OUT&=~L_FORWARD;
				}
			}
		}
		if(right_wheel_on++<right_wheel_count){
			if(!(P3IN&R_FORWARD)){
                                P3OUT&=~R_REVERSE;
				P3OUT|=R_FORWARD;
			}
		}else{
			if(right_wheel_on<WHEEL_COUNT){
				right_wheel_on=SET_0;
                                if(P3IN&R_FORWARD){
                                    P3OUT&=~R_FORWARD;
				}
			}
		}
		if(stop){
			P3OUT&=~R_REVERSE;
                        P3OUT&=~L_REVERSE;
			P3OUT&=~R_FORWARD;
			P3OUT&=~L_FORWARD;
		}

	}else{
		if(left_wheel_on++<LEFT_WHEEL_COUNT){
			if(!(P3IN&L_REVERSE)){
                                P3OUT&=~L_FORWARD;
				P3OUT|=L_REVERSE;
			}
		}else{
			if(left_wheel_on<WHEEL_COUNT){
                            left_wheel_on=0;
                            if(P3IN&L_REVERSE){
                              P3OUT&=~L_REVERSE;
                            }
			}
		}
		if(right_wheel_on++<RIGHT_WHEEL_COUNT){
                  if(!(P3IN&R_REVERSE)){
                        P3OUT&=~R_FORWARD;
			P3OUT|=R_REVERSE;
                  }
		}else{
                  if(right_wheel_on<WHEEL_COUNT){
			right_wheel_on=0;
                        if(P3IN&R_REVERSE){
                          P3OUT&=~R_REVERSE;
			}
                  }
		}
		if(stop){
                        P3OUT&=~R_REVERSE;
                        P3OUT&=~L_REVERSE;
			P3OUT&=~R_FORWARD;
			P3OUT&=~L_FORWARD;
		}
	}
}


//=========================================================================== 
// Function name: CLOCK_TIME_Process
//
// Description: This functions makes the car go CLOCKWISE OR COUNTER CLOCKWISE
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: stop, straight_direction, left_wheel_on, left_wheel_count, right_wheel_on, right_wheel_count
//
// Author: Mattia Muller
// Date: Oct 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) 
//===========================================================================
void CLOCK_TIME_Process(void){

  if(straight_direction){
		if(left_wheel_on++<left_wheel_count){
			if(!(P3IN&L_FORWARD)){
                                P3OUT&=~L_REVERSE;
				P3OUT|=L_FORWARD;
			}
		}else{
			if(left_wheel_on<WHEEL_COUNT){
				left_wheel_on=SET_0;
				if(P3IN&L_FORWARD){
					P3OUT&=~L_FORWARD;
				}
			}
		}
		if(right_wheel_on++<right_wheel_count){
			if(!(P3IN&R_REVERSE)){
                                P3OUT&=~R_FORWARD;
				P3OUT|=R_REVERSE;
			}
		}else{
			if(right_wheel_on<WHEEL_COUNT){
				right_wheel_on=SET_0;
                                if(P3IN&R_REVERSE){
                                    P3OUT&=~R_REVERSE;
				}
			}
		}
		if(stop){
			P3OUT&=~R_REVERSE;
                        P3OUT&=~L_REVERSE;
			P3OUT&=~R_FORWARD;
			P3OUT&=~L_FORWARD;
		}

	}else{
		if(left_wheel_on++<LEFT_WHEEL_COUNT){
			if(!(P3IN&L_REVERSE)){
                                P3OUT&=~L_FORWARD;
				P3OUT|=L_REVERSE;
			}
		}else{
			if(left_wheel_on<WHEEL_COUNT){
                            left_wheel_on=0;
                            if(P3IN&L_REVERSE){
                              P3OUT&=~L_REVERSE;
                            }
			}
		}
		if(right_wheel_on++<RIGHT_WHEEL_COUNT){
                  if(!(P3IN&R_FORWARD)){
                        P3OUT&=~R_REVERSE;
			P3OUT|=R_FORWARD;
                  }
		}else{
                  if(right_wheel_on<WHEEL_COUNT){
			right_wheel_on=0;
                        if(P3IN&R_FORWARD){
                          P3OUT&=~R_FORWARD;
			}
                  }
		}
		if(stop){
                        P3OUT&=~R_REVERSE;
                        P3OUT&=~L_REVERSE;
			P3OUT&=~R_FORWARD;
			P3OUT&=~L_FORWARD;
		}
	}
  
  
  
}