#include <Nefry.h>
#include<NefryWriteMode.h>

// WriteMode --------------------------------------
void WriteModeSetup() {
  Nefry.println("Write Mode Setup");
}
void WriteModeloop() {
  Nefry.setLed(random(250), random(255), random(255));
  Nefry.ndelay(500);
}
NefryWriteMode WriteMode(WriteModeSetup, WriteModeloop);

// Main -------------------------------------------

void setup() {
  pinMode(D3,OUTPUT);
}

void loop() {
  Nefry.println("ON");
  digitalWrite(D3,LOW);
  Nefry.ndelay(1000);
  Nefry.println("OFF");
  digitalWrite(D3,HIGH);
  Nefry.ndelay(1000);
}
