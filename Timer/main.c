#include <msp430.h> 

/*
 * LightTower 7-Segment print firmware to do timer
 * Setup
 *      Bit0: Seconds
 *      Bit1: Minutes
 *      Bit0+1: Hours
 *      Bit7: Keepalive blink on/off
 * Input:
 *      0: Reset
 *      1: Start
 *
 * Software version:
 *      1.0
 *
 * Hardware platform:
 *      Thita Elektronik - A42264P
 *
 * Author
 *      fym@bitmax.dk
 */

#include "Init.h"
#include "RS485.h"
#include "global.h"
#include "handledatabuffer.h"
#include "blinker.h"
#include "rxbuffer.h"
#include "timer.h"
#include "blinker.h"

unsigned int Sek_Flag;             // settes 1 gang / sek
int Sek_count;                     // Tids t�ller i timer int
unsigned int Tik;                  // s�ttes 5 gange / sek
unsigned int temp;                 //

unsigned int ms100_Flag;           // Millisekundt flag -
int msCount;                       // Millisekundt t�ller

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;      // Stop watchdog timer
    Init();                        // Init alle register in cpu

    PwmSegmentValue = 65500;
    TA0CCR0 = PwmSegmentValue;

    Sek_count = 10;

    Segment1Value = 255-BIT2;
    Segment2Value = 255-BIT4;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    Segment1Value = 255-BIT3;
    Segment2Value = 255-BIT3;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    Segment1Value = 255-BIT4;
    Segment2Value = 255-BIT2;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    Segment1Value = 255-BIT5;
    Segment2Value = 255-BIT1;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    Segment1Value = 255-BIT0;
    Segment2Value = 255-BIT0;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    Segment1Value = 255-BIT1;
    Segment2Value = 255-BIT5;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    Segment1Value = 255-BIT6;
    Segment2Value = 255-BIT6;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    Segment1Value = 0;
    Segment2Value = 0;
    Sek_Flag = 0;
    while (Sek_Flag==0);                             //  delay 1 sek
    {}

    Segment1Value = 255;
    Segment2Value = 255;

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
                P3OUT &= ~(BIT1);                 // sluk keepalive led
            }
            else
            {
                P3OUT |= BIT1;                    // t�nd keepalive led
            }
            ms100_Flag = 0;
        }

        // If error occures, blink faster
        if (SettingSwitch == 0xff)
        {
                BlinkError();
        }

        // Test for data blink when button held down
        if ((P3IN & BIT2) != BIT2)
        {
            BlinkData();
        }

        // If "silent" setting is selected - turn off blink led
        if ((SettingSwitch & SETTINGSILENT) == 0)
        {
             P3OUT &= ~(BIT1);                 // sluk keepalive led
        }

        // RS485 data packages
        if (RS485RX_BUFFER > 0)
        {
            BlinkData();
            AddByteToRXBuffer(RS485RX_BUFFER);
            RS485RX_BUFFER = 0;
            if (DataBufferData == 1)
            {
                int sw = (~SettingSwitch & 63);
                int adr = (DataBuffer[1]-16);
                if ( sw == adr )
                {
                    HandleDataBuffer();
                }
                DataBufferData = 0;
            }
        }

        TA0CCR0 = PwmSegmentValue;

    } // for(;;)
} // Main

