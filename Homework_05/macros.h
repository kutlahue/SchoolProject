//------------------------------------------------------------------------------
//  File Name : macros.h
//
//  Description: This file contains all the constants 
//
//  Mattia Muller
//  Sep 2014
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------


// Required defines
// In the event the universe no longer exists, this bit will reset
#define USLEEP_TIMER           (14) // Counter to simulate 1 usec
#define B0_COUNTER           (1000) // Counter for the TimerB0 function
#define INIT_TIMER             (75) // 375 msec delay
#define CSLOCK               (0x01) // Any incorrect password locks registers
#define MCLK_FREQ        (8000000L)
#define SMCLK_FREQ       (8000000L)
#define SMCLK_DIV              (64)
#define DEBOUNCE_COUNTER        (5) // Defines how many times the signal needs to bounce to be considered
#define DEBOUNCE_TIMER         (20) // Defines how many times the signal needs to bounce to be considered
#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define LCD_LINE_1           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_LINE_2           (0xC0) // Position Cursor at Character 01 of Line 2
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x08) // LED 4
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SET_0                   (0) // Set the state to 0
#define SET_1                   (1) // Set the state to 1
#define ERROR                   (1) // Return an error
#define V_DETECT_R           (0x01) // Port 1 Pin 0 offset
#define V_DETECT_L           (0x02) // Port 1 Pin 1 offset
#define IR_LED               (0x04) // Port 1 Pin 2 offset
#define V_THUMB              (0x08) // Port 1 Pin 3 offset
#define SPI_CS_LCD           (0x10) // Port 1 Pin 4 offset
#define RESET_LCD            (0x20) // Port 1 Pin 5 offset
#define SPI_SIMO             (0x40) // Port 1 Pin 6 offset
#define RS_LCD               (0x80) // Port 1 Pin 7 offset
#define USB_TXD              (0x01) // Port 2 Pin 0 offset
#define USB_RXD              (0x02) // Port 2 Pin 1 offset
#define SPI_SCK              (0x04) // Port 2 Pin 2 offset
#define CPU_TXD              (0x20) // Port 2 Pin 5 offset
#define CPU_RXD              (0x40) // Port 2 Pin 6 offset
#define X                    (0x01) // Port 3 Pin 0 offset
#define Y                    (0x02) // Port 3 Pin 1 offset
#define Z                    (0x04) // Port 3 Pin 2 offset
#define TEST_PROBE           (0x08) // Port 3 Pin 3 offset
#define R_FORWARD            (0x10) // Port 3 Pin 4 offset
#define R_REVERSE            (0x20) // Port 3 Pin 5 offset
#define L_FORWARD            (0x40) // Port 3 Pin 6 offset
#define L_REVERSE            (0x80) // Port 3 Pin 7 offset
#define SW1                  (0x01) // Port 4 Pin 0 offset
#define SW2                  (0x02) // Port 4 Pin 1 offset
#define GPS_PWR              (0x01) // Port J Pin 0 offset
#define GPS_RESET            (0x02) // Port J Pin 1 offset
#define GPS_PWRCNTL          (0x04) // Port J Pin 2 offset
#define GPS_PWRCHK           (0x08) // Port J Pin 3 offset
#define USE_R_FORWARD		 (0x00) // Use right wheel
#define USE_SMCLK			 (0x01) // Use the clock 