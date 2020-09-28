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
        return 255 - (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5);
    case 1:
        return 255 - (BIT1 + BIT2);
    case 2:
        return 255 - (BIT0 + BIT1+ BIT3 + BIT4 + BIT6);
    case 3:
        return 255 - (BIT0 + BIT1 + BIT2 + BIT3 + BIT6);
    case 4:
        return 255 - (BIT1 + BIT2 + BIT5 + BIT6);
    case 5:
        return 255 - (BIT0 + BIT2 + BIT3 + BIT5 + BIT6);
    case 6:
        return 255 - (BIT0 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6);
    case 7:
        return 255 - (BIT0 + BIT1 + BIT2);
    case 8:
        return 255 - (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6);
    case 9:
        return 255 - (BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT6);
    }
    return 255;
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
        return 255;
    }
    return 0;
}

int HandleDataBuffer()
{
    int tal1;
    int tal2;
	if (DataBuffer[0] != 3) // Pakkelængde på 3 accepteres
	{
		DataBufferIndex = 0;
		return 0;
	}

	if ((DataBuffer[3] >= 0x10) && (DataBuffer[3] <= 0x73) )
	{
	    tal2 = (DataBuffer[3] - 0x10) / 10;
	    tal1 = (DataBuffer[3] - 0x10) % 10;
        Segment1Value = TranslateToSegmentNumber(tal1);
        if(tal2 > 0)
        {
            Segment2Value = TranslateToSegmentNumber(tal2);
        }
        else
            Segment2Value = 255;
	}

    //if ((DataBuffer[1] >= 0x70) && (DataBuffer[1] <= 0x7F) )
    //    Segment2Value = TranslateToSegmentNumber(DataBuffer[1] - 0x70);


    if ((DataBuffer[3] >= 0x80) && (DataBuffer[3] <= 0x8F) )
        Segment1Value = TurnOnSegment(DataBuffer[3] - 0x80, Segment1Value);

    if ((DataBuffer[3] >= 0x90) && (DataBuffer[3] <= 0x9F) )
        Segment1Value = TurnOffSegment(DataBuffer[3] - 0x90, Segment1Value);

    if ((DataBuffer[3] >= 0xA0) && (DataBuffer[3] <= 0xAF) )
        Segment2Value = TurnOnSegment(DataBuffer[3] - 0xA0, Segment2Value);

    if ((DataBuffer[3] >= 0xB0) && (DataBuffer[3] <= 0xBF) )
        Segment2Value = TurnOffSegment(DataBuffer[3] - 0xB0, Segment2Value);

    if ((DataBuffer[3] == 0x74) )
    {
        Segment1Value = TranslateToSegmentNumber(0);
        Segment2Value = TranslateToSegmentNumber(0);
    }

    if ((DataBuffer[3] == 0x75) )
    {
        Segment1Value = 255;
        Segment2Value = 255;
    }


    // Value for intensity: 10-246 (Omformet til 0-235) - 277
    PwmSegmentValue = 65530 - ((DataBuffer[2]-10)*277);

	return 0;
}
