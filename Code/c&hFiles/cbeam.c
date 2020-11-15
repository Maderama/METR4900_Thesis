#include "cbeam.h"
#include <stdbool.h>
#include "Arduino.h"

//horizontal lead screw
#define cbeamLeadDIR 4
#define cbeamLeadSTEP 5
#define cbeamDistanceTraversed x

#define cbeamHomeSwitch A3

bool cbeamHomeFlag = false;

void cbeamInit() {
  pinMode(cbeamLeadDIR, OUTPUT);
  pinMode(cbeamLeadSTEP, OUTPUT);
  pinMode(cbeamHomeSwitch, INPUT);
}

void cbeamForwardMovement(float cbeamLeadSteps) {
  // Set the spinning direction clockwise/fowards
  digitalWrite(cbeamLeadDIR, LOW);

  // Spin the stepper motor _ revolutions slowly:
  for (int i = 0; i < cbeamLeadSteps; i++) {
    //The following result in 1 step:
    digitalWrite(cbeamLeadSTEP, HIGH);
    delayMicroseconds(1000);
    digitalWrite(cbeamLeadSTEP, LOW);
    delayMicroseconds(1000);
  }

  delay(1000);
}

void cbeamBackMovement(float cbeamLeadSteps) {
  // Set the spinning direction anticlockwise/backwards
  digitalWrite(cbeamLeadDIR, HIGH);

  // Spin the stepper motor _ revolutions slowly:
  for (int i = 0; i < cbeamLeadSteps; i++) {
    if (analogRead(cbeamHomeSwitch) <= 255 && !cbeamHomeFlag) {
      digitalWrite(cbeamLeadSTEP, HIGH);
      delayMicroseconds(1000);
      digitalWrite(cbeamLeadSTEP, LOW);
      delayMicroseconds(1000);
    } else {
      cbeamHomeFlag = true;
    }
  }
  delay(1000);
}

void homeCbeam() {
  while (!cbeamHomeFlag) {
    cbeamBackMovement(1000000);
  }
}
