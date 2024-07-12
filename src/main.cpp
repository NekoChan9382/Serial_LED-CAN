#include "mbed.h"
#include "Servo.hpp"
#include <cstdint>

CAN can1(PA_11, PA_12, (int)1e6); //CAN初期化
BufferedSerial serial(USBTX, USBRX, 115200); //シリアル初期化
int16_t output[4] = {0, 0, 0, 0}; //CAN送信データ
CANMessage msg; //CANメッセージ定義
DigitalOut led(LED1); //LED初期化

int main()
{

    while (1)
    {
        
        // int deg;
        int8_t CAN_Send; //CAN送信データ保存


        if (serial.readable())
        {
            int i = 0; //繰り返し変数
            char buff='0'; //シリアル受信
            char data[5]; //受信データ保存

            while (buff != '\0' and i < 5)
            {
                serial.read(&buff, sizeof(buff)); //シリアル受信
                data[i] = buff; //受信データ保存
                i++;

            }

            //データ処理
            /*if (strcmp(data, "10\0") == 0)
            {
                output[0] = 8000;
            }
            else if (strcmp(data, "11\0") == 0)
            {
                output[0] = -8000;
            }*/
            if (strcmp(data, "w\0") == 0)
            {
                CAN_Send = 1;
            }
            else if (strcmp(data, "s\0") == 0)
            {
                CAN_Send = -1;
            }
            else if (strcmp(data, "w0\0") == 0 or strcmp(data, "s0\0") == 0)
            {
                CAN_Send = 0;
            }else if (strcmp(data, "a\0") == 0)
            {
                CAN_Send = 2;
            }
            else if (strcmp(data, "d\0") == 0)
            {
                CAN_Send = -2;
            }
            else if (strcmp(data, "a0\0") == 0 or strcmp(data, "d0\0") == 0)
            {
                CAN_Send = 3;
            }
            else
            {
                output[0] = 0;
            }
        }//受信データを送信データに整理
        if (CAN_Send == 1)
        {
            output[0] = 8000;
            led = 1;
        }
        else if (CAN_Send == -1)
        {
            output[0] = -8000;
        }
        else if(CAN_Send == 0)
        {
            output[0] = 0;
            led = 0;
        }
        if (CAN_Send ==2){
            output[1] = 8000;
        }
        else if (CAN_Send == -2)
        {
            output[1] = -8000;
        }
        else if (CAN_Send == 3)
        {
            output[1] = 0;
        }
        CANMessage msg(4, (const uint8_t *)output, 8); //メッセージ構築
        can1.write(msg); //CAN送信
    }
}