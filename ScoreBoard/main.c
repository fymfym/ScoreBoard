#include <msp430.h> 

/*
 * 7-Segment print firmware to do ScoreBoard
 *
 * Setup
 *      Bit7: Keepalive blink on/off
 *
 * Input:
 *      0: Score up
 *      1: Score down
 *      2: Reset to Zero
 *
 * Software version:
 *      0.2
 *
 * Hardware platform:
 *      Thita Elektronik - A42264P - version 2
 *
 * Author
 *      fym@bitmax.dk
 */

#include "Init.h"
#include "RS485.h"
#include "global.h"
#include "handledatabuffer.h"
#include "blinker.h"
#include "timer.h"
#include "blinker.h"
#include "handledatabuffer.h"

unsigned int Sek_Flag;             // settes 1 gang / sek
int Sek_count;                     // Tids tæller i timer int
unsigned int Tik;                  // sættes 5 gange / sek
unsigned int temp;                 //

unsigned int ms100_Flag;           // Millisekundt flag -
int msCount;                       // Millisekundt tæller
int displayNumber;

int buffer[20];
unsigned int bufferIndex;

void main(void)
{
    bufferIndex = 0;

    WDTCTL = WDTPW | WDTHOLD;      // Stop watchdog timer
    Init();                        // Init alle register in cpu

    displayNumber = 0;
    P1OUT = 6;

    PwmSegmentValue = 65500;
    TA0CCR0 = PwmSegmentValue;

    Sek_count = 10;

    P4OUT = BIT2;
    P10OUT = BIT4;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    P4OUT = BIT3;
    P10OUT = BIT3;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    P4OUT = BIT4;
    P10OUT = BIT2;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    P4OUT = BIT5;
    P10OUT = BIT1;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    P4OUT = BIT0;
    P10OUT = BIT0;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    P4OUT = BIT1;
    P10OUT = BIT5;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    P4OUT = BIT6;
    P10OUT = BIT6;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    P4OUT = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
    P10OUT = 0;

    // Zero PWM
    Sek_Flag = 0;

    // initialize
    BlinkInit(2500,2,140,140,40,200);

    Rx_Start_RS485();                 // start serial com

    ms100_Flag = 0;

    // Main loop
    for (;;)
    {
        SettingSwitch = P6IN;

        // Every 100 ms the blink execute is run
        if (ms100_Flag == 1)
        {
            int res = BlinkExecuteTimerTick();
            if (res == 1)
            {
                P3OUT |= BIT1;                    // tænd keepalive led
            }
            else
            {
                P3OUT &= ~(BIT1);                 // sluk keepalive led
            }
            ms100_Flag = 0;
        }

        if (Button1Pressed == 1)
        {
            Button1Pressed = 2;
            if (displayNumber < 99) displayNumber++;
            SetLedValue(displayNumber);
        }

        if (Button2Pressed == 1)
        {
            Button2Pressed = 2;
            if (displayNumber > 0) displayNumber--;
            SetLedValue(displayNumber);
        }

        if (Button3Pressed == 1)
        {
            Button3Pressed = 2;
            displayNumber = 0;
            SetLedValue(displayNumber);
        }


        // Test for data blink when "test" button held down
        if ((P3IN & BIT2) != BIT2)
        {
            BlinkData();
            displayNumber = 0;
            P4OUT = 0;
            P10OUT = 0;
        }

        // If "silent" setting is selected - turn off blink led
        if ((SettingSwitch & SETTINGSILENT) == 0)
        {
             P3OUT &= ~(BIT1);                 // sluk keepalive led
        }

        // RS485 data packages
        if (commandReady > 0)
        {
            BlinkData();
            HandleDataBuffer(command);
            commandReady = 0;
        }

        TA0CCR0 = PwmSegmentValue;

    } // for(;;)
} // Main

