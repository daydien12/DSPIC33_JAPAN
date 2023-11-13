/***********************************************************************************************************************
* File Name    : common.c
* Device(s)    : DSPIC33FJ64GP802
* Description  : Common Program
* Creation Date: 2021-9-9
* Programmer    : Nguyen 
***********************************************************************************************************************/

/*********************************************************************************************************************************
*****  INCLUDES																												
*********************************************************************************************************************************/
#include "common.h"
/********************************************************************************************************************************
*****  DEFINES																												*****
********************************************************************************************************************************/

/********************************************************************************************************************************
*****  VARIABLES																											*****
********************************************************************************************************************************/

/********************************************************************************************************************************
*****  FUNCTIONS PROTOTYPE																									*****
********************************************************************************************************************************/
void io_config(void){
    //input pin configure
    TRISBbits.TRISB14 = 0; //Set PortB pin14 as input P_LD 
    TRISAbits.TRISA7 = 1; //Set PortA pin7 as input P_START 
    TRISAbits.TRISA10 = 1; //Set PortA pin10 as input P_RESET
    TRISBbits.TRISB12 = 0; //Set PortB pin12 as input P_LAT0
    TRISBbits.TRISB9 = 1; //Set PortB pin9 as input P_READ
    //output pin configure
    TRISBbits.TRISB13 = 0; //Set PortB pin13 as output CE
    TRISBbits.TRISB15 = 0; //Set PortB pin15 as output Busy
    TRISCbits.TRISC6 = 0; //Set PortC pin6 as output P_DIR
    //Test led
    TRISCbits.TRISC9 = 0; //Set PortC pin9 as output LED
    
    //Uart config
    TRISBbits.TRISB10 = 1; //Set PortB pin10 as input RX
    TRISBbits.TRISB11 = 0; //Set PortB pin11 as input TX

    //AD disable
    AD1PCFGL = 0xffff;
}

void io_config_read_from_tester(void){
    PIC_DIR = 1 ;   //set Octal Bus Transceiver and 3.3-V to 5-V Shifter direction
    TRISAbits.TRISA9 = 1; //Set PortA pin9 as input P_D0
    TRISCbits.TRISC3 = 1; //Set PortC pin3 as input P_D1
    TRISCbits.TRISC4 = 1; //Set PortC pin4 as input P_D2
    TRISCbits.TRISC5 = 1; //Set PortC pin5 as input P_D3
    TRISBbits.TRISB5 = 1; //Set PortB pin5 as input P_D4
    TRISBbits.TRISB6 = 1; //Set PortB pin6 as input P_D5
    TRISBbits.TRISB7 = 1; //Set PortB pin7 as input P_D6
    TRISBbits.TRISB8 = 1; //Set PortB pin8 as input P_D7
}

void io_config_send_to_tester(void){
    PIC_DIR = 0 ;   //set Octal Bus Transceiver and 3.3-V to 5-V Shifter direction
    TRISAbits.TRISA9 = 0; //Set PortA pin9 as output P_D0
    TRISCbits.TRISC3 = 0; //Set PortC pin3 as output P_D1
    TRISCbits.TRISC4 = 0; //Set PortC pin4 as output P_D2
    TRISCbits.TRISC5 = 0; //Set PortC pin5 as output P_D3
    TRISBbits.TRISB5 = 0; //Set PortB pin5 as output P_D4
    TRISBbits.TRISB6 = 0; //Set PortB pin6 as output P_D5
    TRISBbits.TRISB7 = 0; //Set PortB pin7 as output P_D6
    TRISBbits.TRISB8 = 0; //Set PortB pin8 as output P_D7
}


void system_clock_selection(void){
// Configure PLL pre_scaler, PLL post_scaler, PLL divisor
    PLLFBD=30; // M = 32
    CLKDIVbits.PLLPOST=0; // N2 = 2
    CLKDIVbits.PLLPRE=0; // N1 = 2
// Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
// Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);
// Wait for PLL to lock
    while(OSCCONbits.LOCK!=1) {};
}
