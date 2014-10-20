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
volatile char okay_to_look_at_switch1 = NOT_OKAY;
volatile char okay_to_look_at_switch2 = NOT_OKAY;
volatile char sw1_position = RELEASED;
volatile char sw2_position = RELEASED;
volatile int count_debounce_SW1 = SET_0;
volatile int count_debounce_SW2 = SET_0;


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
            lcd_out(" SW1 Interrupt  ",LCD_LINE_2);                
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
            lcd_out(" SW2 Interrupt  ",LCD_LINE_2);                
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
