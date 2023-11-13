/***********************************************************************************************************************
* File Name    : state_machine.c
* Device(s)    : DSPIC33FJ128GP804
* Description  : Main Program
* Creation Date: 2021-08-17
* Programmer    : Nguyen 
***********************************************************************************************************************/
#include "xc.h"
#include "time.h"
#include "common.h"
#include "state_machine.h"
#include <stdio.h>

/********************************************************************************************************************************
*****  PRIVATE DEFINES																										
********************************************************************************************************************************/
state_func_t* const state_table[ NUM_STATES ] = {                              
    do_state_idle,
    do_state_cmd,
    do_state_data0,
    do_state_data1,
    do_state_data_store,
    do_state_return_to_tester,
    do_state_read_device_data,
    do_state_send_code_entry,
    do_state_send_tester_data
};

/********************************************************************************************************************************
*****  PRIVATE FUNCTIONS PROTOTYPE																							
********************************************************************************************************************************/
void Manchester_Encode(unsigned char raw_data[], unsigned char encoded_data[], unsigned char n){
    unsigned char i;
    for(i=0;i<n;i++){
        if(raw_data[i]==0){
            encoded_data[2*i] = 1;
            encoded_data[2*i+1] = 0;
        }
        else{
            encoded_data[2*i] = 0;
            encoded_data[2*i+1] =1;
        } 
    }
}

state_t run_state( state_t cur_state, RECEIVE_DATA_t *data ) {
    return state_table[ cur_state ]( data );
//    transition_func_t *transition =
//    transition_table[ cur_state ][ new_state ];
//    if ( transition ) {
//        transition( data );
//    }
};

state_t do_state_idle()
{
    if(LD&&!LD0&&Tester_Reset&&Tester_Start){
        return STATE_CMD;
    }
        
    if(Start&&!Start0&&Tester_LAT){
        return STATE_SEND_CODE_ENTRY;
    }
        
    if(Start&&!Start0&&!Tester_LAT){
        return STATE_SEND_TESTER_DATA;
    }
    return STATE_IDLE;
}

state_t do_state_cmd(){
    cmd = Tester_D0 + Tester_D1*2 + Tester_D2*4 + Tester_D3*8 + Tester_D4*16 + Tester_D5*32 + Tester_D6*64 + Tester_D7*128;
    if(cmd>0x80&&cmd!=0xFF){
        return STATE_RETURN_TO_TESTER;
    }
    if(cmd==0xFF){
        return STATE_READ_DEVICE_DATA;
    }
    else{
        return STATE_DATA0;
    }
}

state_t do_state_data0(){
    if(LD&&!LD0){
        data0[0] = Tester_D0;
        data0[1] = Tester_D1;
        data0[2] = Tester_D2;
        data0[3] = Tester_D3;
        data0[4] = Tester_D4;
        data0[5] = Tester_D5;
        data0[6] = Tester_D6;
        data0[7] = Tester_D7;            
        return STATE_DATA1;
    }
    return STATE_DATA0;
}

state_t do_state_data1(){
    if(LD&&!LD0){
        data1[0] = Tester_D0;
        data1[1] = Tester_D1;
        data1[2] = Tester_D2;
        data1[3] = Tester_D3;
        data1[4] = Tester_D4;
        data1[5] = Tester_D5;
        data1[6] = Tester_D6;
        data1[7] = Tester_D7;            
        return STATE_DATA_STORE;
    }
    return STATE_DATA1;    
}

state_t do_state_data_store(){
    static unsigned char i;
    switch(cmd){
        case 0x00:
            break;
        case 0x01:
            for(i=0;i<8;i++){
                receive_data.code_entry[i] = data0[i];
            }
            receive_data.code_entry[8] = data1[0];
            break;
        case 0x02:
            receive_data.TWDM = 0;
            receive_data.TEWAIT = 0;
            for(i=0;i<8;i++){
                receive_data.TWDM += 2^i*data0[i];
                receive_data.TEWAIT += 2^i*data1[i];
            }
            break;
        case 0x03:
            receive_data.TPW = 0;
            for(i=0;i<8;i++){
                receive_data.TPW += 2^i*data0[i];
            }
            if(!mode1){
                for(i=0;i<6;i++){
                    receive_data.start_bit[i] = data1[i];
                }
                receive_data.dum = data1[6];
            }
            else{
                Manchester_Encode(data1, receive_data.start_bit, 3);
                receive_data.dum = data1[3];
            }
            break;
        case 0x04:
            if(!mode1){
                receive_data.rw[0] = data0[0];
                receive_data.rw[1] = data0[1];
                for(i=0;i<6;i++){
                    receive_data.addr[i] = data0[i+2];
                }
                for(i=0;i<4;i++){
                    receive_data.addr[i+8] = data1[i];
                }
            }
            else{
                Manchester_Encode(data0, receive_data.rw, 1);
                Manchester_Encode(&data0[1], receive_data.addr, 5);
            }
            break;
        case 0x05:
            if(!mode1){
                for(i=0;i<8;i++){
                    receive_data.txdata[i] = data0[i];
                    receive_data.txdata[i+8] = data1[i];
                }
            }
            else{
                Manchester_Encode(data0, receive_data.txdata, 8);
            }
            break;
        case 0x06:
            mode1 = data0[0];
            wait = 0;
            for(i=0;i<8;i++){
               wait += 2^i*data1[i];
            }
            break;
        default:
            break;
    }
    return STATE_IDLE;
}
/*
state_t do_state_return_to_tester(){
    
}

state_t do_state_read_device_data(){
    
}

state_t do_state_send_code_entry(){
    
}

state_t do_state_send_tester_data(){
    
}
*/
