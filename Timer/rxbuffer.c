#include "global.h"

unsigned char RXBuffer[20];
unsigned char RXBufferIndex;

void AddByteToRXBuffer(unsigned char Byte)
{

    unsigned int i = 0;
	if ((Byte >= 1) && (Byte <= 0x0f))
	{
		for (i = sizeof(RXBuffer)-1; i ; i--)
			RXBuffer[i] = 0;
		RXBufferIndex = 1;
		RXBuffer[0] = Byte;
	}
	else
	{
        RXBuffer[RXBufferIndex] = Byte;

        if (RXBufferIndex == RXBuffer[0])
        {
            for (i = sizeof(DataBuffer)-1 ; i ; i--)
                DataBuffer[i-1] = 0;

            for (i = RXBufferIndex+1; i ; i--)
                DataBuffer[i-1] = RXBuffer[i-1];

            DataBufferIndex = 0;

            for (i = sizeof(RXBuffer)-1 ; i ; i--)
                RXBuffer[i-1] = 0x00;

            DataBufferData = 1;
            RXBufferIndex=0;
        }
        else
            RXBufferIndex++;

        if (RXBufferIndex >= sizeof(RXBuffer))
            RXBufferIndex = 0;
	}
}
