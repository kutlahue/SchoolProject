#include "macros.h"
#include "msp430.h"

//------------------------------------------------------------------------------
//Configure Port 1
// Port 1 Pins
// V_DETECT_R (0x01) //
// V_DETECT_L (0x02) //
// IR_LED (0x04) //
// V_THUMB (0x08) //
// SPI_CS_LCD (0x10) // LCD Chip Select
// RESET_LCD (0x20) // GPS Power Check from GPS
// SPI_SIMO (0x40) // SPI mode - slave in/master out of USCI_B0
// RS_LCD (0x80) // RS_LCD Command / Data selection
// Slave out not used for LCD, pin used as RS_LCD
// SOMI_B (0x80) // SPI mode - slave out/master in of USCI_B0
void Init_Port1(void){ 
 P1SEL0 = SET_0; // P1 set as I/0
 P1SEL1 = SET_0; // P1 set as I/0
 P1DIR = SET_0; // Set P1 direction to input
 P1SEL0 &= ~SPI_SIMO; // 0 SIMO_B selected
 P1SEL1 |= SPI_SIMO; // 1 SIMO_B selected
// P1SEL0 &= ~SOMI_B; // 0 SOMI_B is unused on the LCD
// P1SEL1 |= SOMI_B; // 1 SOMI_B is unused on the LCD
 P1SEL0 |= V_DETECT_R; // 1 V_DETECT_R selected
 P1SEL1 |= V_DETECT_R; // 1 V_DETECT_R selected
 P1SEL0 |= V_DETECT_L; // 1 V_DETECT_L selected
 P1SEL1 |= V_DETECT_L; // 1 V_DETECT_L selected
 P1SEL0 |= V_THUMB; // 1 V_THUMB selected
 P1SEL1 |= V_THUMB; // 1 V_THUMB selected
// P1DIR &= ~SOMI_B; // SOMI_B is unused on the LCD
 P1DIR |= SPI_SIMO; // 1 SIMO_B set to Output
 P1OUT &= ~RESET_LCD; // 0 P1 SPI_CS_LCD Port Pin set low
 P1DIR |= RESET_LCD; // 1 Set RESET_LCD output direction
 P1OUT |= SPI_CS_LCD; // 1 P1 SPI_CS_LCD Port Pin set high
 P1DIR |= SPI_CS_LCD; // 1 Set SPI_CS_LCD output direction
 P1OUT |= RS_LCD; // 1 P1 RS_LCD Port Pin set high
 P1DIR |= RS_LCD; // 1 Set RS_LCD output direction
 P1OUT &= ~IR_LED; // 0 P1 IR_LED Port Pin set low
 P1REN |= SPI_SIMO; // 1 Enable pullup resistor
 P1REN |= RS_LCD; // 1 Enable pullup resistor
 P1REN |= RESET_LCD; // 1 Enable pullup resistor
 P1REN |= SPI_CS_LCD; // 1 Enable pullup resistor
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Configure Port 2
// Port 2 Pins
// USB_TXD              (0x01) // Port 2 Pin 0 offset
// USB_RXD              (0x02) // Port 2 Pin 1 offset
// SPI_SCK              (0x04) // Port 2 Pin 2 offset
// CPU_TXD              (0x20) // Port 2 Pin 5 offset
// CPU_RXD              (0x40) // Port 2 Pin 6 offset
void Init_Port2(void) { 

    P2SEL0 = SET_0;
    P2SEL1 = SET_0;
    P2DIR = SET_0;
    P2OUT = SET_0;
  
    P2SEL0 &= ~(USB_TXD | USB_RXD | SPI_SCK | CPU_TXD | CPU_RXD); // Set specific pins as function
    P2SEL1 |= (USB_TXD | USB_RXD | SPI_SCK | CPU_TXD | CPU_RXD); // Set specific pins as function
    P2OUT |= SPI_SCK;
    P2REN |= SPI_SCK;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Configure Port 3
// Port 3 Pins
// X                    (0x01) // Port 3 Pin 0 offset
// Y                    (0x02) // Port 3 Pin 1 offset
// Z                    (0x04) // Port 3 Pin 2 offset
// TEST_PROBE           (0x08) // LCD BACKLIGHT
// R_FORWARD            (0x10) // Port 3 Pin 4 offset
// R_REVERSE            (0x20) // Port 3 Pin 5 offset
// L_FORWARD            (0x40) // Port 3 Pin 6 offset
// L_REVERSE            (0x80) // Port 3 Pin 7 offset
void Init_Port3(char clock_state) { //This function will initialize all pins in port 3.

    P3SEL0 = SET_0;
    P3SEL1 = SET_0;
    P3DIR = SET_0;
    P3OUT = SET_0;
  
    P3DIR |= (R_FORWARD | L_FORWARD | TEST_PROBE | R_REVERSE | L_REVERSE); // Set specific pins as output
    P3DIR &= ~(X | Y | Z ); // Set specific pins as input
    P3SEL0 &= ~(X | Y | Z | R_FORWARD | L_FORWARD | TEST_PROBE | R_REVERSE | L_REVERSE); // Set specific pins as GP I/O
    P3SEL1 &= ~(X | Y | Z | R_FORWARD | L_FORWARD | TEST_PROBE | R_REVERSE | L_REVERSE); // Set specific pins as GP I/O
    P3OUT &= ~(X | Y | Z | R_FORWARD | L_FORWARD | TEST_PROBE | R_REVERSE | L_REVERSE); // Set specific pins to 0
    
    
}
//------------------------------------------------------------------------------



//----------------------------------------------------------------
// Configure PORT 4
// Port 4 has only two pins
// Port 4 Pins
// SW1 (0x01) // Switch 1
// SW2 (0x02) // Switch 2
void Init_Port4(void){
   P4SEL0 = SET_0; // P4 set as I/0
   P4SEL1 = SET_0; // P4 set as I/0
   P4DIR = SET_0; // Set P4 direction to input
   P4DIR &= ~(SW1 | SW2); // Direction = input
   P4OUT = SET_0;
   P4OUT |= SW1 | SW2; // Configure pullup resistor
   P4REN |= SW1 | SW2; // Enable pullup resistor
   //P4IES |= SW1 | SW2; // P4.0 Hi/Lo edge interrupt
}
//----------------------------------------------------------------

//----------------------------------------------------------------
// Configure PORT J
// GPS_PWR              (0x01) // Port J Pin 0 offset
// GPS_RESET            (0x02) // Port J Pin 1 offset
// GPS_PWRCNTL          (0x04) // Port J Pin 2 offset
// GPS_PWRCHK           (0x08) // Port J Pin 3 offset
void Init_PortJ(void) { //This function will initialize all pins in port 3.

    PJSEL0 = SET_0;
    PJSEL1 = SET_0;
    PJDIR = SET_0;
    PJOUT = SET_0;
  
    PJDIR |= (GPS_PWR | GPS_RESET | GPS_PWRCNTL); // Set specific pins as output
    PJDIR &= ~(GPS_PWRCHK); // Set specific pins as input
    PJSEL0 &= ~(GPS_PWR | GPS_RESET | GPS_PWRCNTL | GPS_PWRCHK); // Set specific pins as GP I/O
    PJSEL1 &= ~(GPS_PWR | GPS_RESET | GPS_PWRCNTL | GPS_PWRCHK); // Set specific pins as GP I/O
    PJOUT &= ~(GPS_PWR | GPS_RESET | GPS_PWRCNTL | GPS_PWRCHK); // Set specific pins to 0
}
//----------------------------------------------------------------

