//******************************************************************************
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"

// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define LED1                 (0x01) // LED 1
#define BLINK_LED            (0x01) // Allow LED to Blink
#define CNTL_STATE_INDEX        (3) // Control States
#define LCD_LINE_1           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_LINE_2           (0xC0) // Position Cursor at Character 01 of Line 2
#define GPS_ONOFF            (0x08) //
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x08) // LED 4
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CNTL_STATE_INDEX        (3)
#define LCD_BACKLITE         (0x08) // TEST_PROBE


// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
extern char *display_1;
extern char *display_2;
extern volatile char switch_states;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
// 
//------------------------------------------------------------------------------
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();
  PJOUT |= LED1;                            // Turn LED 1 on to indicate boot
  Time_Sequence = 0;                        // 
  Init_Timers();                            // Initialize Timers
  Init_LEDs();                              // Initialize LEDs
  Init_LCD();                               // Initialize LCD
  
//               1234567890123456
    display_1 = "   N.C. State   ";
    display_2 = "    ECE-306     ";


//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                            // Can the Operating system run
  switch(Time_Sequence){
    case 250:                               // 1000 msec  
      if(one_time){
        Init_LEDs();                        // Initialize LEDs
        one_time = 0;
      }
      Time_Sequence = 0;                    // 
    case 200:                               // 1000 msec  
      if(one_time){
        PJOUT |= LED4;                      // Change State of LED 4
        P3OUT |= LED5;                      // Change State of LED 5
        one_time = 0;
      }
    case 150:                               // 750 msec  
      if(one_time){
        PJOUT |= LED3;                      // Change State of LED 3
        P3OUT |= LED6;                      // Change State of LED 6
        one_time = 0;
      }
    case 100:                               // 500 msec  
      if(one_time){
        PJOUT |= LED2;                      // Change State of LED 2
        P3OUT |= LED7;                      // Change State of LED 7
        one_time = 0;
      }
    case  50:                               // 250 msec  
      if(one_time){
        PJOUT |= LED1;                      // Change State of LED 1
        P3OUT |= LED8;                      // Change State of LED 8
        one_time = 0;
      }
      Display_Process();
      break;                                // 
    default: break; 
  }
  Switches_Process();                       // Check for switch state change 
  if(Time_Sequence > 250){
    Time_Sequence = 0;
  }
 }
//------------------------------------------------------------------------------
}

void Init_Conditions(void){
//------------------------------------------------------------------------------
// Initializations Configurations
//------------------------------------------------------------------------------
// Interrupts are disabled by default, enable them. 
  enable_interrupts();

//------------------------------------------------------------------------------
}

void Switches_Process(void){
//------------------------------------------------------------------------------
  if (switch_states & SW1){
    switch_states &= ~SW1;
//               1234567890123456
    display_1 = "   N.C. State   ";
    display_2 = "    ECE-306     ";
    }

  if (switch_states & SW2) {
    switch_states &= ~SW2;
//               1234567890123456
    display_1 = "Embedded Systems";
    display_2 = "     Rock!      ";
    }
//------------------------------------------------------------------------------
}

void Init_Timers(void){
//------------------------------------------------------------------------------
// Timer Configurations
//------------------------------------------------------------------------------
//  Init_Timer_A0(); //
//  Init_Timer_A1(); // 
//  Init_Timer_B0(); // 
//  Init_Timer_B1(); //  
  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
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


