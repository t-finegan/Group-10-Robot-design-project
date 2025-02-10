#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);//connect bt rx to arduino 11 pin (tx) | connect bt tx to arduino 10(rx)
int motorSpeed=30;
int angularMotorSpeed=60;
int angle=10;
char bluetoothData[16];

void setup() 
{
  BTSerial.begin(38400);
}

void loop() 
{
  for(int i=0;i<10;i++)
  {
    sprintf(bluetoothData,"%i,%i,%i.",angle,motorSpeed,angularMotorSpeed);
    BTSerial.write(bluetoothData);
    delay(100);
  }
}
