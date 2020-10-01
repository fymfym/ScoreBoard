/*
 * Timer.c
 *
 */

#include "Timer.h"
#include <msp430.h>
#include "global.h"

int msCount;

static const unsigned int MaxButtonCount = 200;
static const unsigned int ButtonPressed = 25;

/*
    The TIMER0_A0_VECTOR is exclusively used for the CCR0 capture/compare event.
    Since CCR0 has the capability to reset the timer in up or up/down mode and
    therefore define the timer cycle, it has been given an own, higher priority
    interrupt.

    Also, the CCIFG bit in CCTL0 is automatically reset when entering this ISR,
    as there is only one possible reason for this interrupt.

    On A1_VECTOR, you'll have to check what was causing the interrupt and manually
    clear the IFG bits (or clear them by reading the TAIV register)
 */

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
{
    // Turn LED ON on set value
    //P1OUT = 6;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR (void)
{
    switch(__even_in_range(TA0IV,14))
    {
        case 2:
            break;

        case 14:
            // Turn LEDS off
            //P1OUT = 0;
            break;
    }
    //TAIFG = 0;
}



// Timer1 A1 interrupt service routine
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR (void)
{
	  switch(__even_in_range(TA1IV,14))
	  {
          case 14:                                  // 0Eh = Interrupt Source: Timer overflow; Interrupt Flag: TA1IFG

              Tik = 1;                                          // TA1CCR0
              Sek_count --;                                     // tæl tid ned
              if (Sek_count <= 0)                               // se om den er blivet 0
              {
                  Sek_count = 45;                                // vent 0,5 sek. igen
                  Sek_Flag = 1;                                 // flag at der er gået et sek
              }

              msCount--;
              if (msCount <= 0)
              {
                  ms100_Flag = 1;
                  msCount = 2;
              }

              // Button 1
              if ( (P8IN & BIT0)==BIT0)
              {
                  if (InputSignal1 < MaxButtonCount)
                  {
                      InputSignal1++;
                      if (InputSignal1 > ButtonPressed && Button1Pressed == 0)
                      {
                          Button1Pressed = 1;
                      }
                  }
              }
              else
              {
                  if (InputSignal1 > 0) InputSignal1--;
                  if (InputSignal1 == 0) Button1Pressed = 0;
              }

              // Button 2
              if ( (P8IN & BIT1)==BIT1)
              {
                  if (InputSignal2 < MaxButtonCount)
                  {
                      InputSignal2++;
                      if (InputSignal2 > ButtonPressed && Button2Pressed == 0)
                      {
                          Button2Pressed = 1;
                      }
                  }
              }
              else
              {
                  if (InputSignal2 > 0) InputSignal2--;
                  if (InputSignal2 == 0) Button2Pressed = 0;
              }

              // Button 3
              if ( (P8IN & BIT2)==BIT2)
              {
                  if (InputSignal3 < MaxButtonCount)
                  {
                      InputSignal3++;
                      if (InputSignal3 > ButtonPressed && Button3Pressed == 0)
                      {
                          Button3Pressed = 1;
                      }
                  }
              }
              else
              {
                  if (InputSignal3 > 0) InputSignal3--;
                  if (InputSignal3 == 0) Button3Pressed = 0;
              }


              break;
          default: break;							//
	  }
}


