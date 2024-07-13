import serial
import tkinter as tk
#import os


class Serials:

    def __init__(self,master,port,baud=115200): #コンストラクタ
        self.ser=serial.Serial(port,baud) #シリアル定義
        self.master=master

        send1=tk.Button(master,text="1を送信",command=lambda: self.ser_send("1\0"))#ボタン作成
        send2=tk.Button(master,text="2を送信",command=lambda: self.ser_send("2\0"))
        send3=tk.Button(master,text="3を送信",command=lambda: self.ser_send("3\0"))
        send1.pack()
        send2.pack()
        send3.pack()
        
        self.read=tk.Button(master,text="受信",command=self.ser_read)
        self.read.pack()

        self.keys=[]

        master.bind("<KeyPress>",self.key_press) #キー入力受け取るための
        master.bind("<KeyRelease>",self.key_release)

    def ser_send(self,send): #シリアル送信(ボタン用)
        self.ser.write(send.encode())

    def key_press(self,event): #キー入力送信

        if event.keysym not in self.keys:
            self.keys.append(event.keysym)
            send=event.keysym+"\0"
            self.ser.write(send.encode())

    def key_release(self,event): #キー解除送信

        send=event.keysym+"0\0"
        self.keys.remove(event.keysym)
        self.ser.write(send.encode())

    def ser_read(self): #シリアル受信(不使用)
        self.read.config(text=self.ser.readline())


    #def __del__(self):
        #self.ser.close()

#os.system("xset r off")

root=tk.Tk()
Serials(root,"COM3")
root.mainloop()

#os.system("xset r on")