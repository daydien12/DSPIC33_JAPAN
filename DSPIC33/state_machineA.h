/***********************************************************************************************************************
* File Name    : state_machine.h
* Device(s)    : DSPIC33FJ128GP802
* Description  : State Machine Header
* Creation Date: 2021-9-15
* Programmer    : Nguyen 
***********************************************************************************************************************/

/*********************************************************************************************************************************
*****  INCLUDES																												
*********************************************************************************************************************************/
#include "xc.h"
#include "common.h"
#include "time.h"
/********************************************************************************************************************************
*****  DEFINES																												*****
********************************************************************************************************************************/
#define END_SEND_DATA 0xFF
#ifndef X_STATE_MACHINE
#define X_STATE_MACHINE
typedef enum {  STATE_IDLE, 
                STATE_CMD, 
                STATE_DATA0,
                STATE_DATA1, 
                STATE_RETURN_DATA0,
                STATE_DATA_STORE,
                STATE_RETURN_TO_TESTER, 
                STATE_READ_DEVICE_DATA, 
                STATE_SEND_CODE_ENTRY, 
                STATE_SEND_TESTER_DATA, 
                NUM_STATES 
            } state_A;                
#endif
/********************************************************************************************************************************
*****  VARIABLES																											*****
********************************************************************************************************************************/
//extern volatile unsigned char T3_Interrupt_Flag;
//extern volatile unsigned char CE_data;

/********************************************************************************************************************************
*****  FUNCTIONS PROTOTYPE																									*****
********************************************************************************************************************************/
state_A do_state_machineA(state_A TEST0);
state_A do_state_idle();
state_A do_state_cmd();
state_A do_state_data0();
state_A do_state_data1();
state_A do_state_return_data0();
state_A do_state_data_store();
state_A do_state_return_to_tester();
state_A do_state_read_device_data();
state_A do_state_send_code_entry();
state_A do_state_send_tester_data();
void reset();
void Manchester_Encode(unsigned char raw_data[], unsigned char encoded_data[], unsigned char n);
void Send_CE_Data(unsigned char data0, unsigned char data, unsigned int data_width_t);