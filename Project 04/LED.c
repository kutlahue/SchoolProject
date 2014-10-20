//------------------------------------------------------------------------------
//  File Name : LED.c
// 
//  Description: This file contains the LED related functions after Initialization 
//
//  Mattia Muller
//  Sep 2014
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern volatile char one_time;
extern volatile unsigned int Time_Sequence;


void Default_Process(){
  switch(Time_Sequence){

 case 250: // 1250 msec 
 if(one_time){
 Init_LEDs(); // Initialize LEDs
 one_time = 0;
}
 Time_Sequence = 0; // 
 case 200: // 1000 msec 
 if(one_time){

 PJOUT |= LED4; // Change State of LED 4

// P3OUT |= LED5; // Change State of LED 5

 one_time = 0;

 

}

 case 150: // 750 msec 

 if(one_time){

 PJOUT |= LED3; // Change State of LED 3

// P3OUT |= LED6; // Change State of LED 6

 one_time = 0;

 

}

 case 100: // 500 msec 

 if(one_time){

 PJOUT |= LED2; // Change State of LED 2

// P3OUT |= LED7; // Change State of LED 7

 one_time = 0;

 

}

 case 50: // 250 msec 

 if(one_time){

 PJOUT |= LED1; // Change State of LED 1

// P3OUT |= LED8; // Change State of LED 8

 one_time = 0;

 

}

 break; // 

 default: break; 

 

}

 if(Time_Sequence > 250){

 Time_Sequence = 0;
}
}
