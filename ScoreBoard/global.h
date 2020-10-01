#ifndef FILE_GLOBAL_SEEN
#define FILE_GLOBAL_SEEN

unsigned char RS485RX_BUFFER;
int RS485RX_BUFFER_DATA_PRESENT;

extern unsigned char SettingSwitch;

extern unsigned int PwmSegmentValue;

extern int BlinkCount;
extern unsigned char BlinkState;
extern unsigned int BlinkKeepAliveOnInterval;
extern unsigned int BlinkKeepAliveOffInterval;
extern unsigned int BlinkDataOnInterval;
extern unsigned int BlinkDataOffInterval;
extern unsigned int BlinkErrorOnInterval;
extern unsigned int BlinkErrorOffInterval;

extern const unsigned char SETTINGSILENT;

extern unsigned char Button1Pressed;
extern unsigned char Button2Pressed;
extern unsigned char Button3Pressed;

extern unsigned int InputSignal1;
extern unsigned int InputSignal2;
extern unsigned int InputSignal3;

extern unsigned char DigitalLedState;

extern const int DIGITALINPUTREPEATCONSTANT;

struct commandStruct
{
    unsigned char commandByte;
    unsigned char dataByte;
};

#endif /* #endif FILE_FOO_SEEN */
