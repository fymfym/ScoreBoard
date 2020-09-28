
#include "global.h"

unsigned char RS485RX_BUFFER;


unsigned char DataBuffer[20];
unsigned char DataBufferIndex;
unsigned char DataBufferData = 0;

unsigned int PwmSegmentValue;

unsigned int Segment1Value;
unsigned int Segment2Value;

unsigned char SettingSwitch;

unsigned char InputSignal1;
unsigned char InputSignal2;
int BlinkCount;
unsigned char BlinkState;

unsigned int BlinkKeepAliveOnInterval;
unsigned int BlinkKeepAliveOffInterval;
unsigned int BlinkDataOnInterval;
unsigned int BlinkDataOffInterval;
unsigned int BlinkErrorOnInterval;
unsigned int BlinkErrorOffInterval;

const unsigned char SETTINGSILENT = 128;

const int DIGITALINPUTREPEATCONSTANT = 4;

unsigned char DigitalLedState;

