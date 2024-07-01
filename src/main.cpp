//main.cpp
#include "drivers/include/drivers/BufferedSerial.h" 
#include "drivers/include/drivers/DigitalOut.h"
#include "drivers/include/drivers/interfaces/InterfaceCAN.h"
#include "mbed.h"
#include "Servo.hpp"
#include <cstdint>



CAN can1(PA_11, PA_12, (int)1e6);
BufferedSerial serial(USBTX, USBRX, 115200);
int16_t output[4] = {0, 0, 0, 0};
CANMessage msg;
DigitalOut led(LED1);

int main()
{

while (1) {
    char buff;
    char data[3];
    //int deg;
    int CAN_Send;

    if (serial.readable()){
        int i=0;
        while(1){
            serial.read(&buff, sizeof(buff));
            data[i]=buff;
            serial.write("10", sizeof("10"));
            i++;
            if (buff == '\0'){
                break;
            }
        }
    //serial.write("wi",sizeof("wi"));
    if(strcmp(data, "10\0") == 0){
        output[0] = 4000;
    } else if(strcmp(data, "11\0") == 0){
        output[0] = -2000;
    }else if (strcmp(data, "w\0") == 0) {
        CAN_Send=1;
    
    }else if(strcmp(data, "s\0") == 0){
        CAN_Send=-1;

    }
    else if(strcmp(data, "0\0") == 0){
        CAN_Send=0;
    
    }
    else{
        output[0] = 0;
    }
    }
if (CAN_Send==1){
        output[0]=4000;
    }else if(CAN_Send==-1){
        output[0]=-4000;
    }else{
        output[0]=0;
    }
    CANMessage msg(4, (const uint8_t *)output, 8);
    can1.write(msg);
}

}