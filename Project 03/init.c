//------------------------------------------------------------------------------
// File Name : init.c
// 
// Description: This file contains the Initialization calls for the different sub systems
//
//  Mattia Muller
//  Sep 2014
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

#include "macros.h"
#include "functions.h"
#include "msp430.h"

extern volatile unsigned int Time_Sequence;

//------------------------------------------------------------------------------
// Initialization of all the Ports
//------------------------------------------------------------------------------
void Init_Ports(void){ //This calls the rest of the initialization functions
  Init_Port1();
  Init_Port2();
  Init_Port3(' ');
  Init_Port4();
  Init_PortJ();
}

void Init_Conditions(void){
//------------------------------------------------------------------------------
// Initializations Configurations
//------------------------------------------------------------------------------
// Interrupts are disabled by default, enable them. 
  enable_interrupts();

//------------------------------------------------------------------------------
}

void Init_Timers(void){
  Time_Sequence = 0;                        
// 
//******************************************************************************
//------------------------------------------------------------------------------
// Timer Configurations
//------------------------------------------------------------------------------
//  Init_Timer_A0(); //
//  Init_Timer_A1(); // 
//  Init_Timer_B0(); // 
//  Init_Timer_B1(); //  
  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
//******************************************************************************
}

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on all 8 LEDs
  PJOUT &= ~LED1;
  PJOUT &= ~LED2;
  PJOUT &= ~LED3;
  PJOUT &= ~LED4;
  P3OUT &= ~LED5;
  P3OUT &= ~LED6;
  P3OUT &= ~LED7;
  P3OUT &= ~LED8;
//------------------------------------------------------------------------------
}