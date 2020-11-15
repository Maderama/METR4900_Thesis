#include <RadioHead.h>
#include <SPI.h>
#include <RH_nRF24.h>
#include <stdio.h>
#include <stdlib.h>

//---------------- RADIO FREQUENCY --------------------------
// Singleton instance of the radio driver
RH_NRF24 nrf24;

uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf);
char coords[sizeof(buf)];
int i = 0;
bool check = false;

//---------------------------String Split----------------------
char shelf[sizeof(buf)];
char xcoord[sizeof(buf)];
char ycoord[sizeof(buf)];

int countX = 0;
int countY = 0;

int shelfNo;
int xCoords;
int yCoords;

//---------------- STEPPER MOTORS ----------------------------
// Define stepper motoor connections and steps per revolution
#define stepsPerRev 200

//LEAD SCREWS
//vertical lead screw
#define armLeadDIR 2
#define armLeadSTEP 3
//#define armDistanceTraversed y

//horizontal lead screw
#define cbeamLeadDIR 4
#define cbeamLeadSTEP 5
//#define cbeamDistanceTraversed x

//TIMING BELT
#define centreBeamDIR 6
#define centreBeamSTEP 7
//#define centreBeamDistanceTraversed z

//SWITHCES
#define armHomeSwitch A1
#define centreBeamHomeSwitch A2
#define cbeamHomeSwitch A3
#define centreBeamLimitSwitch A4
#define cbeamLimitSwitch A5

//calculations/setting distances
int armLeadSteps;
int cbeamLeadSteps;
int centreBeamSteps;

int stepsPerMM = 25;

//flags
bool centreBeamHomeFlag = false;
bool armHomeFlag = false;
bool cbeamHomeFlag = false;
bool centreBeamLimitFlag = false;
bool cbeamLimitFlag = false;

const int ledPin =  13;

//-------------------- SETUP -----------------------------
void setup() {
  Serial.begin(9600);

  //while (!Serial)
  ; // wait for serial port to connect. needed for Leonardo only
  if (!nrf24.init()) {
    Serial.print("init failed");
    // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  }
  if (!nrf24.setChannel(1)) {
    Serial.println("setChannel failed");
  }
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)) {
    Serial.println("setRF failed");
  }

  // Declare output pins:
  pinMode(armLeadDIR, OUTPUT);
  pinMode(armLeadSTEP, OUTPUT);
  pinMode(cbeamLeadDIR, OUTPUT);
  pinMode(cbeamLeadSTEP, OUTPUT);
  pinMode(centreBeamDIR, OUTPUT);
  pinMode(centreBeamSTEP, OUTPUT);

  pinMode(armHomeSwitch, INPUT);
  pinMode(centreBeamHomeSwitch, INPUT);
  pinMode(cbeamHomeSwitch, INPUT);
  pinMode(centreBeamLimitSwitch, INPUT);
  pinMode(cbeamLimitSwitch, INPUT);

  pinMode(ledPin, OUTPUT);
}

//--------------------- LOOP -----------------------------

void loop() {

  delay(2000);

  while (!check) {
    receive();
  }

  homeAll(); 
  resetFlags(); 

  shelfNo = 1; 

  switch (shelfNo) {
    case 1:
      Serial.println("case 1"); 
      centreBeamUpMovement(960);
      break;
    case 2:
      Serial.println("case 2"); 
      centreBeamUpMovement(2300); 
      break; 
    case 3:
      Serial.println("case 3"); 
      centreBeamUpMovement(2955); 
      break; 
    default: 
      centreBeamUpMovement(1500); 
    }

    //ARM FULLY EXTENDED: 340MM
    //int horDistSteps = (pow((pow(xCoords,2) + pow(yCoords,2)),0.5) - 340)*25; 
    cbeamForwardMovement(600);
    
    delay(1000);

    armDownMovement(850); 

    homeAll(); 
    resetFlags(); 

    check = false; 

    while(1){
    }
}


//----------------------- CENTRE BEAM -----------------------------------

void centreBeamUpMovement(float centreBeamSteps) {
  // Set the spinning direction clockwise/upwards
  digitalWrite(centreBeamDIR, HIGH);

  // Spin the stepper motor _ revolutions slowly:
  for (int i = 0; i < centreBeamSteps; i++) {
    if (analogRead(centreBeamLimitSwitch) <= 255 && !centreBeamLimitFlag) {
      //The following result in 1 step:
      digitalWrite(centreBeamSTEP, HIGH);
      delayMicroseconds(4000);
      digitalWrite(centreBeamSTEP, LOW);
      delayMicroseconds(4000);
    } else {
      centreBeamLimitFlag = true;
      break;
    }
  }
  delay(1000);
}


void centreBeamDownMovement(float centreBeamSteps) {
  // Set the spinning direction anticlockwise/upwards
  digitalWrite(centreBeamDIR, LOW);

  // Spin the stepper motor _ revolutions slowly:
  for (int i = 0; i < centreBeamSteps; i++) {
    if (analogRead(centreBeamHomeSwitch) <= 255 && !centreBeamHomeFlag) {
      //The following result in 1 step:
      digitalWrite(centreBeamSTEP, HIGH);
      delayMicroseconds(4000);
      digitalWrite(centreBeamSTEP, LOW);
      delayMicroseconds(4000);
    } else {
      centreBeamHomeFlag = true;
      break;
    }
  }
  delay(1000);
}


//----------------------- C BEAM -----------------------------------
void cbeamForwardMovement(float cbeamLeadSteps) {
  // Set the spinning direction clockwise/fowards
  digitalWrite(cbeamLeadDIR, LOW);

  // Spin the stepper motor _ revolutions slowly:
  for (int i = 0; i < cbeamLeadSteps; i++) {
    if (analogRead(cbeamLimitSwitch) <= 255 && !cbeamLimitFlag) {
      digitalWrite(cbeamLeadSTEP, HIGH);
      delayMicroseconds(2000);
      digitalWrite(cbeamLeadSTEP, LOW);
      delayMicroseconds(2000);
    } else {
      cbeamLimitFlag = true;
      break;
    }
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
      delayMicroseconds(2000);
      digitalWrite(cbeamLeadSTEP, LOW);
      delayMicroseconds(2000);
    } else {
      cbeamHomeFlag = true;
      break;
    }
  }
  delay(1000);
}


//----------------------- ARM -----------------------------------
void armUpMovement(float armLeadSteps) {
  // Set the spinning direction clockwise/fowards
  digitalWrite(armLeadDIR, LOW);

  // Spin the stepper motor _ revolutions slowly:
  for (int i = 0; i < armLeadSteps; i++) {
    if (analogRead(armHomeSwitch) <= 255 && !armHomeFlag) {
      //The following result in 1 step:
      digitalWrite(armLeadSTEP, HIGH);
      delayMicroseconds(6000);
      digitalWrite(armLeadSTEP, LOW);
      delayMicroseconds(6000);
    } else {
      armHomeFlag = true;
      break;
    }
  }
  delay(1000);
}

float armDownMovement(float armLeadSteps) {
  // Set the spinning direction clockwise/fowards
  digitalWrite(armLeadDIR, HIGH);

  // Spin the stepper motor _ revolutions slowly:
  for (int i = 0; i < armLeadSteps; i++) {
    //The following result in 1 step:
    digitalWrite(armLeadSTEP, HIGH);
    delayMicroseconds(5000);
    digitalWrite(armLeadSTEP, LOW);
    delayMicroseconds(5000);
  }

  delay(1000);
}


//----------------------- HOMING FUNCTIONS -----------------------------------
void homeCentreBeam() {
  // read the state of the limitswitch:
  while (!centreBeamHomeFlag) {
    centreBeamDownMovement(1000000);
  }
}

void homeCbeam() {
  while (!cbeamHomeFlag) {
    cbeamBackMovement(1000000);
  }
}

void homeArm() {
  // read the state of the limitswitch:
  while (!armHomeFlag) {
    armUpMovement(100000);
  }
}

void homeAll() {
  homeArm();
  homeCbeam();
  homeCentreBeam();
}

void resetFlags() {
  centreBeamHomeFlag = false;
  centreBeamLimitFlag = false;
  armHomeFlag = false;
  cbeamHomeFlag = false;
  cbeamLimitFlag = false;
}

//-------------------------- RECEIVER ------------------------------------------
void receive() {
  Serial.println("I am waiting for a message");
  uint8_t data[] = "yep";
  while (nrf24.waitAvailableTimeout(200) && nrf24.recv(buf, &len))
  {
    Serial.println("Something was received");

    for (i; i < sizeof(buf); i++)
    {
      coords[i] = buf[i];
      coords[i] = (char)buf[i];
      Serial.print(coords[i]);
    }

    //STRING SPLIT
    for (int j = 0; j < sizeof(coords); j++) {
      if (j < 1) {
        shelf[j] = coords[j];
        shelf[j] = (char)coords[j];
        shelfNo = atoi(shelf);
      }

      if (j >= 1 && j < 4) {
        xcoord[countX] = coords[j];
        xcoord[countX] = (char)coords[j];
        xCoords = atoi(xcoord);
        countX += 1;
      }

      if (j >= 4 && j < sizeof(coords)) {
        ycoord[countY] = coords[j];
        ycoord[countY] = (char)coords[j];
        yCoords = atoi(ycoord);
        countY += 1;
      }
    }
    Serial.println("SHELF =");
    Serial.println(shelfNo);
    Serial.println("XCOORDs =");
    Serial.println(xCoords);
    Serial.println("YCOORDs =");
    Serial.println(yCoords);
    Serial.println(coords);

    check = true;

    if (check == true) {
      while (i <= 50) {
        delay(1000);
        //sending data back now
        nrf24.send(data, sizeof(data));
        nrf24.waitPacketSent();
        Serial.println("something was sent");
        i++;
      }
    } break; 
  }
}
