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
    char data;
    int deg;
    int ledst;

    if (serial.readable()){
    serial.read(&data, sizeof(data));
    if(data=='5'){
        output[0] = 4000;
    } else if(data=='4'){
        output[0] = -2000;
    }else if (data == '7') {
        ledst=1;
    
    }else if(data=='8'){
        ledst=0;

    }
    else{
        output[0] = 0;
    }
    if (ledst==1){
        output[0]=4000;
    }else{
        output[0]=0;
    }
    CANMessage msg(1, (const uint8_t *)output, 8);
    can1.write(msg);

}

}

}