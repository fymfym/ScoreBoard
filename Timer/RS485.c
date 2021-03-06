/*
 * RS485.c
 *
 */


#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include "RS485.h"
#include "global.h"

//unsigned int RS485_TX_Pointer;                   // RS485 Tx pointer
//unsigned int RS485_RX_Pointer;                   // RS485 Rx pointer
//const char RS485_Start[2] = "0";        // RS485 Start m�rke
//const char RS485_Stop[2] =  "1";         // RS485 Stop m�rke

void Tx_Pakke_RS485 (void)
{
    UCA2IE &= ~UCTXIE;                                          // Stop tx intrupt lidt
    UCA2IE |= UCTXIE;                                          // Start tx intrupt igen
}

void Tx_Start_RS485 (void)
{
    //P2OUT = P2OUT | BIT5;                    // Enabel RS485 Driver
    //UCA2TXBUF = 0;
    //UCA2TXBUF = RS485_Start[0];                                        // flyt start m�rke over i buffer
    //RS485_TX_Pointer = 0;                                              // T�l op i buffer
}

void Rx_Start_RS485 (void)
{
    //RS485_RX_Pointer = 0;                                              // T�l op i buffer
}

// Read pakke in to buffer
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:break;                                                 // Vector 0 - no interrupt
  case 2:                                                       // Vector 2 - RXIFG
      RS485RX_BUFFER = UCA0RXBUF;                               // hent data ind i buffer
      break;
// write buffer in to Uart
  case 4:                                                                       // Vector 4 - TXIFG
      if (~(UCA0IFG & UCTXIFG))
      {
      }
      break;
  default: break;
  }
}


