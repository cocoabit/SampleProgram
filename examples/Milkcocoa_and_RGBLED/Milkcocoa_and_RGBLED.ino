#include <Nefry.h>
#include <Nefry_Milkcocoa.h>

Nefry_Milkcocoa *milkcocoa;

char *datastore;
int sensorValue;

void setup() {
  milkcocoa->print();//Setup ModuleページにAPPIDの表示をする
  milkcocoa = Nefry_Milkcocoa::begin();//milkcocoaと接続に必要になる処理をします。
  datastore = Nefry.getConfStr(3);//Setup Moduleページに入力されたデータストア名を保存します。
 }

void loop() {
  sensorValue = analogRead(A0);//アナログの入力を読みます。
  Nefry.print("sensor = " );
  Nefry.println(sensorValue);//センサーデータを表示します。
  Nefry.println( milkcocoa->loop(10000) ? "Milkcocoa Connect OK" : "Milkcocoa Connect NG" ); //10秒以内にMilkcocoaに接続できればokと表示されます。
  DataElement elem = DataElement();
  elem.setValue("sensor", sensorValue);//センサーの状態を送信できる形に変換
  milkcocoa->push(datastore, &elem);//Milkcocoaに送信
  Nefry.setLed(sensorValue/4,255,0);//Red(sensorValue/4),Green(255),Blue(0)
  Nefry.ndelay(2000);//2秒待つ
}

