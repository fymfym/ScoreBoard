#ifndef FILE_BLINKER_SEEN
#define FILE_BLINKER_SEEN

void BlinkInit(int KeepAliveOnInterval, int KeepAliveOffInterval, int ErrorOnInterval, int ErrorOffInterval, int DataOnInterval, int DataOffInterval);
void BlinkData();
void BlinkError();

unsigned char BlinkExecuteTimerTick();

#endif /* #endif FILE_BLINKER_SEEN */
