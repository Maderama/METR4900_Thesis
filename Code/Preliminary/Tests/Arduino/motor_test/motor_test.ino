// Define stepper motoro connections and steps per revolution
#define dir1Pin 2
#define step1Pin 3
#define dir2Pin 4
#define step2Pin 5

#define stepsPerRevolution 200

#define distanceTraversed 20; 
#define traversedRotation = distanceTraversed/8; 
#define traversedSteps = distanceRotation * stepsPerRevolution; 

int ledPin = 13; 

void setup() {
  //Serial.begin(9600);
  // Declare output pins: 
  pinMode(step1Pin, OUTPUT); 
  pinMode(dir1Pin, OUTPUT); 
  pinMode(step2Pin, OUTPUT); 
  pinMode(dir2Pin, OUTPUT); 

//  pinMode(ledPin, OUTPUT); 
//  pinMode(ledPin, OUTPUT); 

}

void loop() {
  hey(); 
  // Set the spinning direction clockwise: 


//  // Set the spinning direction to counterclockwise:
//  digitalWrite(dir1Pin, LOW); 
//
//  // Spin the stepper motor 1 revolution quickly: 
//  for (int i = 0; i < (stepsPerRevolution*3); i++) {
//    digitalWrite(step1Pin, HIGH); 
//    delayMicroseconds(5000); 
//    digitalWrite(step1Pin, LOW); 
//    delayMicroseconds(5000); 
//  }
//  delay(1000); 

  //----------------------------------------------

//    // Set the spinning direction clockwise: 
//  digitalWrite(dir2Pin, HIGH); 
//  digitalWrite(ledPin, HIGH);
//
//  // Spin the stepper motor 1 revolution slowly: 
//  for (int i = 0; i < (stepsPerRevolution*6); i++) { 
//    //The following result in 1 step: 
//    digitalWrite(step2Pin, HIGH); 
////    delayMicroseconds(50000000); 
//    delayMicroseconds(1000); 
//    digitalWrite(step2Pin, LOW); 
//    delayMicroseconds(1000); 
//  }
//
//  delay(1000); 
//
//  // Set the spinning direction to counterclockwise:
//  digitalWrite(dir2Pin, LOW); 
//
//  // Spin the stepper motor 1 revolution quickly: 
//  for (int i = 0; i < (stepsPerRevolution*3); i++) {
//    digitalWrite(step2Pin, HIGH); 
//    delayMicroseconds(1000); 
//    digitalWrite(step2Pin, LOW); 
//    delayMicroseconds(1000); 
//  }
//
//  delay(1000); 
  

}



void hey(){
    digitalWrite(dir1Pin, HIGH);

  // Spin the stepper motor 1 revolution slowly: 
  for (int i = 0; i < (2000); i++) { 
    //Serial.println("here"); 
    //The following result in 1 step: 
    digitalWrite(step1Pin, HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(step1Pin, LOW); 
    delayMicroseconds(1000); 
  }

  delay(1000); 

  digitalWrite(dir1Pin, LOW);

  // Spin the stepper motor 1 revolution slowly: 
  for (int i = 0; i < (200); i++) { 
    Serial.println("here"); 
    //The following result in 1 step: 
    digitalWrite(step1Pin, HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(step1Pin, LOW); 
    delayMicroseconds(1000); 
  }

  delay(1000); 
}
