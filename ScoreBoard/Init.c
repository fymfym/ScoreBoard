/*
 * Init.c
 *
 *
 */

#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include "Init.h"
unsigned int loop ;

void Init(void)                                        // hvis det går godt retuner 1 ellers 0
{

    // ********************************************************************************************************
    //Initialsering GPIO

    WDTCTL = WDTPW | WDTHOLD;                               // Stop watchdog timer

    // PWM
    P1DIR = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0;        // Port 1 output direction output, 0b = Port configured as input, 1b = Port configured as output
    P1REN = 0;                                              // Port 1 Resistor Enable
    P1OUT = 0;                                              // Port 1 Pullup / Pulldown
    //P1DS  = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0;        // Port 1 Output Drive Strength Registers
    //P1SEL = BIT3+BIT2;                                      // Port 1 Function Select Registers - PWM 1 og 2
    P1IES = 0 ;                                             // Port 1 interrupt Edge Select hige to low
    P1IE  = 0 ;                                             // Port 1 interrupt enable
    P1IFG = 0 ;                                             // Port 1 interrupt Flag no int from port 1

    // RS485
    P2DIR = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0;        // Port 2 output direction output, 0b = Port configured as input, 1b = Port configured as output
    P2REN = 0;                                              // Port 2 Resistor Enable
    P2OUT = 0;                                              // Port 2 LED off RS485 driver off
    P2DS  = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0 ;       // Port 2 Output Drive Strength Registers
    P2SEL = 0 ;                                             // Port 2 Function Select Registers BIT 5 Driver Busser
    P2IES = 0 ;                                             // Port 2 lnterrupt Edge Select hige to low
    P2IE =  0 ;                                             // Port 2 interrupt enable
    P2IFG = 0 ;                                             // Port 2 lnterrupt Flag no int from port 2

    // RS485 / Info LED / Switch
    P3DIR = BIT7+BIT6+BIT4+BIT3+BIT1+BIT0;                  // Port 3 output direction output all output,
    P3REN = BIT2;                                           // Port 3 Resistor Enable
    P3OUT = BIT2;                                           // Port 3 CS LCD
    P3DS  = 0 ;                                             // Port 3 Output Drive Strength Registers
    P3SEL = BIT5+BIT4;                                      // Port 3 Function Select Registers BIT 6 NC

    // 7-seg #1
    P4DIR = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0;        // Port 4 output direction output all, 0b = Port configured as input, 1b = Port configured as output
    P4REN = 0;                                              // Port 4 Resistor Enable
    P4OUT = 0 ;                                             // Port 4 Pullup / Pulldown
    P4DS  = 0 ;                                             // Port 4 Output Drive Strength Registers
    P4SEL = 0 ;                                             // Port 4 Function Select Registers

    // External crystal
    P5DIR = BIT7+BIT6+BIT5+BIT4 +BIT0;                      // Port 5 output direction output , 0b = Port configured as input, 1b = Port configured as output
    P5REN = 0 ;                                             // Port 5 Resistor Enable
    P5OUT = 0 ;                                             // Port 5 Pullup / Pulldown
    P5DS  = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0 ;       // Port 5 Output Drive Strength Registers
    P5SEL = BIT3+BIT2+BIT1 ;                                // Port 5 Function Select Registers

    // Config switch
    P6DIR = 0 ;                                             // Port 6 output direction output , 0b = Port configured as input, 1b = Port configured as output
    P6REN = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0  ;      // Port 6 Resistor Enable
    P6OUT = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0 ;       // Port 6 Pullup / Pulldown
    P6DS  = 0 ;                                             // Port 6 Output Drive Strength Registers
    P6SEL = 0 ;                                             // Port 6 Function Select Registers

    // Not used
    P7DIR = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0 ;       // Port 7 output direction output, 0b = Port configured as input, 1b = Port configured as output
    P7REN = 0 ;                                             // Port 7 Resistor Enable
    P7OUT = 0 ;                                             // Port 7 Pullup / Pulldown
    P7DS  = 0 ;                                             // Port 7 Output Drive Strength Registers
    P7SEL = 0 ;                                             // Port 7 Function Select Registers

    // Pin input from plug
    P8DIR = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0 ;       // Port 8 output direction output , 0b = Port configured as input, 1b = Port configured as output
    P8REN = 0 ;                                             // Port 8 Resistor Enable
    P8OUT = 0 ;                                             // Port 8 Pullup / Pulldown
    P8DS  = 0 ;                                             // Port 8 Output Drive Strength Registers
    P8SEL = 0 ;                                             // Port 8 Function Select Registers

    // Light sensor
    P9DIR = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2 ;                 // Port 9 output direction output , 0b = Port configured as input, 1b = Port configured as output
    P9REN = 0 ;                                             // Port 9 Resistor Enable
    P9OUT = 0 ;                                             // Port 9 Pullup / Pulldown
    P9DS  = 0 ;                                             // Port 9 Output Drive Strength Registers
    P9SEL = BIT1+BIT0 ;                                     // Port 9 Function Select Registers

    // 7-seg #2
    P10DIR = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0 ;      // Port 10 direction - 0b = Port configured as input, 1b = Port configured as output
    P10REN = 0;                                             // Port 10 Resistor Enable
    P10OUT = 0;                                             // Port 10 Pullup / Pulldown
    P10DS  = 0;                                             // Port 10 Output Drive Strength Registers
    P10SEL = 0;                                             // Port 10 Function Select Registers

    // Not used
    P11DIR = BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0 ;      // Port 11 output direction output , 0b = Port configured as input, 1b = Port configured as output
    P11REN = 0 ;                                            // Port 11 Resistor Enable
    P11OUT = 0 ;                                            // Port 11 Pullup / Pulldown
    P11DS  = 0 ;                                            // Port 11 Output Drive Strength Registers
    P11SEL = 0 ;                                            // Port 11 Function Select Registers


    // ********************************************************************************************************
    //Initelsering Unified Clock System
    // XT1 off
    // XT2 HF Mode 14,7456MHz
    // MCLK = 14,7456 MHz
    // ACLK = 14,7456MHz

    //
    // 14745600 / 65535 = 225 gange i sekundet

    // Initialize XT2

    UCSCTL6 &= ~(XT2OFF);                     // XT2 On
    UCSCTL6 |= XT1OFF;                        // XT1 Off
    UCSCTL4 = SELA_4 + SELS_4 + SELM_4;       // set Aclk og Mclk til 4MHz og SM clck til 32KHz
    _BIC_SR(OSCOFF);
    // Loop until XT2 fault flag is cleared
    do
    {
       UCSCTL7 &= ~XT2OFFG;                    // Clear XT2 fault flags
    } while (UCSCTL7&XT2OFFG);                 // Test XT2 fault flag
    UCSCTL3 =  SELREF_7;

    // Initialize DCO to 4,096 MHz
    __bis_SR_register(SCG0);                  // Disable the FLL control loop

    // Loop until XT1,XT2 & DCO fault flag is cleared
    do
    {
       UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);  // Clear XT2,XT1,DCO fault flags       SFRIFG1 &= ~OFIFG;                      // Clear fault flags
       SFRIFG1 &= ~OFIFG;                                       // Clear XT2 fault flags
    } while (SFRIFG1&OFIFG);                                    // Test oscillator fault flag

    UCSCTL4 = SELA_5 + SELS_5 + SELM_5;                         // set Aclk og Mclk og SM clck til 14MHz

    // ********************************************************************************************************
    // Timer A 0 -  PWM
    TA0CTL = TASSEL_1 + MC_2 + TACLR + TAIE;    // set Timer A, Source:ACLK,  Continuous mode
    TA0CCTL0 = CCIE;

    TA0CCR0 = 65530;


    // ********************************************************************************************************
    // Timer A 1
    // init timer A1 til at give intrrupt 5 gange per sek.
    //TA1EX0 = 4;                                 // predel de 14 MHz med 5 tæller op med 4.915.200 Hz
    TA1CTL = TASSEL_1 + MC_2 + TACLR +  TAIE;    // set Timer A til Continuous mode en int, og del med 4, skulle give int ved 75 hz.


    // ********************************************************************************************************
    // init UART A0 57600
    UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL_1;                     // SMCLK
    UCA0BR0 = 16;                             // 14,7456MHz/(16*57600) = 16
    UCA0BR1 = 0;                              //
    UCA0MCTL = UCOS16;                        // Modln UCBRSx=0, UCBRFx=0, over sampling
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    //UCA0IE |= UCTXIE + UCRXIE;              // Enable USCI_A0 RX og TX interrupt
    UCA0IE |=  UCRXIE;                        // Enable USCI_A0 RX interrupt

    // Variables setup
    Sek_Flag  = 0;                            // settes 1 gang / sek vendt 1 sek
    Sek_count = 0;                            // Tids tæller
    Tik = 0;                                  // vendt 0,2 sek.
    msCount = 0;
    ms100_Flag = 0;

    __bis_SR_register( GIE);                  // LPM0, ADC10_ISR will force exit

    P4OUT = 255;                              // Sluk alle 7-seg
    P10OUT = 255;                             // Sluk alle 7-seg

}
