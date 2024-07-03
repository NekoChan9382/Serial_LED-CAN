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

    while (1)
    {
        char buff;
        char data[5];
        // int deg;
        int CAN_ws;
        int CAN_ad;

        if (serial.readable())
        {
            int i = 0;
            while (1)
            {
                serial.read(&buff, sizeof(buff));
                data[i] = buff;
                i++;
                if (buff == '\0')
                {
                    break;
                }
                serial.write(&data, sizeof(data));
            }
            // serial.write("wi",sizeof("wi"));
            if (strcmp(data, "10\0") == 0)
            {
                output[0] = 8000;
            }
            else if (strcmp(data, "11\0") == 0)
            {
                output[0] = -8000;
            }
            else if (strcmp(data, "w\0") == 0)
            {
                CAN_ws = 1;
            }
            else if (strcmp(data, "s\0") == 0)
            {
                CAN_ws = -1;
            }
            else if (strcmp(data, "w0\0") == 0 or strcmp(data, "s0\0") == 0)
            {
                CAN_ws = 0;
            }else if (strcmp(data, "a\0") == 0)
            {
                CAN_ad = 1;
            }
            else if (strcmp(data, "d\0") == 0)
            {
                CAN_ad = -1;
            }
            else if (strcmp(data, "a0\0") == 0 or strcmp(data, "d0\0") == 0)
            {
                CAN_ad = 0;
            }
            else
            {
                output[0] = 0;
            }
        }
        if (CAN_ws == 1)
        {
            output[0] = 8000;
            led = 1;
        }
        else if (CAN_ws == -1)
        {
            output[0] = -8000;
        }
        else
        {
            output[0] = 0;
            led = 0;
        }
        if (CAN_ad ==1){
            output[1] = 8000;
        }
        else if (CAN_ad == -1)
        {
            output[1] = -8000;
        }
        else
        {
            output[1] = 0;
        }
        CANMessage msg(4, (const uint8_t *)output, 8);
        can1.write(msg);
    }
}