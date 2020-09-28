/*
 * Init.h
 *
 *  Created on: 8. mar. 2017
 *      Author: a
 */

#ifndef INIT_H_
#define INIT_H_

extern char RS485_TX_Buffer[120];       // RS485 tx buffer radio status
extern char RS485_RX_Buffer[120];       // RS485 tx buffer radio status
extern int RS485_Rx_Chek;               // RS485 chek sum Rx
extern char RS485_Tx_Chek;              // RS485 chek sum Rx
extern char RS485_Rx_Flag;              // Flag at der er nye data i Rx buffer
extern unsigned int LED_Nr;             // nr. på led linje
extern int LED_Intensity;               // lys intensitet tal mellem 0 og 8
extern int Display_Flag;

extern unsigned int Sek_Flag;                    // settes 1 gang / sek
extern int Sek_count;                   // Tids tæller i timer int

extern unsigned int ms100_Flag;
extern int msCount;                   // Tids tæller i timer int

extern unsigned int Tik;

void Init(void);

#endif /* INIT_H_ */
