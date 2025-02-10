#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);//connect bt rx to arduino 11 pin (tx) | connect bt tx to arduino 10(rx)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println("ENTER AT COMMANDS");
  BTSerial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  //if (Serial.available())
    //BTSerial.write(Serial.read());
}
