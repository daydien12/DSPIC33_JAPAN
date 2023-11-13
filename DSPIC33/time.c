/***********************************************************************************************************************
  File Name    : time.c
  Device(s)    : DSPIC33FJ64GP802
  Description  :
  Creation Date: 2021-9-9
  Programmer    : Nguyen
***********************************************************************************************************************/

/*********************************************************************************************************************************
*****  INCLUDES
*********************************************************************************************************************************/
#include "time.h"

/********************************************************************************************************************************
*****  DEFINES                                                        *****
********************************************************************************************************************************/

/********************************************************************************************************************************
*****  VARIABLES                                                      *****
*******************************************************************************************************************************/
volatile unsigned long us_counter = 0;
/********************************************************************************************************************************
*****  FUNCTIONS PROTOTYPE                                                  *****
********************************************************************************************************************************/
void T1_interrupt_setup()
{
  // Configure Timer 1
  T1CONbits.TON = 0;      // Disable Timer 1
  T1CONbits.TCS = 0;      // Select internal clock (FOSC/2)
  T1CONbits.TGATE = 0;    // Disable gated time accumulation
  T1CONbits.TCKPS = 0;    // Set the prescaler to 1:256
  PR1 = 40 * 10;          // Set the period register for a 1 Hz interrupt frequency

  // Configure Timer 1 interrupt
  _T1IP = 1;              // Set Timer 1 interrupt priority
  _T1IF = 0;              // Clear Timer 1 interrupt flag
  _T1IE = 1;              // Enable Timer 1 interrupt

  // Enable Timer 1 and start the application
  T1CONbits.TON = 1;      // Enable Timer 1
}

void wait_ms(int ms)
{
  us_counter = ms * 100;
  while (us_counter);
}

void wait_us(int us)
{
  us_counter = us;
  while (us_counter);
}

// Timer 1 interrupt service routine (ISR)
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
  // Your code to be executed on Timer 1 interrupt
  if (us_counter > 0)
  {
    us_counter--;
  }
  _T1IF = 0;
}
