#include <HardwareSerial.h>
int angle = 0;
int maxSpeed = 0;
char bluetoothData[16];

void setup() {
  Serial1.begin(9600, SERIAL_8N1, D9, D8);

}

void loop() {
  for(int i=0;i<10;i++) 
  {
    angle=angle+10;
    maxSpeed = maxSpeed+15;
    sprintf(bluetoothData, "<%i,%i>",angle,maxSpeed);
    Serial1.write(bluetoothData);
    delay(100);
  }
  
}
