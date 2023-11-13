/***********************************************************************************************************************
* File Name    : common.h
* Device(s)    : DSPIC33FJ64GP802
* Description  : Common Header
* Creation Date: 2021-9-15
* Programmer    : Nguyen 
***********************************************************************************************************************/

/*********************************************************************************************************************************
*****  INCLUDES																												
*********************************************************************************************************************************/
#include "xc.h"
/********************************************************************************************************************************
*****  DEFINES																												*****
********************************************************************************************************************************/
//use external crystal with PLL 
#define FCY 40000000UL          
//input
#define Tester_Reset PORTAbits.RA10
#define Tester_Start PORTAbits.RA7
//#define Tester_LAT PORTBbits.RB12
//#define Tester_LD PORTBbits.RB14
#define Tester_D0_input PORTAbits.RA9
#define Tester_D1_input PORTCbits.RC3
#define Tester_D2_input PORTCbits.RC4
#define Tester_D3_input PORTCbits.RC5
#define Tester_D4_input PORTBbits.RB5
#define Tester_D5_input PORTBbits.RB6
#define Tester_D6_input PORTBbits.RB7
#define Tester_D7_input PORTBbits.RB8
#define Device_read PORTBbits.RB9
//output
#define LED LATCbits.LATC9
#define PIC_Busy LATBbits.LATB15
#define PIC_CE LATBbits.LATB13
#define PIC_DIR LATCbits.LATC6

#define Tester_LAT LATBbits.LATB12
#define Tester_LD LATBbits.LATB14

#define Tester_D0_output LATAbits.LATA9
#define Tester_D1_output LATCbits.LATC3
#define Tester_D2_output LATCbits.LATC4
#define Tester_D3_output LATCbits.LATC5
#define Tester_D4_output LATBbits.LATB5
#define Tester_D5_output LATBbits.LATB6
#define Tester_D6_output LATBbits.LATB7
#define Tester_D7_output LATBbits.LATB8

#ifndef R_DATA
#define R_DATA
typedef struct{
    unsigned char code_entry[9];
    unsigned char TWDM;
    unsigned char TEWAIT;
    unsigned char TPW;
    unsigned char dum;
    
    unsigned char start_bit[6];
    unsigned char addr[10];
    unsigned char rw[2];
    unsigned char txdata[16];
}RECEIVE_DATA;

#endif
/********************************************************************************************************************************
*****  VARIABLES																											*****
********************************************************************************************************************************/

/********************************************************************************************************************************
*****  FUNCTIONS PROTOTYPE																									*****
********************************************************************************************************************************/
void io_config();
void io_config_read_from_tester();
void io_config_send_to_tester();
void system_clock_selection();
