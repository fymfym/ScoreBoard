#include "global.h"
#include <msp430.h>


int TranslateIntensity(int Value)
{
    switch (Value)
    {
    case 0:
        return (3000 / 100) * 5;
    case 1:
        return (3000 / 100) * 10;
    case 2:
        return (3000 / 100) * 15;
    case 3:
        return (3000 / 100) * 20;
    case 4:
        return (3000 / 100) * 30;
    case 5:
        return (3000 / 100) * 40;
    case 6:
        return (3000 / 100) * 50;
    case 8:
        return (3000 / 100) * 60;
    case 9:
        return (3000 / 100) * 70;
    case 10:
        return (3000 / 100) * 80;
    case 11:
        return (3000 / 100) * 90;
    case 12:
        return (3000 / 100) * 99;
    }
    return 0;
}

int TranslateToSegmentNumber(int Value)
{
    switch (Value)
    {
    case 0:
        return (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5);
    case 1:
        return (BIT1 + BIT2);
    case 2:
        return (BIT0 + BIT1+ BIT3 + BIT4 + BIT6);
    case 3:
        return (BIT0 + BIT1 + BIT2 + BIT3 + BIT6);
    case 4:
        return (BIT1 + BIT2 + BIT5 + BIT6);
    case 5:
        return (BIT0 + BIT2 + BIT3 + BIT5 + BIT6);
    case 6:
        return (BIT0 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6);
    case 7:
        return (BIT0 + BIT1 + BIT2);
    case 8:
        return (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6);
    case 9:
        return (BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT6);
    }
    return 0;
}

int TurnOnSegment(int Value, int Segment)
{
    switch (Value)
    {
    case 0:
        return Segment & ~BIT0;
    case 1:
        return Segment & ~BIT1;
    case 2:
        return Segment & ~BIT2;
    case 3:
        return Segment & ~BIT3;
    case 4:
        return Segment & ~BIT4;
    case 5:
        return Segment & ~BIT5;
    case 6:
        return Segment & ~BIT6;
    case 7:
        return Segment & ~BIT7;
    case 8:
        return Segment & ~BIT8;
    case 9:
        return Segment & ~BIT9;
    case 15:
        return 0;
    }
    return 0;
}

int TurnOffSegment(int Value, int Segment)
{
    switch (Value)
    {
    case 0:
        return Segment | BIT0;
    case 1:
        return Segment | BIT1;
    case 2:
        return Segment | BIT2;
    case 3:
        return Segment | BIT3;
    case 4:
        return Segment | BIT4;
    case 5:
        return Segment | BIT5;
    case 6:
        return Segment | BIT6;
    case 7:
        return Segment | BIT7;
    case 8:
        return Segment | BIT8;
    case 9:
        return Segment | BIT9;
    case 15:
        return 0;
    }
    return 0;
}

int SetLedValue(int value)
{
    P4OUT = 0;
    P10OUT = 0;

    if (value == 200)
    {
        return 1;
    }

    int tal1;
    int tal2;

    tal2 = value / 10;
    tal1 = value % 10;

    P4OUT = TranslateToSegmentNumber(tal1);
    if (value > 99)
    {
        P10OUT = TranslateToSegmentNumber(0);
    }
    else
    {
        if(tal2 > 0)
        {
            P10OUT = TranslateToSegmentNumber(tal2);
        }
    }
    return 1;
}

int HandleDataBuffer(struct commandStruct command)
{
    switch(command.commandByte)
    {
        case 01:
        {
            SetLedValue(command.dataByte);
            break;
        }

        case 02:
        {
            P4OUT = command.dataByte;
            break;
        }

        case 03:
        {
            P10OUT = command.dataByte;
            break;
        }

    }


    return 0;
}
