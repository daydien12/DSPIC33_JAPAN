/***********************************************************************************************************************
* File Name    : uart.c
* Device(s)    : DSPIC33FJ64GP802
* Description  : PC communication
* Creation Date: 2021-08-03
* Programmer    : Nguyen 
***********************************************************************************************************************/

/*********************************************************************************************************************************
*****  INCLUDES																												
*********************************************************************************************************************************/
#include "uart.h"
#include "string.h"
/********************************************************************************************************************************
*****  DEFINES																												*****
********************************************************************************************************************************/

/********************************************************************************************************************************
*****  VARIABLES																											*****
********************************************************************************************************************************/

/********************************************************************************************************************************
*****  FUNCTIONS PROTOTYPE																									*****
********************************************************************************************************************************/

void UartInit(unsigned int baud)
{
    PPS();//Peripheral Pin Select
    U1BRG = 259; // BAUD Rate Setting
    U1MODE=0x8000; /* Enable, 8data, no parity, 1 stop    */
    U1STA =0x8400; /* Enable TX                           */
    IFS0bits.U1RXIF = 0; 
//    IEC0bits.U1RXIE = 1;
//    IPC2bits.U1RXIP = 1;
    U1STAbits.URXISEL = 0x00;
    
    /*
    U1MODEbits.STSEL = 0; // 1 Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8 data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1MODEbits.BRGH = 0; // Low Speed mode
    U1MODEbits.UEN = 0;
    U1STAbits.ADDEN = 0;
    U1BRG = 259 ; // BAUD Rate Setting for 9600
    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX Character is transmitted
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.URXISEL = 0;
    IEC0bits.U1TXIE = 1; // Enable UART TX Interrupt
    IEC0bits.U1RXIE = 1;
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX
    */
    //wait at least 104 u_sec (1/9600) before sending first char
//    for(i = 0; i < 4160; i++)Nop();
}

void Uart_Write(char send){
    while(U1STAbits.UTXBF== 1);
    U1TXREG = send;
}

void Uart_Write_String(char *str){
    int i = 0;
    while(str[i] != 0x00){
        Uart_Write(str[i]);
        i++;
    }
}

char Uart_Read(){
    char data_r;
    while(IFS0bits.U1RXIF == 0){
    }
    data_r = U1RXREG;
    IFS0bits.U1RXIF = 0;
    return data_r;
}

void Uart_Read_CMD(char *str){
    int i;
    for(i=0;i<2;i++){
        str[i] = Uart_Read();
    }
}


void PPS(){
    RPINR18bits.U1RXR = 10; // rx to RP10
    //RPINR18bits.U1CTSR = 1;// Assign U1CTS To Pin RP1
    RPOR5bits.RP11R = 3;// Assign U1Tx To Pin RP11
    //RPOR1bits.RP3R = 4;// Assign U1RTS To Pin RP3
}