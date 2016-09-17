void setup() {
  // put your setup code here, to run once:
  pinMode(D0,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(analogRead(A0)>500){
    digitalWrite(D0,LOW);
  }else{
    digitalWrite(D0,HIGH);
  }
}
