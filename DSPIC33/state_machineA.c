///***********************************************************************************************************************
//* File Name    : state_machine.c
//* Device(s)    : DSPIC33FJ64GP802
//* Description  : State Machine Program
//* Creation Date: 2022-03-15
//* Programmer    : Nguyen 
//***********************************************************************************************************************/
//
///*********************************************************************************************************************************
//*****  INCLUDES																												
//*********************************************************************************************************************************/
//#include "state_machineA.h"
//
///********************************************************************************************************************************
//*****  DEFINES																												*****
//********************************************************************************************************************************/
//#define READ_DEVICE_WAIT 2 //2 tpw wait
///********************************************************************************************************************************
//*****  VARIABLES																											*****
//********************************************************************************************************************************/
//unsigned char Reset = 1;
//unsigned char Reset0 = 1;
//unsigned char LD = 1;
//unsigned char LD0 = 1;
//unsigned char Start = 1;
//unsigned char Start0 = 1;
//
//unsigned char cmd;
//unsigned char data0[8];
//unsigned char data1[8];
//unsigned char rev;
//RECEIVE_DATA receive_data_t;
//unsigned char PG_Read[8];
//unsigned char data_to_send[100];   //CE value for transmission
//unsigned int data_width[100];               //time between 2 CE transmission
//unsigned char send_first_data;
//
//
///********************************************************************************************************************************
//*****  FUNCTIONS PROTOTYPE																									*****
//********************************************************************************************************************************/
//state_A do_state_machineA(state_A TEST0){
////    while(1){  
//        switch(TEST0){
//            case STATE_IDLE:
//                PIC_Busy = 1;
//                TEST0 = do_state_idle();
//                break;
//            case STATE_CMD:
//                TEST0 = do_state_cmd();
//                break;
//            case STATE_DATA0:
//                TEST0 = do_state_data0();
//                break;
//            case STATE_DATA1:
//                TEST0 = do_state_data1();
//                break;
//            case STATE_DATA_STORE:
//                PIC_Busy = 0;
//                TEST0 = do_state_data_store();
//                break;
//            case STATE_SEND_CODE_ENTRY:
//                PIC_Busy = 0;
//                TEST0 = do_state_send_code_entry();
//                break;
//            case STATE_SEND_TESTER_DATA:
//                PIC_Busy = 0;
//                TEST0 = do_state_send_tester_data();
//                break;
//            case STATE_READ_DEVICE_DATA:
//                PIC_Busy = 0;
//                TEST0 = do_state_read_device_data();
//                break;
//            case STATE_RETURN_TO_TESTER:
//                PIC_Busy = 0;
//                TEST0 = do_state_return_to_tester();
//                break;
//            case STATE_RETURN_DATA0:
//                PIC_Busy = 0;
//                TEST0 = do_state_return_data0();
//                break;
//            default:
//                break;
//        }
//        LD0 = LD;
//        LD = Tester_LD;
//        Start0 = Start;
//        Start = Tester_Start;
//        Reset0 = Reset;
//        Reset = Tester_Reset;
//        if(Reset&&!Reset0){
//            reset();
//            TEST0 = STATE_IDLE;
//        }
////    }   
//    return TEST0;
//}
//
//void Manchester_Encode(unsigned char raw_data[], unsigned char encoded_data[], unsigned char n){
//    unsigned char i;
//    for(i=0;i<n;i++){
//        if(raw_data[i]==0){
//            encoded_data[2*i] = 1;
//            encoded_data[2*i+1] = 0;
//        }
//        else{
//            encoded_data[2*i] = 0;
//            encoded_data[2*i+1] =1;
//        } 
//    }
//}
//
//state_A do_state_idle()
//{
//    if(LD&&!LD0&&Tester_Reset&&Tester_Start){
//        return STATE_CMD;
//    }
//    if(Start&&!Start0&&Tester_LAT){
//        return STATE_SEND_CODE_ENTRY;
//    }   
//    if(Start&&!Start0&&!Tester_LAT){
//        return STATE_SEND_TESTER_DATA;
//    }
//    return STATE_IDLE;
//}
//
//state_A do_state_cmd(){
//    cmd = Tester_D0_input + Tester_D1_input*2 + Tester_D2_input*4 + Tester_D3_input*8 + Tester_D4_input*16 + Tester_D5_input*32 + Tester_D6_input*64 + Tester_D7_input*128;
//    if(cmd>=0x80&&cmd!=0xFF){
//        return STATE_RETURN_TO_TESTER;
//    }
//    if(cmd==0xFF){
//        return STATE_READ_DEVICE_DATA;
//    }
//    else{
//        return STATE_DATA0;
//    }
//}
//
//state_A do_state_data0(){
//    if(LD&&!LD0){
//        data0[0] = Tester_D0_input;
//        data0[1] = Tester_D1_input;
//        data0[2] = Tester_D2_input;
//        data0[3] = Tester_D3_input;
//        data0[4] = Tester_D4_input;
//        data0[5] = Tester_D5_input;
//        data0[6] = Tester_D6_input;
//        data0[7] = Tester_D7_input;            
//        return STATE_DATA1;
//    }
//    return STATE_DATA0;
//}
//
//state_A do_state_data1(){
//    if(LD&&!LD0){
//        data1[0] = Tester_D0_input;
//        data1[1] = Tester_D1_input;
//        data1[2] = Tester_D2_input;
//        data1[3] = Tester_D3_input;
//        data1[4] = Tester_D4_input;
//        data1[5] = Tester_D5_input;
//        data1[6] = Tester_D6_input;
//        data1[7] = Tester_D7_input;            
//        return STATE_DATA_STORE;
//    }
//    return STATE_DATA1;    
//}
//
//
//
//state_A do_state_return_data0(){
//    if(LD&&!LD0){
//        Tester_D0_output = data0[0];
//        Tester_D1_output = data0[1];
//        Tester_D2_output = data0[2];
//        Tester_D3_output = data0[3];
//        Tester_D4_output = data0[4];
//        Tester_D5_output = data0[5];
//        Tester_D6_output = data0[6];
//        Tester_D7_output = data0[7];
//        wait_ms(10);
//        io_config_read_from_tester();
//        return STATE_IDLE;
//    }
//    return STATE_RETURN_DATA0;
//}
//
//state_A do_state_data_store(){
//    static unsigned char i;
//    switch(cmd){
//        case 0x00:
//            break;
//        case 0x01:
//            for(i=0;i<8;i++){
//                receive_data_t.code_entry[i] = data0[i];
//            }
//            receive_data_t.code_entry[8] = data1[0];
//            break;
//        case 0x02:
//            receive_data_t.TWDM = 0;
//            receive_data_t.TEWAIT = 0;
//            for(i=0;i<8;i++){
//                receive_data_t.TWDM += data0[i]<<i;
//                receive_data_t.TEWAIT += data1[i]<<i;
//            }
//            break;
//        case 0x03:
//            receive_data_t.TPW = 0;
//            for(i=0;i<8;i++){
//                receive_data_t.TPW += data0[i]<<i;
//            }
//            Manchester_Encode(data1, receive_data_t.start_bit, 3);
//            receive_data_t.dum = data1[3];
//            break;
//        case 0x04:
//            Manchester_Encode(data0, receive_data_t.rw, 1);
//            for(i=1;i<3;i++){
//                rev = data0[i];
//                data0[i]=data0[6-i];
//                data0[6-i] = rev;
//            }
//            Manchester_Encode(&data0[1], receive_data_t.addr, 5);
//            break;
//        case 0x05:
//            for(i=0;i<4;i++){
//                rev = data0[i];
//                data0[i]=data0[7-i];
//                data0[7-i] = rev;
//            }
//            Manchester_Encode(data0, receive_data_t.txdata, 8);
//            break;
//        default:
//            break;
//    }
//    return STATE_IDLE;
//}
//
//state_A do_state_return_to_tester(){
//    io_config_send_to_tester();
//    static unsigned char i;
//    switch(cmd){
//        case 0x80:
//            for(i=0;i<8;i++){
//                data0[i] = !PG_Read[7-i];
//            }
//            break;
//        default:
//            break;
//    }
//    return STATE_RETURN_DATA0;
//}
//
//state_A do_state_read_device_data(){
//    static int i,j;
//    static unsigned char read_t;
//    static unsigned char start_clk = 20 + READ_DEVICE_WAIT;
//    static char dm;
//    j = 0;
//    for(i=0;i<6;i++){
//        data_to_send[j] = receive_data_t.start_bit[i];
//        j++;
//    }
//    for(i=0;i<10;i++){
//        data_to_send[j] = receive_data_t.addr[i];
//        j++;
//    }
//    for(i=1;i>=0;i--){
//        data_to_send[j] = receive_data_t.rw[i];
//        j++;
//    }
//    //add wait
//    for(i=0;i<READ_DEVICE_WAIT;i++){
//        data_to_send[j] = 0;
//        j++;
//    }
//    for(i=0;i<16;i+=2){
//        data_to_send[j] = 1;
//        j++;
//        data_to_send[j] = 0;
//        j++;
//    }
//    if(receive_data_t.dum){
//        data_to_send[j] = 0;
//        j++;
//        data_to_send[j] = 1;
//        j++;
//    }
//    else{
//        data_to_send[j] = 1;
//        j++;
//        data_to_send[j] = 0;
//        j++;
//    }
//    data_to_send[j] = END_SEND_DATA;
//    for(i = 0; i<j; i++){
//        data_width[i] = receive_data_t.TPW;
//    } 
//    i = 0;
//    LED = 0;
//    send_first_data = 0;
//    T3_interrupt_setup();
//    while(data_to_send[i]!=END_SEND_DATA){
//        Send_CE_Data(data_to_send[0], data_to_send[i+1], data_width[i]);
//        i++;
//        if(i>=start_clk){
//            dm = i-start_clk;
//            if(dm%2==0){
//                read_t = dm/2;
//                PG_Read[read_t] = Device_read;
//                LED = !(read_t%2);
//            }
//        }
//    }
//    return STATE_IDLE; 
//}
//
//state_A do_state_send_code_entry(){
//    static unsigned char i, j;
//    j = 0;
//    data_to_send[j] = 0;    //in TWDM CE = 0
//    j++;
//    data_to_send[j] = 1;    //in TEWAIT CE = 1
//    j++;
//    for(i=0;i<9;i++){
//        data_to_send[j] = receive_data_t.code_entry[i];
//        j++;
//    }
//    data_to_send[j] = receive_data_t.dum;
//    j++;
//    data_to_send[j] = END_SEND_DATA;
//    j++;
//    data_width[0] = receive_data_t.TWDM*1000;
//    data_width[1] = receive_data_t.TEWAIT*1000;
//    for(i=2;i<11;i++){
//        data_width[i] = receive_data_t.TPW;
//    }    
//    i = 0;
//    T3_interrupt_setup();
//    send_first_data = 0;
//    while(data_to_send[i]!=END_SEND_DATA){
//        Send_CE_Data(data_to_send[0], data_to_send[i+1], data_width[i]);
//        i++;
//    }
//    return STATE_IDLE;
//}
//
//state_A do_state_send_tester_data(){
//    static unsigned char i, j;
//    j = 0;
//    for(i=0;i<6;i++){
//        data_to_send[j] = receive_data_t.start_bit[i];
//        j++;
//    }
//    for(i=0;i<10;i++){
//        data_to_send[j] = receive_data_t.addr[i];
//        j++;
//    }
//    for(i=0;i<2;i++){
//        data_to_send[j] = receive_data_t.rw[i];
//        j++;
//    }
//    for(i=0;i<16;i++){
//        data_to_send[j] = receive_data_t.txdata[i];
//        j++;
//    }
//    data_to_send[j] = receive_data_t.dum;
//    j++;
//    data_to_send[j] = END_SEND_DATA;
//    j++;
//    for(i = 0; i<(j-1); i++){
//        data_width[i] = receive_data_t.TPW;
//    } 
//    i = 0;
//    T3_interrupt_setup();
//    send_first_data = 0;
//    while(data_to_send[i]!=END_SEND_DATA){
//        Send_CE_Data(data_to_send[0], data_to_send[i+1], data_width[i]);
//        i++;
//    }
//    return STATE_IDLE;
//}
//
//void Send_CE_Data(unsigned char data0, unsigned char data, unsigned int data_width_t){
////    T3CONbits.TON = 0; // Disable Timer
//    if(data_width_t<10000){
//        T3CONbits.TCKPS = 0b00; // Select 1:1 Pre_scaler    
//        PR3 = data_width_t*4-19; // For TPW      Load the period value, different with each system clock
//    }
//    else{
//        T3CONbits.TCKPS = 0b01; // Select 1:8 Pre_scaler
//        PR3 = data_width_t/2; // For TEWAIT, TWDM      Load the period value, different with each system clock        
//    }
//    //IPC0bits.T3IP = 0x01; // Set Timer3 Interrupt Priority Level
//    CE_data = data;
//    if(send_first_data==0){
//        T3CONbits.TON = 1;
//        PIC_CE = data0;
//        send_first_data = 1;
//    }
//    if(data==END_SEND_DATA){
//        T3CONbits.TON = 0;
//        IEC0bits.T3IE = 0; // Disable Timer3 interrupt
//        T3_Interrupt_Flag = 1;
//    }
//    while(T3_Interrupt_Flag==0){
//    
//    }
//    T3_Interrupt_Flag = 0;
//}
//
//void reset(){
//    
//}