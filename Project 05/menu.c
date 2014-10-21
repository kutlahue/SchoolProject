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


volatile unsigned char what_to_do, shape_selection = SET_0, what_to_do_movement;
extern volatile unsigned int Time_Sequence, cycle_time, complete;
extern unsigned char count_time, straight_direction, left_wheel_on, right_wheel_on, left_wheel_count, right_wheel_count;



void select_menu(void){
	switch(shape_selection){
		case LED_STATE:
 			what_to_do = LED_STATE;
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
	
struct {  // let's define our menu structure
        unsigned int value;
        char* description;
        unsigned char action;
    } menu_list[] = {
        { 250, "   Project 4   ",  PROJECT_04},
        { 500, "   Project 5   ",  PROJECT_05},
        { 750, "    Calibrate   ",  CALIBRATE},
        { 1024, "    Menu 4     ", STRAIGHT }
    };

void menu_process(int adc_value){
  unsigned char i;
  char* display;
  for ( i=SET_0; i<4 && adc_value>=menu_list[i].value; i++) ;
  what_to_do =  menu_list[i].action;
  display = menu_list[i].description;
  lcd_out(display, LCD_LINE_1);
  
}