/***********************************************************************************************************************
  File Name    : Main.c
  Device(s)    : DSPIC33FJ128GP804
  Description  : Main Program
  Creation Date: 2021-9-15
  Programmer    : Nguyen
***********************************************************************************************************************/

/********************************************************************************************************************************
*****  DEFINES                                                        *****
********************************************************************************************************************************/
#define __main__

/*********************************************************************************************************************************
*****  INCLUDES
*********************************************************************************************************************************/
#include "uart.h"
#include "xc.h"
#include "common.h"
#include "time.h"
#include "state_machineA.h"
#include "string.h"
#include "stdio.h"
#include <libpic30.h>

/********************************************************************************************************************************
*****  FUNCTIONS PROTOTYPE                                                  *****
********************************************************************************************************************************/

/********************************************************************************************************************************
*****  PRIVATE DEFINES
********************************************************************************************************************************/

/********************************************************************************************************************************
*****  PRIVATE FUNCTIONS PROTOTYPE
********************************************************************************************************************************/

/********************************************************************************************************************************
*****  GLOBAL VARIABLES
   define in main and declare in time, state_machineA
********************************************************************************************************************************/
//volatile unsigned char T3_Interrupt_Flag = 0;
//volatile unsigned char CE_data;

/********************************************************************************************************************************
*****  PRIVATE VARIABLES
********************************************************************************************************************************/

/********************************************************************************************************************************
*****  PLL setup
   System clock(80MHz) with external crystal(10MHz)
********************************************************************************************************************************/
#pragma config FNOSC = FRC
#pragma config IESO = OFF
#pragma config FCKSM = CSECMD
#pragma config OSCIOFNC = OFF
#pragma config POSCMD = XT
#pragma config FPWRT = PWR128
#pragma config JTAGEN = OFF
/********************************************************************************************************************************
*****  Watchdog timer setup
   LPRC 32.768kHz
   WDT Time-out Period = WDTPOST*WDTPRE/LPRC = 0.25s
********************************************************************************************************************************/
//#pragma config FWDTEN = OFF //watch dog timer off
//40000000
#pragma config FWDTEN = ON
#pragma config WDTPOST = PS128 // Watchdog Timer Postscaler Bits (1:256)
#pragma config WDTPRE = PR32 // Watchdog Timer Prescaler bit (1:32)
//#pragma config WDTPRE = PR256 // Watchdog Timer Prescaler bit (1:32)

void send_data(uint8_t data);
void send_cmd0(void);
void send_cmd1(void);
void send_cmd2(uint8_t twdm, uint8_t tewait);
void send_cmd3(uint8_t tpw, uint8_t start_bit, uint8_t dum);
void send_cmd4(uint8_t read_write, uint8_t address);
void send_cmd5(uint8_t tester_data);
void send_cmd6(void);

int main(void)
{
  system_clock_selection();
  io_config();
  io_config_send_to_tester();
  UartInit(9600);
  T1_interrupt_setup();

  printf("Hello, UART!\r\n");
  while (1)
  {
    Tester_LAT = 1;
    wait_us(1);
    Tester_LAT = 0;
    wait_us(1);
    ClrWdt();
    //reset watchdog timer
  }
  return 0;
}

void send_data(uint8_t data)
{
  uint8_t data_bit[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (uint8_t i = 0; i < 8; i++)
  {
    data_bit[i] = ((data >> i) & 0x01);
  }

  Tester_LAT = 0;
  Tester_D0_output = data_bit[0];
  Tester_D1_output = data_bit[1];
  Tester_D2_output = data_bit[2];
  Tester_D3_output = data_bit[3];
  Tester_D4_output = data_bit[4];
  Tester_D5_output = data_bit[5];
  Tester_D6_output = data_bit[6];
  Tester_D7_output = data_bit[7];
  wait_us(1); // 10ns
  Tester_LAT = 1;
  wait_us(10);//100ns
}

void send_cmd0(void)
{
  send_data(0);
  send_data(0);
  send_data(0);
}

void send_cmd1(void)
{
  uint8_t  code_entry[8] = {0, 1, 0, 1, 0, 1, 1, 0, 1};
  uint8_t data0 = 0, data1 = 0;
  for (uint8_t i = 0; i < 8; i++)
  {
    data0 += code_entry[i] << i;
  }
  data1 = code_entry[8];
  send_data(1);
  send_data(data0);
  send_data(data1);

}

void send_cmd2(uint8_t twdm, uint8_t tewait)
{
  uint8_t data0 = twdm, data1 = tewait;
  send_data(2);
  send_data(data0);
  send_data(data1);
}

void send_cmd3(uint8_t tpw, uint8_t start_bit, uint8_t dum)
{
  uint8_t data0 = tpw, data1 = 0;
  data1 |= (start_bit & 0x01);
  data1 |= ((start_bit >> 1) & 0x01) << 1;
  data1 |= ((start_bit >> 2) & 0x01) << 2;
  data1 |= ((dum) & 0x01) << 3;
  send_data(3);
  send_data(data0);
  send_data(data1);
}

void send_cmd4(uint8_t read_write, uint8_t address)
{
  uint8_t data0, data1 = 0;
  data0 |= (read_write & 0x01);
  data0 |= ((address >> 0) & 0x01) << 1;
  data0 |= ((address >> 1) & 0x01) << 2;
  data0 |= ((address >> 2) & 0x01) << 3;
  data0 |= ((address >> 3) & 0x01) << 4;
  data0 |= ((address >> 4) & 0x01) << 5;
  send_data(4);
  send_data(data0);
  send_data(data1);
}

void send_cmd5(uint8_t tester_data)
{
  char str[5];
  uint8_t data0 = tester_data, data1 = 0;

  send_data(5);
  send_data(data0);
  send_data(data1);
}

void send_cmd6(void)
{
  send_data(0);
  send_data(0);
  send_data(0);
}

