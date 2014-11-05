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

const char string[] = "NCSU #1         ";

volatile unsigned int cpu_rx_ring_wr, cpu_rx_ring_rd, cpu_tx_ring_wr, cpu_tx_ring_rd;
volatile char CPU_Char_Rx[SMALL_RING_SIZE];
volatile char CPU_Char_Tx[LARGE_RING_SIZE];


char to_display[16];

volatile unsigned int i;

//---------------------------------------------------------------------------- 
void Init_Serial_UCA1(void){
  
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


void reset_buffers(void){

  for(i=SET_0; i<SMALL_RING_SIZE; i++){
    CPU_Char_Rx[i] = SET_0;       // CPU Character
    }
    cpu_rx_ring_wr = SET_0;
    cpu_rx_ring_rd = SET_0;

  for(i=SET_0; i<LARGE_RING_SIZE; i++){ 
      CPU_Char_Tx[i] = string[i];     // CPU Character
    }
    cpu_tx_ring_wr = SET_0;
    cpu_tx_ring_rd = SET_0;
    
   for (i=SET_0; i<LARGE_RING_SIZE; i++)
     to_display[i] = SPACE;
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
      //UCA1IE &= ~UCRXIE; // Disable USCI_A1 RX interrupt
      PJOUT |= LED3; 
      
      CPU_Char_Rx[cpu_rx_ring_wr] = UCA1RXBUF;
      cpu_rx_ring_wr++;
      
      compare_receive_ring_buffer();
      
      UCA1IE |= UCTXIE; // Enable USCI_A1 RX interrupt
      PJOUT &= ~LED3;
      break;
    case 4: // Vector 4 – TXIFG 
     
      PJOUT |= LED2;
      UCA1IE &= ~UCTXIE; // Disable USCI_A1 TX interrupt
      
      if (cpu_tx_ring_wr < LARGE_RING_SIZE){ // TX over? 
          UCA1TXBUF = CPU_Char_Tx[cpu_tx_ring_wr++]; // TX next character 
      }
      
      //UCA1IE |= UCRXIE; // Enable USCI_A1 RX interrupt
      PJOUT &= ~LED2;
      break;
    default: break;
  } 
}
//------------------------------------------------------------------------------



void compare_receive_ring_buffer(void){
  if(cpu_rx_ring_wr > cpu_rx_ring_rd) {
    to_display[cpu_rx_ring_rd] = CPU_Char_Rx[cpu_rx_ring_rd];
    cpu_rx_ring_rd++;
    lcd_out(to_display, LCD_LINE_2);
  }
}
