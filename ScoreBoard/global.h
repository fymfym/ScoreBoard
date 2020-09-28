#ifndef FILE_GLOBAL_SEEN
#define FILE_GLOBAL_SEEN


extern unsigned char DataBuffer[20];
extern unsigned char DataBufferIndex;
extern unsigned char DataBufferData;

extern unsigned char SettingSwitch;

extern unsigned int PwmSegmentValue;

extern unsigned int Segment1Value;
extern unsigned int Segment2Value;


extern int BlinkCount;
extern unsigned char BlinkState;
extern unsigned int BlinkKeepAliveOnInterval;
extern unsigned int BlinkKeepAliveOffInterval;
extern unsigned int BlinkDataOnInterval;
extern unsigned int BlinkDataOffInterval;
extern unsigned int BlinkErrorOnInterval;
extern unsigned int BlinkErrorOffInterval;

extern const unsigned char SETTINGSILENT;

extern unsigned char InputSignal1;
extern unsigned char InputSignal2;
extern unsigned char DigitalLedState;

extern const int DIGITALINPUTREPEATCONSTANT;

#endif /* #endif FILE_FOO_SEEN */
