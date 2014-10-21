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


extern volatile unsigned char what_to_do, what_to_do_movement, sample;
extern char *display_1;
extern char *display_2;
extern volatile unsigned int Time_Sequence, five_msec_count_timer_A0, time;
volatile unsigned int cycle_time, complete;
unsigned char current_step=SET_0, count_time,  left_wheel_on = SET_0, right_wheel_on = SET_0, left_wheel_count, right_wheel_count, next_move = SET_0;
volatile unsigned char straight_direction = SET_0, stop = SET_0;
extern unsigned char black_space;
unsigned int distance = SET_0;
extern volatile int time_limit = SET_0;



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
		if(stop == ON){
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
		if(stop == ON){
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
		if(stop == ON){
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
		if(stop == ON){
                        P3OUT&=~R_REVERSE;
                        P3OUT&=~L_REVERSE;
			P3OUT&=~R_FORWARD;
			P3OUT&=~L_FORWARD;
		}
	}
}

void project_5_process(void){
	
	if(black_space == ON && stop == OFF && straight_direction == FORWARD && current_step == STEP_0)
      {
  
    
        P3OUT&=~R_REVERSE;
    P3OUT&=~L_REVERSE;
    P3OUT&=~R_FORWARD;
    P3OUT&=~L_FORWARD;
        
    five_msec_count_timer_A0 = SET_0;//Start distance timer
    distance = SET_0;
    five_msec_sleep(SET_100);	//Stop for .5 seconds
    disableADC();    				//Disable ADC for .5 seconds
    
    what_to_do_movement = STRAIGHT;
    time_limit = SET_NEG_1;
    stop = OFF;
    straight_direction = REVERSE;
    black_space = OFF;
    current_step++;
}

else if(black_space == ON && stop == OFF && straight_direction == REVERSE && current_step == STEP_1)
{
  
  
  P3OUT&=~R_REVERSE;
    P3OUT&=~L_REVERSE;
    P3OUT&=~R_FORWARD;
    P3OUT&=~L_FORWARD;
  
    five_msec_sleep(SET_100);
    what_to_do_movement = STRAIGHT;
    time_limit = five_msec_count_timer_A0 >> SET_2;	// distance time divided by 2
    five_msec_count_timer_A0 = SET_0;
    time = SET_0;
    straight_direction = FORWARD;
    black_space = OFF;
    stop = OFF;
    current_step++;
    sample = OFF;
}
else if(stop == ON && straight_direction == FORWARD && current_step == STEP_2)
{
  
  P3OUT&=~R_REVERSE;
    P3OUT&=~L_REVERSE;
    P3OUT&=~R_FORWARD;
    P3OUT&=~L_FORWARD;
  
    five_msec_sleep(SET_100);
    straight_direction = FORWARD;
    time_limit = 800; // 800 
    time = SET_0;
     stop = OFF;
    what_to_do_movement = THUMB_WHEEL;
    current_step++;
} else if(stop == ON && straight_direction == FORWARD && current_step == STEP_3) {
  
  P3OUT&=~R_REVERSE;
    P3OUT&=~L_REVERSE;
    P3OUT&=~R_FORWARD;
    P3OUT&=~L_FORWARD;
  
    straight_direction = REVERSE;
    
    time_limit = 1300; // 1300
    time = SET_0;
     stop = OFF;
    what_to_do_movement = THUMB_WHEEL;
    current_step++;
} else if(stop == ON && straight_direction == REVERSE && current_step == STEP_4) {
    stop = SET_1;
}
  
}
