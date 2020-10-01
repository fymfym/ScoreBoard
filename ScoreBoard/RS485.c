/*
 * RS485.c
 *
 */


#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include "RS485.h"
#include "global.h"

static const int stateWaitingForStartByte = 1;
static const int stateWaitingForAddressByte = 2;
static const int stateWaitingForCommandByte = 3;
static const int stateWaitingForDataByte = 4;

int commandState;

//unsigned int RS485_TX_Pointer;                   // RS485 Tx pointer
//unsigned int RS485_RX_Pointer;                   // RS485 Rx pointer
//const char RS485_Start[2] = "0";        // RS485 Start mærke
//const char RS485_Stop[2] =  "1";         // RS485 Stop mærke

//unsigned char RXBuffer[20];
//unsigned char RXBufferIndex;


void Tx_Pakke_RS485 (void)
{
    UCA2IE &= ~UCTXIE;                                          // Stop tx intrupt lidt
    UCA2IE |= UCTXIE;                                          // Start tx intrupt igen
}

void Tx_Start_RS485 (void)
{
    //P2OUT = P2OUT | BIT5;                    // Enabel RS485 Driver
    //UCA2TXBUF = 0;
    //UCA2TXBUF = RS485_Start[0];                                        // flyt start mærke over i buffer
    //RS485_TX_Pointer = 0;                                              // Tæl op i buffer
}

void Rx_Start_RS485 (void)
{
    //RS485_RX_Pointer = 0;                                              // Tæl op i buffer
    //int i;
    //for(i = 19 ; i > 0 ; i--) RXBuffer[i] = 0;
    RS485RX_BUFFER_DATA_PRESENT = 0;
    commandState = stateWaitingForStartByte;
    commandReady = 0;
    return 1;

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
      switch (commandState)
      {
          case stateWaitingForAddressByte:
          {
              int sw = (~P6IN & 63);
              if (sw != RS485RX_BUFFER) break;
              commandState = stateWaitingForCommandByte;
              commandReady = 0;
              break;
          }
          case stateWaitingForCommandByte:
          {
              command.commandByte = RS485RX_BUFFER;
              commandState = stateWaitingForDataByte;
              commandReady = 0;
              break;
          }
          case stateWaitingForDataByte:
          {
              command.dataByte = RS485RX_BUFFER;
              commandState = stateWaitingForStartByte;
              commandReady = 1;
              break;
          }
      }

      if (RS485RX_BUFFER == 0xFF)
      {
          command.commandByte = 0;
          command.dataByte = 0;
          commandState = stateWaitingForAddressByte;
          commandReady = 0;
      }

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
