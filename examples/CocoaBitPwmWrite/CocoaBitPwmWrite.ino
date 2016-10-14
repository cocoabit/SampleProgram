#include<CocoaBit.h>
#include<Nefry.h>
void setup() {
  
}

void loop() {
  for(int i=0;i<100;i++){
  CocoaBit.pwmWrite(D0,i);
  Nefry.ndelay(10);
  }
  for(int i=99;i>0;i--){
    CocoaBit.pwmWrite(D0,i);
    Nefry.ndelay(10);
  }
}
