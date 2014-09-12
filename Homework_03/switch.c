#include "macros.h"
#include "msp430.h"
#include "functions.h"

unsigned char SW1_Debounce = SET_0, SW2_Debounce = SET_0;
extern char *display_1;
extern char *display_2;

void Switches_Process(void){
//------------------------------------------------------------------------------
// Switch Configurations
//------------------------------------------------------------------------------
  if (!(P4IN & SW1)){
    SW1_Debounce++;
    if (SW1_Debounce == DEBOUNCE_COUNTER){
      // Second letter
      //Current_Letter = display_2 + 0x01; // Should give me the address of the second
      //Current_Letter ^=
      P3OUT ^= (R_FORWARD);
      P3OUT |= TEST_PROBE;

      if (!(P3OUT & R_FORWARD)){
        if (!(P3OUT & L_FORWARD)){
          //           1234567890123456
          display_2 = "OFF          OFF";
        } else {
          //           1234567890123456
          display_2 = "OFF           ON";
        }
      } else {
        if (!(P3OUT & L_FORWARD)){
          //           1234567890123456
          display_2 = "ON           OFF";
        } else {
          //           1234567890123456
          display_2 = "ON            ON";
        }
      }
      //lcd_clear();
  //           1234567890123456
  display_1 = "Lt  Forward   Rt";
      lcd_out(display_1,LCD_LINE_1);       // 16 characters max between quotes - line 1
      lcd_out(display_2,LCD_LINE_2);        // 16 characters max between quotes - line 2
      SW1_Debounce = SET_0;
      five_msec_sleep(DEBOUNCE_TIMER);
    }
  }
  if (!(P4IN & SW2)) {
    SW2_Debounce++;
    if (SW2_Debounce == DEBOUNCE_COUNTER){
      P3OUT ^= (L_FORWARD);
      P3OUT |= TEST_PROBE;

      if (!(P3OUT & R_FORWARD)){
        if (!(P3OUT & L_FORWARD)){
          //           1234567890123456
          display_2 = "OFF          OFF";
        } else {
          //           1234567890123456
          display_2 = "OFF           ON";
        }
      } else {
        if (!(P3OUT & L_FORWARD)){   
          //           1234567890123456
          display_2 = "ON           OFF";
        } else {
       //              1234567890123456
          display_2 = "ON            ON";
        }
      }
      //lcd_clear();
   //              1234567890123456
    display_1 = "Lt  Forward   Rt";
      lcd_out(display_1,LCD_LINE_1);       // 16 characters max between quotes - line 1
      lcd_out(display_2,LCD_LINE_2);        // 16 characters max between quotes - line 2
      SW2_Debounce = SET_0;
      five_msec_sleep(DEBOUNCE_TIMER);
    }
  }
//------------------------------------------------------------------------------
}