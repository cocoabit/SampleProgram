#include <Nefry.h>
#include <NefryIFTTT.h>

int sensorValue;
int sensorValueHistory;
int spanValue;

String Event, SecretKey;
int counter =0;                       //送信データのカウンタ

void setup() {
  Nefry.setProgramName("CocoaBit_IFTTT");
  Nefry.setConfHtmlStr("SecretKey",0); //Nefry DataStoreのタイトルを指定
  Nefry.setConfHtmlStr("Event",1);     //Nefry DataStoreのタイトルを指定
  SecretKey = Nefry.getConfStr(0);     //Nefry DataStoreからデータを取得
  Event = Nefry.getConfStr(1);         //Nefry DataStoreからデータを取得
}

void loop() {
  sensorValue = analogRead(A0);//アナログの入力を読みます。
  Nefry.println(sensorValue);//センサーデータを表示します。
  // 通信を減らすために変化が大きい時だけ送信
  int spanValue = abs(sensorValueHistory - sensorValue);
  if( spanValue > 100 ){
    Nefry.println("IFTTT Send");
    counter++;                        //送信回数加算
    bool sendData = IFTTT.send(Event, SecretKey,(String)spanValue,(String)(micros()/1000000)+"秒",(String)counter);//IFTTTにデータを送信
                                      //Value1:Analog値,Value2:Nefryが起動してからの秒数,Value3:送信カウンタ
    if (!sendData) {//IFTTTにデータを送信が成功したか失敗したかの判定
      Nefry.setLed(255, 0, 0);        //Errの時、赤色点灯
      Nefry.println("Error");
    }
    Nefry.ndelay(1000);               //送信後1秒間待つ
  } else {
    Nefry.println("--");
  }
  sensorValueHistory = sensorValue;
  Nefry.ndelay(1000);
}
