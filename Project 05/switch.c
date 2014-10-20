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

extern char *display_1, current_step;
extern char *display_2;
volatile char okay_to_look_at_switch1 = NOT_OKAY;
volatile char okay_to_look_at_switch2 = NOT_OKAY;
volatile char sw1_position = RELEASED;
volatile char sw2_position = RELEASED;
volatile int count_debounce_SW1 = SET_0;
volatile int count_debounce_SW2 = SET_0;
extern char current_step, what_to_do;
extern volatile unsigned char stop, straight_direction;
extern volatile int time_limit;

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
	if (!sw1_position){
            sw1_position = RELEASED;
             okay_to_look_at_switch1 = NOT_OKAY;
             PJOUT &=~LED3;
                                    current_step = SET_0;

            do_stuff();              
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
		if (!sw2_position){
            sw2_position = RELEASED;
             okay_to_look_at_switch2 = NOT_OKAY;
             PJOUT &=~LED3;
             current_step++;   
            do_stuff();              
             
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


// timerA0-1,2,overflow Interrupt Vector (TAIV) handler
#pragma vector=PORT4_VECTOR
__interrupt void PORT4_VECTOR_ISR(void){

  switch(P4IV)
    {
      case P4IV_P4IFG0:        
        disableInput();               
        sw1_position = RELEASED;
        okay_to_look_at_switch1 = OKAY;
        count_debounce_SW1 = SET_0;
        PJOUT |=LED3;
        break;
          
      case P4IV_P4IFG1:
        disableInput();               
        sw2_position = RELEASED;
        okay_to_look_at_switch2 = OKAY;
        count_debounce_SW2 = SET_0;
        PJOUT |=LED3;
      default:
        break;
    }  
  

}
// timerA0
//=============================================================================


//=========================================================================== 
// Function name: disableInput
//
// Description: This function disables of SW1 and SW2
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
void disableInput(void)
{

  P4IE &= ~(SW1 | SW2);                     // P4.0 interrupt disabled
  P4IFG = SET_0;                            // P4 IFG cleared  
}

//=========================================================================== 
// Function name: enableInput
//
// Description: This function enables SW1 and SW2
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
void enableInput(void)
{

  P4IE |= (SW1 | SW2);                     // P4.0 interrupt disabled
  P4IFG = SET_0;                           // P4 IFG cleared  
}



void do_stuff(void){
  switch(what_to_do){
		case CALIBRATE:
                       IR_calibration(current_step);
                       char* ascii_value = itoa(current_step);            
                       lcd_out("              ", LCD_LINE_2);   
                       lcd_out(ascii_value, LCD_LINE_2);     
                break;
		case STRAIGHT: // 1250 msec 
			STRAIGHT_TIME_Process();
		break;
                case PROJECT_05: // 1250 msec 
                        fifty_msec_sleep_A1(SET_10);
                        stop = OFF;
                        straight_direction = FORWARD;
                        current_step = SET_0;
                        time_limit = SET_NEG_1;
			what_to_do = PROJECT_05;
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
  
  
}
