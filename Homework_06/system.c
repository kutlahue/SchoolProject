//------------------------------------------------------------------------------
// System Configurations

// Tells the compiler to provide the value in reg as an input to an 
// inline assembly block.  Even though the block contains no instructions,
// the compiler may not optimize it away, and is told that the value
// may change and should not be relied upon.
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"

//=========================================================================== 
// Function name: enable_interrupts
//
// Description: This function enables interrupts
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1) 
//===========================================================================
void enable_interrupts(void){
//------------------------------------------------------------------------------
  __bis_SR_register(GIE);     // enable interrupts
//------------------------------------------------------------------------------
}

