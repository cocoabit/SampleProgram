void setup() {
  pinMode(D0, OUTPUT); //CocoaBitのD0を出力モードにする
}
void loop() {
  //SWを押した時にLEDが点灯する
  if (analogRead(A0) > 500) {//7(押してない)or970(押されてる)中間で分岐します
    //押した時
    digitalWrite(D0, HIGH); //LED点灯
  } else {
    //離した時
    digitalWrite(D0, LOW); //LED消灯
  }
  delay(100);//0.1秒待つ
}
