// Define stepper motor connections and steps per revolution
//#define turnDirPin 14 //(D5)
//#define turnStepPin 12 //(D6)

#define turnDirPin 6 //
#define turnStepPin 7 //


#define stepsPerRevolution 200

#define angle; 

void setup() {
  // Declare output pins: 
  pinMode(turnStepPin, OUTPUT); 
  pinMode(turnDirPin, OUTPUT); 
}

void loop() {
  // Set the spinning direction clockwise: 
  digitalWrite(turnDirPin, LOW); 

  // Spin the stepper motor 1 revolution slowly: 
  for (int i = 0; i < (stepsPerRevolution); i++) { 
    digitalWrite(turnStepPin, HIGH); 
    delayMicroseconds(9000); 
    digitalWrite(turnStepPin, LOW); 
    delayMicroseconds(9000); 
  }

  delay(3000); 

//  // Set the spinning direction to counterclockwise:
//  digitalWrite(turnDirPin, LOW); 
//
//  // Spin the stepper motor 1 revolution quickly: 
//  for (int i = 0; i < (stepsPerRevolution*3); i++) {
////    digitalWrite(turnStepPin, HIGH); 
////    delayMicroseconds(1000); 
////    digitalWrite(turnStepPin, LOW); 
////    delayMicroseconds(1000); 
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
