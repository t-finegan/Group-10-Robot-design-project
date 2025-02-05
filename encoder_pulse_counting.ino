//Define pin connections 
#define APin 3 
#define BPin 18 
#define M1A 9 
#define M1B 10 
int motorDirection = M1A;
//Define counter variables 
unsigned long ACount = 0; 
unsigned long BCount = 0; 
void setup() { 
  //Declare inputs 
  pinMode(APin, INPUT); 
  pinMode(BPin, INPUT); 
  //Attach interupts 
  //Attach interrupt to APin, which will cause function ATick to execute on  
  //rising pulse 
  attachInterrupt(digitalPinToInterrupt(APin), ATick, RISING);  
  //Attach interrupt to BPin, which will cause function BTick to execute on  
  //rising pulse 
  attachInterrupt(digitalPinToInterrupt(BPin), BTick, RISING); 
  //Open serial monitor 
  Serial.begin(9600); 
  //Start motors 
  analogWrite(motorDirection, 100);
  ACount=0;
  BCount=0;
} 
 
void loop() { 
  Serial.print("A: " + String(ACount)); 
  Serial.print("  B: " + String(BCount) + "\n"); 
  if(ACount>=947 or BCount >=947)//when the wheel has turned once, counters A and B are reset and the motor spinning direction is flipped
  {
    
    ACount=0;
    BCount=0;

    if(motorDirection==M1A)
    {
      motorDireciton = M1B;
    }
    else()
    {
      motorDirection = M1A;
    }
  }
} 
 
void ATick(){ 
  ACount++; //Increment ACount 
} 
 
void BTick(){ 
  BCount++; //Increment BCount 
} 
