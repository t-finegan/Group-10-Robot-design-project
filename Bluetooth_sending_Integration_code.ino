#include <HardwareSerial.h>
#include <ESP32Servo.h>

Servo myservo;

int pos = 90;
int servoPin = 2;//can be any GPIO for esp32 nano
int motorForwardPin = 3;//digitalWrite will go to D3
int motorReversePin = 4;//digitalWrite will go to D4


int angle = 0;
int maxSpeed = 0;
char bluetoothData[16];

const byte numChars = 64;
char receivedChars [numChars];
char tempChars[numChars];

boolean newData = false;

float tiltFloat = 90;
float verticalMovementFloat = 0;
int forkliftVerticalMovement = 0;
int forkliftTilt = 90;


void setup() {
  Serial1.begin(9600, SERIAL_8N1, D9, D8);
  Serial.begin(115200);
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 750, 2250); // attaches the servo on pin 18 to the servo object
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
}

void loop() {

  sendToArduino();
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
    forkliftMovement();
    newData = false;
  }

  //delay(100);
  
}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
 
  while (BTSerial.available() > 0 && newData == false) {
      rc = BTSerial.read();

      if (recvInProgress == true) {
          if (rc != endMarker) {
              receivedChars[ndx] = rc;
              ndx++;
              if (ndx >= numChars) {
                  ndx = numChars - 1;
              }
          }
          else {
              receivedChars[ndx] = '\0'; // terminate the string
              recvInProgress = false;
              ndx = 0;
              newData = true;
          }
      }

      else if (rc == startMarker) {
          recvInProgress = true;
      }
  }
}

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars, ","); // this continues where the previous call left off
    tiltFloat = atof(strtokIndx);     // convert this part to a float
    tiltFloat = tiltFloat*(90/512);

    strtokIndx = strtok(NULL, ",");
    verticalMovementFloat = atof(strtokIndx);   // convert this part to a float
    verticalMovementFloat = verticalMovementFloat*(255/512);

    strtokIndx = strtok(NULL, ",");
    angle = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    maxSpeed = atoi(strtokIndx);

}

void forkliftMovement()  {
  forkliftTilt = tiltFloat + 90;

  if(forkliftTilt>135)
  {

    if(pos<180)
    {
      pos=pos+5;//adjust value after testing
    }
    myservo.write(pos);

  }
  if(forkliftTilt<45)
  {

    if(pos>0)
    {
      pos=pos-5;
    }
    myservo.write(pos)

  }
  
  forkliftVerticalMovement = int(trunc(tiltFloat);
  

  
  if(forkliftVerticalMovement>50)//needs to be changed for deadspace on joystick
  {
    analogWrite(motorForwardPin, forkliftVerticalMovement);
    
  else if(forkliftVerticalMovement<-50)//needs to be changed for deadspace
  {
    analogWrite(motorReversePin, forkliftVerticalMovement); 
  }
  else
  {
    analogWrite(motorReversePin, 0);
    analogWrite(motorForwardPin, 0);
  }
}

void sendToArduino()
{
    sprintf(bluetoothData, "<%i,%i>",angle,maxSpeed);
    Serial1.write(bluetoothData);
}
