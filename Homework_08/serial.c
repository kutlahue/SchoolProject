//------------------------------------------------------------------------------
//  File Name: serial.c
//
//  Description: This file contains the serial communication functions
//
//  Mattia Muller
//  Oct 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

const char string[] = "NCSU #1";

unsigned int usb_rx_ring_wr, usb_rx_ring_rd, usb_tx_ring_wr, usb_tx_ring_rd, i;
char* USB_Char_Rx;
char* USB_Char_Tx;

char reception[16];

//---------------------------------------------------------------------------- 
void Init_Serial_UCA1(void){
volatile int i;

for(i=SET_0; i<SMALL_RING_SIZE; i++){
  USB_Char_Rx[i] = SET_0;       // USB Character
  }
  usb_rx_ring_wr = SET_0;
  usb_rx_ring_rd = SET_0;

for(i=SET_0; i<LARGE_RING_SIZE; i++){ 
    USB_Char_Tx[i] = SET_0;     // USB Character
  }
  usb_tx_ring_wr = SET_0;
  usb_tx_ring_rd = SET_0;
  
// Configure UART 0
UCA1CTLW0 = SET_0; // Use word register 
UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK 
UCA1CTLW0 |= UCSWRST; // Set Software reset enable


// 9,600 Baud Rate
// 1. Calculate N = fBRCLK/Baudrate [if N > 16 continue with step 3, otherwise with step 2] 
// N = SMCLK / 4,800 => 8,000,000 / 4,800 = 1666.6666
// 2. OS16 = 0, UCBRx = INT(N) [continue with step 4]
// 3. OS16 = 1, UCx = INT(N/16), UCFx = INT([(N/16) – INT(N/16)] × 16)
// UCx = INT(N/16) = 1666.66666/16 => 104
// UCFx = INT([(N/16) – INT(N/16)] × 16) = ([1666.66666/16-INT(1666.66666/16)]*16) => (104.0208333-52)*16=>0.0208333*16=0.3333
// 4. UCSx can be found by looking up the fractional part of N ( = N - INT(N) ) in Table 18-4
// Decicmal of SMCLK / 8,000,000 / 9,600 = 1666.66666 => 0.666 yields 0xD6
// 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
// 
//                                        TX error (%) RX error (%) 
// BRCLK   Baudrate UCOS16  UCBRx  UCFx   UCSx   neg    pos   neg    pos 
// 8000000 4800     1       104     0      0xD6   -0.08  0.04  -0.10  0.14
UCA1BRW = 104 ; // 4,800 baud
// UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
// UCA0MCTLW = 0xD6 concatenate 1 concatenate 1;
UCA1MCTLW = 0xD621 ;
UCA1CTL1 &= ~UCSWRST; // Release from reset 
UCA1IE |= UCRXIE; // Enable RX interrupt
//UCA0IE |= UCTXIE;

}



void uart_send_byte( unsigned char data ) {
  
  //data <<= SET_1;
    // Wait until USCI_A0 TX buffer is ready
  while (!(SET_2&UCTXIFG)) ;
    // Send the byte
    UCA1TXBUF = data;
}



//------------------------------------------------------------------------------ 
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
unsigned int temp;
switch(__even_in_range(UCA1IV,0x08)){
    case 0: // Vector 0 - no interrupt
      break;
    case 2: // Vector 2 - RXIFG
      /*
      temp = usb_rx_ring_wr++; 
      USB_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
      if (usb_rx_ring_wr >= (SMALL_RING_SIZE)){
        usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
      }
      */
      PJOUT |= LED3; 
      if (i < (sizeof string - SET_NEG_1)) {
        if (UCA1RXBUF == string[i] ) {
            UCA1TXBUF = string[i++];
            reception[i] = UCA1RXBUF;
            i++;
        }
      }
      
          PJOUT &= ~LED3;
      break;
    case 4: // Vector 4 – TXIFG 
     
      PJOUT |= LED2;
     // UCA1TXBUF = string[i++]; // TX next character 
    
      if (i == sizeof string - 1){ // TX over? 
        //UCA1IE &= ~UCTXIE; // Disable USCI_A0 TX interrupt 
        i=0;
      }
      PJOUT &= ~LED2;
      break;
    default: break;
  } 
}
//------------------------------------------------------------------------------



