/*
 * RS485.h
 *
 */

#ifndef RS485_H_
#define RS485_H_

extern char RS485_TX_Buffer[120];       // RS485 tx buffer radio status
extern char RS485_RX_Buffer[120];       // RS485 tx buffer radio status
extern int RS485_Rx_Chek;               // RS485 chek sum Rx
extern char RS485_Tx_Chek;              // RS485 chek sum Rx
//extern char RS485_Rx_Flag;              // Flag at der er nye data i Rx buffer
extern char RS485RX_BUFFER;                // Character recevied from RS485
void Tx_Start_RS485 (void);
void Tx_Pakke_RS485 (void);
void Rx_Start_RS485 (void);
#endif /* RS485_H_ */
