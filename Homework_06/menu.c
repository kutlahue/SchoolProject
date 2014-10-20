//------------------------------------------------------------------------------
//  File Name : menu.c
//
//  Description: This file contains the menu control functions
//
//  Mattia Muller
//  Sep 2014
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------


#include "macros.h"
#include "msp430.h"
#include "functions.h"


volatile unsigned char what_to_do, shape_selection = SET_0;
extern volatile unsigned int Time_Sequence, cycle_time, complete;
extern char count_time, straight_direction, left_wheel_on, right_wheel_on, left_wheel_count, right_wheel_count;



void select_menu(void){
	switch(shape_selection){
		case LED_STATE:
 			what_to_do = LED_STATE;
 			break;
 		case RW_FOR_ON:
 			what_to_do = RW_FOR_ON;
 			break;
 		case RW_FOR_OFF:
 			what_to_do = RW_FOR_OFF;
 			break;
 		case LW_FOR_ON:
 			what_to_do = LW_FOR_ON;
 			break;
 		case LW_FOR_OFF:
 			what_to_do = LW_FOR_OFF;
 			break;
 		case RW_REV_ON:
 			what_to_do = RW_REV_ON;
 			break;
 		case RW_REV_OFF:
 			what_to_do = RW_REV_OFF;
 			break;
 		case LW_REV_ON:
 			what_to_do = LW_REV_ON;
 			break;
 		case LW_REV_OFF:
 			what_to_do = LW_REV_OFF;
 			break;
 		case STRAIGHT:
 			what_to_do = STRAIGHT;
 			left_wheel_count = LEFT_WHEEL_COUNT;
 			right_wheel_count = RIGHT_WHEEL_COUNT;
 			break;
 		case PROJECT_04:
 			what_to_do = PROJECT_04;
                        left_wheel_count = LEFT_WHEEL_COUNT;
 			right_wheel_count = RIGHT_WHEEL_COUNT;
 			break;
 		case CIRCLE:
 			what_to_do = CIRCLE;
 			left_wheel_count = LEFT_WHEEL_COUNT_CIRCLE;
 			right_wheel_count = RIGHT_WHEEL_COUNT_CIRCLE;
 			cycle_time = 0;
 			break;
 		case THUMB_WHEEL:
 			what_to_do = THUMB_WHEEL;
 			break;
                case TRIANGLE:
                        what_to_do = TRIANGLE;
                        cycle_time = 0;
 			break;
                case FIGURE_8:
                        what_to_do = FIGURE_8; 
			cycle_time = 0;
                        break;
	}
} 

//---------------------------------------------------
void shape_menu(void){
	shape_selection++;
	if(shape_selection > TRIANGLE){
 		shape_selection = LED_STATE;
 	}
 	switch(shape_selection){
 		case LED_STATE:
 			//shape_LED_STATE();
 			break;
 		case RW_FOR_ON:
                          lcd_out(" RT FW ON  ",LCD_LINE_1);
			 //shape_On();
			 break;
 		case RW_FOR_OFF:
                          lcd_out(" RT FW OFF  ",LCD_LINE_1);
			 //shape_OFF();
			 break;
 		case LW_FOR_ON:
                          lcd_out(" LT FW ON  ",LCD_LINE_1);
			 //shape_On();
			 break;
 		case LW_FOR_OFF:
                          lcd_out(" LT FW OFF  ",LCD_LINE_1);
			 //shape_OFF();
			 break;
 		case RW_REV_ON:
                          lcd_out(" RT REV ON  ",LCD_LINE_1);
			 //shape_On();
			 break;
		case RW_REV_OFF:
                          lcd_out(" RT REV OFF  ",LCD_LINE_1);
			 //shape_OFF();
			 break;
 		case LW_REV_ON:
                          lcd_out(" LT REV ON  ",LCD_LINE_1);
			 //shape_On();
			 break;
 		case LW_REV_OFF:
                          lcd_out(" LT FW OFF  ",LCD_LINE_1);
			 //shape_OFF();
			 break;
 		case STRAIGHT:
                          lcd_out("  Straight  ",LCD_LINE_1);
			 break;
 		case CIRCLE:
                            lcd_out("  Circle  ",LCD_LINE_1);
 			break;
 		case FIGURE_8:
                          lcd_out(" Figure 8  ",LCD_LINE_1);
			 break;
 		case TRIANGLE:
                          lcd_out(" Triangle  ",LCD_LINE_1);
 			break;
                case PROJECT_04:
                          lcd_out("   PROJECT 04       ",LCD_LINE_1);
 			break;
 	}
//-----------------------------------------------------
}
	
	