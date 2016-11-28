#include <Nefry.h>
#include <Nefry_Milkcocoa.h>

int OUTPUT_PORT = D3;

// WriteMode

#include<NefryWriteMode.h>

void WriteModeSetup() {
  Nefry.println("Write Mode Setup");
}
void WriteModeloop() {
  Nefry.setLed(random(250), random(255), random(255));
  Nefry.ndelay(500);
}
NefryWriteMode WriteMode(WriteModeSetup, WriteModeloop);

// Main

Nefry_Milkcocoa *milkcocoa;

char *datastore;
int sensorValue;

void setup() {
  milkcocoa->print();//Setup ModuleページにAPPIDの表示をする
  milkcocoa = Nefry_Milkcocoa::begin();//milkcocoaと接続に必要になる処理をします。
  datastore = Nefry.getConfStr(3);//Setup Moduleページに入力されたデータストア名を保存します。
  milkcocoa->on("cocoabit", "push", onpush);
  pinMode(OUTPUT_PORT, OUTPUT);
  digitalWrite(OUTPUT_PORT,LOW);
}

void loop() {
  sensorValue = analogRead(A0);//アナログの入力を読みます。
  Nefry.print("input sensor = " );
  Nefry.println(sensorValue);//センサーデータを表示します。
  Nefry.println( milkcocoa->loop(10000) ? "Milkcocoa Connect OK" : "Milkcocoa Connect NG" ); //10秒以内にMilkcocoaに接続できればokと表示されます。
  Nefry.ndelay(1000);//1秒待つ
}

void onpush(DataElement *elem) {
  Nefry.print("output sensor = " );
  Nefry.println(elem->getInt("output"));
  analogWrite(OUTPUT_PORT,elem->getInt("output"));
};
