/*
 * WebSocketClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include <Nefry.h>
#include<NefryWriteMode.h>

#define USE_SERIAL Nefry

int OUTPUT_PORT = D3;

// WriteMode ----------------------------------------------
void WriteModeSetup() {
  Nefry.println("Write Mode Setup");
}
void WriteModeloop() {
  Nefry.setLed(random(250), random(255), random(255));
  Nefry.ndelay(500);
}
NefryWriteMode WriteMode(WriteModeSetup, WriteModeloop);

WebSocketsClient webSocket;

// const char* ip = Nefry.getConfStr(0);
// const int port = Nefry.getConfValue(1);

//const char* ip = "192.168.225.42";
//const int port = 5000;
int port;
String ip;
int sensorValue;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {
  
    switch(type) {
        case WStype_DISCONNECTED:
              USE_SERIAL.println("[WSc] Disconnected!");
            break;
        case WStype_CONNECTED:
              USE_SERIAL.println("[WSc] Connected to url: "+(String)*payload);
              // send message to server when Connected
              webSocket.sendTXT("Connected");
            break;
        case WStype_TEXT:
              USE_SERIAL.println("[WSc] get text: "+ (String)*payload);
              // send message to server
              webSocket.sendTXT("message here!!!!!!! IP:" + ip + " PORT:" + String(port));
              // webSocket.sendTXT(Nefry.getConfStr(0));
              // webSocket.sendTXT(Nefry.getConfStr(1));
            break;
        case WStype_BIN:
              USE_SERIAL.println("[WSc] get binary lenght:"+lenght);
              hexdump(payload, lenght);
              // send data to server
              // webSocket.sendBIN(payload, lenght);
            break;
    }

}

void setup() {
    pinMode(OUTPUT_PORT, OUTPUT);
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.println("[SETUP] BOOT WAIT :"+t);
        delay(1000);
    }
    //webSocket.begin(ip, port);
    Nefry.setConfHtml("IPAddress",0);
    Nefry.setConfHtml("Port",10);
    port=Nefry.getConfValue(0);
    ip=Nefry.getConfStr(0);
    webSocket.begin(ip.c_str (), port);
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    webSocket.loop();
    // sensorValue = analogRead(A0);//アナログの入力を読みます。
    // Nefry.print("input sensor = " );
    /*
    sensorValue = analogRead(A0);//アナログの入力を読みます。
    Nefry.print("input sensor = " );
    Nefry.println(sensorValue);//センサーデータを表示します。
    Nefry.ndelay(1000);
    */
    Nefry.ndelay(500);
}
