#include "global.h"

const unsigned char BlinkStateNone = 0;
const unsigned char BlinkStateBlinkKeepAlive = 2;
const unsigned char BlinkStateBlinkData = 4;
const unsigned char BlinkStateBlinkError = 8;
const unsigned char BlinkStateLedOn = 16;


int GetBlinkCount()
{
	if ((BlinkState & BlinkStateBlinkError) == BlinkStateBlinkError)
	{
		if ((BlinkState & BlinkStateLedOn) == BlinkStateLedOn)
		{
		    BlinkCount = 10;//BlinkErrorOffInterval;
		}
		else
		{
		    BlinkCount = 10;//BlinkErrorOnInterval;
		}
		return 0;
	}

	if ((BlinkState & BlinkStateBlinkData) == BlinkStateBlinkData)
	{
		if ((BlinkState & BlinkStateLedOn) == BlinkStateLedOn)
		{
		    BlinkCount = 2;//BlinkDataOffInterval;
		}
		else
		{
		    BlinkCount = 2;//BlinkDataOnInterval;
		}
	}
	else
	{
		if ((BlinkState & BlinkStateBlinkKeepAlive) == BlinkStateBlinkKeepAlive)
		{
			if ((BlinkState & BlinkStateLedOn) == BlinkStateLedOn)
			{
			    BlinkCount = 5;//BlinkKeepAliveOffInterval;
			}
			else
			{
			    BlinkCount = 50;//BlinkKeepAliveOnInterval;
			}
		}
	}
	return 0;
}

void BlinkInit(int KeepAliveOnInterval, int KeepAliveOffInterval, int ErrorOnInterval, int ErrorOffInterval, int DataOnInterval, int DataOffInterval)
{
	BlinkState = BlinkStateNone;
	BlinkKeepAliveOnInterval = KeepAliveOnInterval;
	BlinkKeepAliveOffInterval = KeepAliveOffInterval;
	if (BlinkKeepAliveOnInterval > 0)
	{
		BlinkState = BlinkStateBlinkKeepAlive;
		BlinkCount = BlinkKeepAliveOnInterval;
	}
	BlinkDataOnInterval = DataOnInterval;
	BlinkDataOffInterval = DataOffInterval;
	BlinkErrorOnInterval = ErrorOnInterval;
	BlinkErrorOffInterval = ErrorOffInterval;
    GetBlinkCount();
}

unsigned char BlinkExecuteTimerTick()
{
	if (BlinkCount <= 1)
	{
		GetBlinkCount();
		if ((BlinkState & BlinkStateLedOn) == BlinkStateLedOn)
		{
			if ((BlinkState & BlinkStateBlinkData) == BlinkStateBlinkData)
				BlinkState ^= BlinkStateBlinkData;

			if ((BlinkState & BlinkStateBlinkError) == BlinkStateBlinkError)
				BlinkState ^= BlinkStateBlinkError;

			BlinkState &= ~BlinkStateLedOn;

		}
		else
			BlinkState |= BlinkStateLedOn;
	}
	else
	{
		BlinkCount--;
	}
	if ((BlinkState & BlinkStateLedOn) == BlinkStateLedOn)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void BlinkData()
{
	if ((BlinkState & BlinkStateBlinkData) == BlinkStateBlinkData)
		return;
	BlinkCount = BlinkDataOnInterval;
	BlinkState |= BlinkStateBlinkData;
}

void BlinkError()
{
	if ((BlinkState & BlinkStateBlinkError) == BlinkStateBlinkError)
		return;
	BlinkCount = BlinkErrorOnInterval;
	BlinkState |= BlinkStateBlinkError;
}

