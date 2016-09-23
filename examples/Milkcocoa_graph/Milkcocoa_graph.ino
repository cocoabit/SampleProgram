#include <Nefry.h>
#include <Nefry_Milkcocoa.h>
 
Nefry_Milkcocoa *milkcocoa;
 
char *datastore;
int sensorValue;
int sensorValueHistory;
int spanValue;
 
void setup() {
  milkcocoa->print();//Setup ModuleページにAPPIDの表示をする
  milkcocoa = Nefry_Milkcocoa::begin();//milkcocoaと接続に必要になる処理をします。
  datastore = Nefry.getConfStr(3);//Setup Moduleページに入力されたデータストア名を保存します。
  sensorValueHistory = 0;
  spanValue = 0;
}
 
void loop() {
  sensorValue = analogRead(A0);//アナログの入力を読みます。
  Nefry.println(sensorValue);//センサーデータを表示します。
  // 通信を減らすために変化が大きい時だけ送信
  int spanValue = abs(sensorValueHistory - sensorValue);
  if( spanValue > 100 ){
    Nefry.println( milkcocoa->loop(10000) ? "Milkcocoa Connect OK" : "Milkcocoa Connect NG" ); //10秒以内にMilkcocoaに接続できればokと表示されます。
    DataElement elem = DataElement();
    elem.setValue("senser", sensorValue);//センサーの状態を送信できる形に変換
    milkcocoa->push(datastore, &elem);//Milkcocoaに送信
  } else {
    Nefry.println("--");
  }
  sensorValueHistory = sensorValue;
  //
  Nefry.ndelay(1000);//1秒待つ
}
