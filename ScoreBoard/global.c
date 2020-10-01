
#include "global.h"

unsigned int PwmSegmentValue;

unsigned char SettingSwitch;

unsigned char Button1Pressed;
unsigned char Button2Pressed;
unsigned char Button3Pressed;

unsigned int InputSignal1;
unsigned int InputSignal2;
unsigned int InputSignal3;

int BlinkCount;
unsigned char BlinkState;

unsigned int BlinkKeepAliveOnInterval;
unsigned int BlinkKeepAliveOffInterval;
unsigned int BlinkDataOnInterval;
unsigned int BlinkDataOffInterval;
unsigned int BlinkErrorOnInterval;
unsigned int BlinkErrorOffInterval;

const unsigned char SETTINGSILENT = 128;

const int DIGITALINPUTREPEATCONSTANT = 40;

unsigned char DigitalLedState;

