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
#define DEBOUNCE_RESTART        (0) // Defines how many times the signal needs to bounce to be considered
#define DEBOUNCE_TIME          (20) // Defines how many times the signal needs to bounce to be considered
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
#define SET_NEG_1               (-1)
#define SET_2                   (2)
#define SET_4                   (4)
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

#define LEFT_WHEEL_COUNT 	 (30)
#define RIGHT_WHEEL_COUNT 	 (17)
#define LEFT_WHEEL_COUNT_CIRCLE 	(2)
#define RIGHT_WHEEL_COUNT_CIRCLE 	(22)
#define WHEEL_COUNT 		 (35)
#define COMPLETE_CIRCLE 	 (900)
#define COMPLETE_STRAIGHT 	 (60)
#define SIXTY_DEGREES            (140)
#define FIGURE_8_2                (450)

#define	LED_STATE			(0x01)
#define SERIAL  			(0x02)
#define RW_FOR_OFF			(0x03)
#define LW_FOR_ON			(0x04)
#define LW_FOR_OFF			(0x05)
#define RW_REV_ON			(0x06)
#define RW_REV_OFF			(0x07)
#define CALIBRATE			(0x08)
#define PROJECT_05			(0x09)
#define STRAIGHT			(0x0A)
#define PROJECT_04			(0x0B)
#define CIRCLE				(0x0C)
#define THUMB_WHEEL			(0x0D)
#define FIGURE_8			(0x0E)
#define TRIANGLE			(0x0F)

#define RELEASED			(0x01)
#define PRESSED				(0x00)
#define NOT_OKAY			(0x00)
#define OKAY				(0x01)

#define SET_10                          (10)

#define TA0CCR0_INTERVAL                (2500)
#define TA0CCR1_INTERVAL                (25000)
#define TA0CCR2_INTERVAL	        (5000)
#define ONESEC                          (200)
#define HALFSEC                         (100)
#define TWOSEC                          (400)


#define RESET_STATE                     (0x00)

#define Right_Detector                  (0)
#define Left_Detector                   (1)
#define Thumbwheel                      (2)

#define ON                              (1)
#define OFF                             (0)

#define FORWARD							(1)
#define REVERSE							(0)


#define STEP_0                          (0x00)
#define STEP_1                          (0x01)
#define STEP_2                          (0x02)
#define STEP_3                          (0x03)
#define STEP_4                          (0x04)

#define SET_8                           (8)
#define SET_100                         (100)
#define SET_250                         (250)
#define SET_20                          (20)
#define SET_800                         (800)
#define SET_1300                        (1300)
#define MENU1                           (250)
#define MENU2                           (500)
#define MENU3                           (750)
#define MENU4                           (1024)


#define SMALL_RING_SIZE                 (2)
#define LARGE_RING_SIZE                 (2)
#define BEGINNING                       (0)