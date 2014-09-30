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
char count_time, straight_direction = SET_0, left_wheel_on = SET_0, right_wheel_on = SET_0, left_wheel_count, right_wheel_count, next_move = SET_0;

//******************************************************************************
//------------------------------------------------------------------------------
void shape_LED_STATE(void){
	int i;					  //1234567890123456
	char *Line1_LED_STATE = "  LEDs Blinking ";
	for(i=0;i<=(sizeof(Line1_LED_STATE)-1);i++){
		display_1=Line1_LED_STATE;
	}
	lcd_out(display_1,LCD_LINE_1);//16charactersmaxbetweenquotes-line1
	shape_Blank();
}
//******************************************************************************
//------------------------------------------------------------------------------
//******************************************************************************
//------------------------------------------------------------------------------
void shape_Blank(void){
		int i;				  //1234567890123456
		char *Line2_BLANK = "                ";
		for(i=0;i<=(sizeof(Line2_BLANK)-1);i++){
			display_2=Line2_BLANK;
		}
		lcd_out(display_2,LCD_LINE_2);//16charactersmaxbetweenquotes-line2
}
//------------------------------------------------------------------------------
//******************************************************************************
//------------------------------------------------------------------------------


void STRAIGHT_Process(void){
	if(count_time!=Time_Sequence){
		count_time=Time_Sequence;
		cycle_time++;
	}
	if(straight_direction){
		if(left_wheel_on++<left_wheel_count){
			if(!(P3IN&L_FORWARD)){
				P3OUT|=L_FORWARD;
			}
		}else{
			if(left_wheel_on<WHEEL_COUNT){
				left_wheel_on=0;
				if(P3IN&L_FORWARD){
					P3OUT&=~L_FORWARD;
				}
			}
		}
		if(right_wheel_on++<right_wheel_count){
			if(!(P3IN&R_FORWARD)){
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
		if(cycle_time>COMPLETE_STRAIGHT){
			P3OUT&=~R_REVERSE;
                        P3OUT&=~L_REVERSE;
			P3OUT&=~R_FORWARD;
			P3OUT&=~L_FORWARD;
			cycle_time=0;
                        while(cycle_time<10){
				if(count_time!=Time_Sequence){
					count_time=Time_Sequence;
					cycle_time++;
                                }
			}
			cycle_time=0;
			straight_direction=0;
		}

	}else{
		if(left_wheel_on++<LEFT_WHEEL_COUNT){
			if(!(P3IN&L_REVERSE)){
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
		if(cycle_time>COMPLETE_STRAIGHT){
                  cycle_time=0;
                  P3OUT&=~R_REVERSE;
                  P3OUT&=~L_REVERSE;
                  shape_LED_STATE();
                  what_to_do=LED_STATE;
		}
	}
}





void CIRCLE_Process(void){
	if(count_time!=Time_Sequence){
		count_time=Time_Sequence;
		cycle_time++;
	}
	if(left_wheel_on++<left_wheel_count){
		if(!(P3IN&L_FORWARD)){
			P3OUT|=L_FORWARD;
		}
	}else{
		if(left_wheel_on<WHEEL_COUNT){
			left_wheel_on=0;
			if(P3IN&L_FORWARD){
				P3OUT&=~L_FORWARD;
			}
		}
	}
	if(right_wheel_on++<right_wheel_count){
		if(!(P3IN&R_FORWARD)){
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

	if(cycle_time>COMPLETE_CIRCLE){
		cycle_time=0;
		P3OUT&=~R_FORWARD;
		P3OUT&=~L_FORWARD;
		while(cycle_time<10){
			if(count_time!=Time_Sequence){
				count_time=Time_Sequence;
				cycle_time++;
			}
		}
	what_to_do=LED_STATE;
	}
}


void TRIANGLE_Process(void){
	if(count_time!=Time_Sequence){
		count_time=Time_Sequence;
		cycle_time++;
	}
        
        if (!(next_move%2)){
          if(left_wheel_on++<LEFT_WHEEL_COUNT){
                  if(!(P3IN&L_FORWARD)){
                          P3OUT|=L_FORWARD;
                  }
          }else{
                  if(left_wheel_on<WHEEL_COUNT){
                          left_wheel_on=0;
                          if(P3IN&L_FORWARD){
                                  P3OUT&=~L_FORWARD;
                          }
                  }
          }
          if(right_wheel_on++<RIGHT_WHEEL_COUNT){
                  if(!(P3IN&R_FORWARD)){
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

          if(cycle_time>COMPLETE_STRAIGHT){
                  cycle_time=0;
                  P3OUT&=~R_FORWARD;
                  P3OUT&=~L_FORWARD;
                  while(cycle_time<10){
                          if(count_time!=Time_Sequence){
                                  count_time=Time_Sequence;
                                  cycle_time++;
                          }
                  }
                  cycle_time = 0;
                  next_move++;
                  if (next_move > 9 ) {
                    what_to_do=LED_STATE;
                    next_move = SET_0;
                  }
          }
        } else {
            if(left_wheel_on++<LEFT_WHEEL_COUNT_CIRCLE){
                    if(!(P3IN&L_FORWARD)){
                            P3OUT|=L_FORWARD;
                    }
            }else{
                    if(left_wheel_on<WHEEL_COUNT){
                            left_wheel_on=0;
                            if(P3IN&L_FORWARD){
                                    P3OUT&=~L_FORWARD;
                            }
                    }
            }
            if(right_wheel_on++<SET_0){
                    if(!(P3IN&R_FORWARD)){
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

            if(cycle_time>SIXTY_DEGREES){
                    cycle_time=0;
                    P3OUT&=~R_FORWARD;
                    P3OUT&=~L_FORWARD;
                    while(cycle_time<10){
                            if(count_time!=Time_Sequence){
                                    count_time=Time_Sequence;
                                    cycle_time++;
                            }
                    }
                    cycle_time = 0;
                    next_move++;

            }
        }
}


void FIGURE_8_Process(void){
  if (next_move==SET_0 || next_move==2) {
    left_wheel_count = LEFT_WHEEL_COUNT_CIRCLE;
    right_wheel_count = RIGHT_WHEEL_COUNT_CIRCLE;
    ONE_CIRCLE_Process(500);
  } else {
    left_wheel_count =  30;
    right_wheel_count = 1;
    ONE_CIRCLE_Process(350);
  }
  if (next_move > 3 ) {
    what_to_do=LED_STATE;
    next_move = SET_0;
  }
}


void ONE_CIRCLE_Process(int complete){
	if(count_time!=Time_Sequence){
		count_time=Time_Sequence;
		cycle_time++;
	}
	if(left_wheel_on++<left_wheel_count){
		if(!(P3IN&L_FORWARD)){
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

	if(cycle_time>complete){
		cycle_time=0;
                next_move++;
		P3OUT&=~R_FORWARD;
		P3OUT&=~L_FORWARD;
		while(cycle_time<10){
			if(count_time!=Time_Sequence){
				count_time=Time_Sequence;
				cycle_time++;
			}
		}
	}
}