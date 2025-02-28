#include <SoftwareSerial.h>

const byte numChars = 32;
char receivedChars [numChars];
char tempChars[numChars];

boolean newData = false;

int integer0 = 0;
int integer1 = 1;

SoftwareSerial BTSerial(8, 9);//connect bt rx to arduino pin 9 (tx) | connect bt tx to arduino pin 8(rx)

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
    showParsedData();
    newData = false;
  }

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
    integer0 = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ",");
    integer1 = atof(strtokIndx);     // convert this part to a float

}

void showParsedData()  {
  Serial.print("Angle:");
  Serial.print(integer0);
  Serial.print(",");
  Serial.print("Speed:");
  Serial.println(integer1);
}