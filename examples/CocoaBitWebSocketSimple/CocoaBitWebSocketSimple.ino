/*
 * CocoaBitWebSocketSimple.ino
 * 
 *  参考：
 *  https://github.com/Links2004/arduinoWebSockets/blob/master/examples/WebSocketClient/WebSocketClient.ino
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

// Main ----------------------------------------------
WebSocketsClient webSocket;

int port;
String ip;
String consoleText;
int sensorValue = 0;
int sensorValuePrevious = 500;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {
  
    switch(type) {
        case WStype_DISCONNECTED:
              Nefry.println("[WSc] Disconnected!");
            break;
        case WStype_CONNECTED:
              Nefry.println("[WSc] Connected to url: "+(String)*payload);
              // send message to server when Connected
              webSocket.sendTXT("Connected");
            break;
        case WStype_TEXT:
              Nefry.println("[WSc] get text: "+ (String)*payload);
              // send message to server
              //
            break;
        case WStype_BIN:
              Nefry.println("[WSc] get binary lenght:"+lenght);
              hexdump(payload, lenght);
              // send data to server
              // webSocket.sendBIN(payload, lenght);
            break;
    }

}

void setup() {
    pinMode(OUTPUT_PORT, OUTPUT);
    for(uint8_t t = 4; t > 0; t--) {
        Nefry.println("[SETUP] BOOT WAIT :"+t);
        delay(1000);
    }
    Nefry.setConfHtml("IPAddress",0);
    Nefry.setConfHtml("Port",10);
    ip=Nefry.getConfStr(0);
    port=Nefry.getConfValue(0);
    // port=5000;
    webSocket.begin(ip.c_str (), port);
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    // consoleText = "{'message':'message send!','ip':'" + ip + "','port':" + String(port) + ",'module_name':'" + Nefry.getModuleName() + "','sensorValue':" + String(sensorValue) + "}";
    sensorValue = analogRead(A0);//アナログの入力を読みます。
    consoleText = String(Nefry.getModuleName()) + ':' + port + ':' + String(sensorValue);
    
    Nefry.print("sensorValue = " );
    Nefry.println(sensorValue);//センサーデータを表示します。

    int spanValue = abs( sensorValuePrevious - sensorValue );

    // 値に大きく変化があったら
    if( spanValue > 100 ){
      Nefry.print("consoleText = ");
      Nefry.println(consoleText);
      webSocket.sendTXT(consoleText);
    }

    sensorValuePrevious = sensorValue;
    
    Nefry.ndelay(1000);

    webSocket.loop();
}
