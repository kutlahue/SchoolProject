//------------------------------------------------------------------------------
//  File Name : switch.c
//
//  Description: This file contains the switch control functions
//
//  Mattia Muller
//  Sep 2014
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------


#include "macros.h"
#include "msp430.h"
#include "functions.h"

extern char *display_1;
extern char *display_2;
char okay_to_look_at_switch1 = OKAY;
char okay_to_look_at_switch2 = OKAY;
char sw1_position = RELEASED;
char sw2_position = RELEASED;
char count_debounce_SW1 = SET_0;
char count_debounce_SW2 = SET_0;


//=========================================================================== 
// Function name: Switch1_Process
//
// Description: This function handles the detection of SW1
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: none
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) //===========================================================================
void Switch1_Process(void){
	if (okay_to_look_at_switch1 && sw1_position){
		if (!(P4IN & SW1)){
			 sw1_position = PRESSED;
			 okay_to_look_at_switch1 = NOT_OKAY;
			 count_debounce_SW1 = DEBOUNCE_RESTART;
			 shape_menu();
		}
 	}
 	if (count_debounce_SW1 <= DEBOUNCE_TIME){
 		count_debounce_SW1++;
 	}else{
 		okay_to_look_at_switch1 = OKAY;
 		if (P4IN & SW1){
 			sw1_position = RELEASED;
 		}
 	}
}


//=========================================================================== 
// Function name: Switch2_Process
//
// Description: This function handles the detection of SW2
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: none
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) //===========================================================================
void Switch2_Process(void){
	if (okay_to_look_at_switch2 && sw2_position){
		if (!(P4IN & SW2)){
			 sw2_position = PRESSED;
			 okay_to_look_at_switch2 = NOT_OKAY;
			 count_debounce_SW2 = DEBOUNCE_RESTART;
			 select_menu();
		}
 	}
 	if (count_debounce_SW2 <= DEBOUNCE_TIME){
 		count_debounce_SW2++;
 	}else{
 		okay_to_look_at_switch2 = OKAY;
 		if (P4IN & SW2){
 			sw2_position = RELEASED;
 		}
 	}
}

//=========================================================================== 
// Function name: Switches_Process
//
// Description: This function handles the detection of SW1 and SW2
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: none
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) //===========================================================================
//******************************************************************************
//------------------------------------------------------------------------------
void Switches_Process(void){
 Switch1_Process();
 Switch2_Process();
} 
//------------------------------------------------------------------------------
//******************************************************************************