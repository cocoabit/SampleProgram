#include <Nefry.h>
int sensorValue;
void setup() {
}
void loop() {
  sensorValue = analogRead(A0);//アナログの入力を読みます。
  Nefry.print("sensor = " );
  Nefry.println(sensorValue);//センサーデータを表示します。
  Nefry.ndelay(500);//0.5秒待ちます
  Nefry.setLed(sensorValue/4,255,0);//Red(sensorValue/4),Green(255),Blue(0)
}
