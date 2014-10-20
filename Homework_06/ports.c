//------------------------------------------------------------------------------
//  File Name : ports.c 
//
//  Description: This file contains the Port related Initializations
//
//  Mattia Muller
//  Sep 2014
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------


#include "macros.h"
#include "msp430.h"

//=========================================================================== 
// Init_Port1
// Purpose: Initialize Port 1
//
// Various options for Pin 0
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0	1		0		- TA0 CCR1 capture: CCI1A input
// 0	1		1		- TA0 CCR1 compare: Out1
// 1	0		0		- External DMA trigger
// 1	0		1		- RTC clock calibration output
// 1	1		X		- Analog input A0 - ADC, Comparator_D input CD0, Vref- External applied reference
// 
// Various options for Pin 1
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0	1		0		- TA0 CCR1 capture: CCI1A input
// 0	1		1		- TA0 CCR1 compare: Out1
// 1	0		0		- External DMA trigger
// 1	0		1		- RTC clock calibration output
// 1	1		X		- Analog input A0 - ADC, Comparator_D input CD1, Vref- External applied reference
// 
// Various options for Pin 2
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0	1		0		- TA0 CCR1 capture: CCI1A input
// 0	1		1		- TA0 CCR1 compare: Out1
// 1	0		0		- External DMA trigger
// 1	0		1		- RTC clock calibration output
// 1	1		X		- Analog input A2 - ADC, Comparator_D input CD2
//
// Various options for Pin 3
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0	1		0		- TA0 CCR1 capture: CCI1A input
// 0	1		1		- TA0 CCR1 compare: Out1
// 1	0		0		- External DMA trigger
// 1	0		X		- Slave transmit enable - eUSCI_B0 SPI mode
// 1	1		X		- Analog input A3 - ADC, Comparator_D input CD3
//
// Various options for Pin 4
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0	1		0		- TA0 CCR1 capture: CCI1A input
// 0	1		1		- TA0 CCR1 compare: Out1
// 1	0		0		- External DMA trigger
// 1	0		X		- Slave transmit enable - eUSCI_A0 SPI mode
// 1	1		X		- Analog input A4 - ADC, Comparator_D input CD4 
//
// Various options for Pin 5
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0	1		0		- TA0 CCR1 capture: CCI1A input
// 0	1		1		- TA0 CCR1 compare: Out1
// 1	0		0		- External DMA trigger
// 1	0		X		- Clock signal input - eUSCI_A0 SPI slave, Clock signal output - eUSCI_A0 SPI master
// 1	1		X		- Analog input A5 - ADC, Comparator_D input CD5
//
// Various options for Pin 6
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0	1		0		- TA0 CCR1 capture: CCI1A input
// 0	1		1		- TA0 CCR1 compare: Out1
// 1	0		X		- *Slave in, master out - eUSCI_B0 SPI mode, I2C data - eUSCI_B0 I2C mode
// 1	0		1		- TA0 CCR0 capture: CCI0A input
// 1	1		1		- TA0 CCR0 compare: Out0
//
// Various options for Pin 7
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0	1		0		- TA0 CCR1 capture: CCI1A input
// 0	1		1		- TA0 CCR1 compare: Out1
// 1	0		X		- Slave out, master in - eUSCI_B0 SPI mode, I2C clock - eUSCI_B0 I2C mode
// 1	0		1		- TA1 CCR0 capture: CCI0A input
// 1	1		1		- TA1 CCR0 compare: Out0
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0 
//-----------------------------------------------------------------------------
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

//=========================================================================== 
// Init_Port2
// Purpose: Initialize Port 2
//
// Various options for Pin 0
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 0	1		X		- UCA0TXD/UCA0SIMO
// 1	0		0		- TB2.CCI0A 
// 1	0		1		- TB2.0 
// 1	1		0		- TB0CLK
// 1	1		1		- ACLK
// 
// Various options for Pin 1
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 0	1		X		- UCA0RXD/UCA0SOMI
// 1	0		0		- TB2.CCI1A
// 1	0		1		- TB2.1
// 1	1		0		- TB0.CCI0A
// 1	1		1		- TB0.0
// 
// Various options for Pin 2
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 0	1		X		- UCB0CLK
// 1	0		0		- TB2.CCI2A
// 1	0		1		- TB2.2 
// 1	1		0		- TB1.CCI0A
// 1	1		1		- TB1.0 
//
// Various options for Pin 3
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 0	1		X		- UCA1STE
// 1	0		0		- TA0.CCI0B
// 1	0		1		- TA0.0
// 1	1		X		- Analog input A6 - ADC, Comparator_D input CD10
//
// Various options for Pin 4
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 0	1		X		- UCA1CLK
// 1	0		0		- TA1.CCI0B
// 1	0		1		- TA1.0
// 1	1		X		- Analog input A7 - ADC, Comparator_D input CD11
//
// Various options for Pin 5
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 0	1		X		- UCA1TXD/UCA1SIMO
// 1	0		0		- TB0.CCI0B
// 1	0		1		- TB0.0
//
// Various options for Pin 6
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 0	1		X		- UCA1TXD/UCA1SIMO
// 1	0		0		- TB0.CCI0B
// 1	0		1		- TB0.0
//
// Various options for Pin 7
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0 
//-----------------------------------------------------------------------------
void Init_Port2(void) { 

    P2SEL0 = SET_0; // P2 set as I/0
    P2SEL1 = SET_0; // P2 set as I/0
    P2DIR = SET_0;  // P2 set as input
    P2OUT = SET_0;  // P2 initialized as low
  
    P2SEL0 &= ~(USB_TXD | USB_RXD | SPI_SCK | CPU_TXD | CPU_RXD); // Set specified pins as function
    P2SEL1 |= (USB_TXD | USB_RXD | SPI_SCK | CPU_TXD | CPU_RXD); // Set specified pins as function
    P2OUT |= SPI_SCK; // SPI_SCK Port Pin set high
    P2REN |= SPI_SCK; // Enable pullup resistor
}
//------------------------------------------------------------------------------

//=========================================================================== 
// Init_Port3
// Purpose: Initialize Port 3
//
// Various options for Pin 0
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	1		X		- Analog input A12 - ADC, Comparator_D input CD12
// 
// Various options for Pin 1
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	1		X		- Analog input A13 - ADC, Comparator_D input CD13
// 
// Various options for Pin 2
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	1		X		- Analog input A14 - ADC, Comparator_D input CD14
// 
// Various options for Pin 3
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	1		X		- Analog input A15 - ADC, Comparator_D input CD15
// 
// Various options for Pin 4
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	0		0		- TB1.CCI1B
// 1	0		1		- TB1.1
// 1	1		0		- TB2CLK
// 1	1		1		- SMCLK
//
// Various options for Pin 5
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	0		0		- TB1.CCI2B
// 1	0		1		- TB1.2
// 1	1		1		- CDOUT
//
// Various options for Pin 6
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	0		0		- TB2.CCI2B
// 1	0		1		- TB2.1
// 1	1		0		- TB1CLK
//
// Various options for Pin 7
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	0		0		- TB2.CCI2B
// 1	0		1		- TB2.2
//
// Passed: clock_state is passed for future purposes
// Locals: No local variables
// Returned: No values returned
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0 
//-----------------------------------------------------------------------------
void Init_Port3(char clock_state) { //This function will initialize all pins in port 3.

    P3SEL0 = SET_0; // P3 set as I/0
    P3SEL1 = SET_0; // P3 set as I/0
    P3DIR = SET_0;  // P3 set as input
    P3OUT = SET_0;  // P3 initialized as low
  
    P3DIR |= (R_FORWARD | L_FORWARD | TEST_PROBE | R_REVERSE | L_REVERSE); // Set specified pins as outputs
    P3DIR &= ~(X | Y | Z ); // Set specified pins as inputs
    P3SEL0 &= ~(X | Y | Z | R_FORWARD | L_FORWARD | TEST_PROBE | R_REVERSE | L_REVERSE); // Set specified pins as GP I/O
    P3SEL1 &= ~(X | Y | Z | R_FORWARD | L_FORWARD | TEST_PROBE | R_REVERSE | L_REVERSE); // Set specified pins as GP I/O
    P3OUT &= ~(X | Y | Z | R_FORWARD | L_FORWARD | TEST_PROBE | R_REVERSE | L_REVERSE); // Set specified pins to low
    
    
}
//------------------------------------------------------------------------------



//=========================================================================== 
// Init_Port4
// Purpose: Initialize Port 4
//
// Various options for Pin 0
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	0		0		- TB2.CCI0B
// 1	0		1		- TB2.0
// 
// Various options for Pin 1
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
//
//
// Passed: No local variables
// Locals: No local variables
// Returned: No values returned
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0 
//-----------------------------------------------------------------------------
void Init_Port4(void){
   P4SEL0 = SET_0; // P4 set as I/0
   P4SEL1 = SET_0; // P4 set as I/0
   P4DIR = SET_0; // Set P4 direction to input
   P4DIR &= ~(SW1 | SW2); // Direction = input
   P4OUT = SET_0; // Set specified pins to high
   P4OUT |= SW1 | SW2; // Configure pullup resistor
   P4REN |= SW1 | SW2; // Enable pullup resistor
   P4IE |= SW1 | SW2; // P4.0 Hi/Lo edge interrupt
}
//----------------------------------------------------------------

//=========================================================================== 
// Init_PortJ
// Purpose: Initialize Port J
//
// Various options for Pin 0
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	0		0		- TB0OUTH
// 1	0		1		- SMCLK
// 1	1		X		- CD6
// X	X		X		- TDO
// 
// Various options for Pin 1
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	0		0		- TB1OUTH
// 1	0		1		- MCLK
// 1	1		X		- CD7
// X	X		X		- TDI/TCLK
//
// Various options for Pin 2
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	0		0		- TB2OUTH
// 1	0		1		- ACLK
// 1	1		X		- CD8
// X	X		X		- TMS
//
// Various options for Pin 3
// SEL0 SEL1 	DIR
// 0  	0		I:0		- *General-purpose digital I/O
// 1	1		X		- CD9
// X	X		X		- TCK
//
// Various options for Pin 4
// SEL1.5	SEL0.5 SEL1.4	SEL0.4	XT1	DIR
// X		X		0		0		X	I:0		- *General-purpose digital I/O
// X		X		0		1		0	X		- XIN crystal mode
// X		X		0		1		1	X		- XIN bypass mode
//
// Various options for Pin 5
// SEL1.5	SEL0.5 SEL1.4	SEL0.4	XT1	DIR
// X		X		0		0		X	I:0		- *General-purpose digital I/O
// X		X		0		1		0	X		- XOUT crystal mode
// X		X		0		1		1	I:0		- General-purpose digital I/O
//
// Passed: No local variables
// Locals: No local variables
// Returned: No values returned
//
// Author: Mattia Muller
// Date: Sept 2013
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0 
//-----------------------------------------------------------------------------
void Init_PortJ(void) { //This function will initialize all pins in port J

    PJSEL0 = SET_0; // PJ set as I/0
    PJSEL1 = SET_0; // PJ set as I/0
    PJDIR = SET_0;  // PJ set as input
    PJOUT = SET_0;  // PJ initialized as low
  
    PJDIR |= (GPS_PWR | GPS_RESET | GPS_PWRCNTL); // Set specified pins as output
    PJDIR &= ~(GPS_PWRCHK); // Set specified pins as input
    PJSEL0 &= ~(GPS_PWR | GPS_RESET | GPS_PWRCNTL | GPS_PWRCHK); // Set specified pins as GP I/O
    PJSEL1 &= ~(GPS_PWR | GPS_RESET | GPS_PWRCNTL | GPS_PWRCHK); // Set specified pins as GP I/O
    PJOUT &= ~(GPS_PWR | GPS_RESET | GPS_PWRCNTL | GPS_PWRCHK); // Set specified pins to 0
}
//----------------------------------------------------------------

