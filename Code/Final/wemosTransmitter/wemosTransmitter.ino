//web connect
#include <ESP8266WiFi.h>
#include <SPI.h>            // For SPI comm (needed for not getting compile error)
#include <Wire.h>
WiFiClient client;

//transmitter
#include <RadioHead.h>
#include <SPI.h>
#include <RH_NRF24.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------- TURNTABLE -------------------------
#define turnDIR 14 //(D5)
#define turnSTEP 12 //(D6)

#define turntableHomeSwitch 4

bool turntableHomeFlag = false;

float stepsPerDegree = 111.11;



//-----------------------------------------------------------
// Singleton instance of the radio driver
RH_NRF24 nrf24(2, 15);

int button = 4;
int buttonState = 0;

uint8_t buf[7];
uint8_t coords[7];
uint8_t len = sizeof(buf);
char confirm[sizeof(buf)];
uint8_t fin[sizeof(buf)];
int n;
bool check = false;
String message;

uint8_t data[sizeof(coords)];
int sendCount = 0;

String stayString = "\nWAITING";

char shelf[sizeof(buf)];
char xcoord[sizeof(buf)];
char ycoord[sizeof(buf)];

int countX = 0;
int countY = 0;

int shelfNo;
int xCoords;
int yCoords;


//--------------SSID of your Wi-Fi router && Password of your Wi-Fi router------------------------------
//const char* ssid = "Telstra1751";
//const char* password = "0819721227";
//const IPAddress server(192, 168, 15, 2);
//const int httpPort = 5000;

const char* ssid = "Madison's iPhone";
const char* password = "Madison1997";
const IPAddress server(172, 20, 10, 8);
const int httpPort = 5000;


//------------------------------------------------------------------------------------------------------
void setup() {
  pinMode(turnDIR, OUTPUT);
  pinMode(turnSTEP, OUTPUT);

  webConnectSetup();
  transmitSetup();
}

void loop() {
  delay(1000);
  sendGET();
  transmitLoop();
  //  if (!message.equals(stayString)) {
  //    int rotationSteps = atan(yCoords/xCoords)*stepsPerDegree;
  //    homeTurntable();
  //    turntableHomeFlag = false;
  //
  //    turntableClockwiseMovement(rotationSteps);
//}
}

void sendGET() //client function to send/receive GET request data.
{
  if (client.connect(server, httpPort)) {
    Serial.println("Client Connected");
    client.println("GET /coords HTTP/1.1"); //download text
    client.println("Host: 192.168.15.2");
    client.println("Connection: close");  //close 1.1 persistent connection
    client.println(); //end of get request
  } else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }

  while (client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    String line = client.readString();
    int contentBodyIndex = line.lastIndexOf('\n');
    if (contentBodyIndex > 0) {
      message = line.substring(contentBodyIndex);
      Serial.println("MESSAGE EQUALS =" + message);
      Serial.println(stayString);

      if (message.equals(stayString)) {
        Serial.println("EQUAL");
      } else {
        Serial.println("NOT EQUAL");
      }
      int messageIndex = 1;

      for (int i = 0; i < message.length() - 1; i++) {
        coords[i] = message.charAt(messageIndex);
        Serial.println();
        Serial.println(coords[i]);
        messageIndex += 1;
      }
      client.stop();
      client.flush();
    }
    
    shelfNo = 0; 
    countX = 0;
    countY = 0; 

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
  } 
  Serial.println(); 
  Serial.println(shelfNo); 
  Serial.println(xCoords); 
  Serial.println(yCoords); 
}

void webConnectSetup() {
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void transmitSetup() {
  Serial.begin(9600);
  pinMode(button, INPUT);

  if (!nrf24.init()) {
    Serial.println("init failed");
    // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  }
  if (!nrf24.setChannel(1)) {
    Serial.println("setChannel failed");
  }
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)) {
    Serial.println("setRF failed");
  }
  Serial.println("I made it out of setup");
}

void transmitLoop() {
//  if (!message.equals(stayString) && !check && sendCount < 5 && digitalRead(button)){
if (digitalRead(button) && !check && sendCount < 5){
    nrf24.send(coords, sizeof(coords));
    nrf24.waitPacketSent();
    Serial.println("I am sending a message");
    sendCount += 1;
    return;
  } else {
    // Wait for a message
    Serial.println("I am waiting for a message");
    while (nrf24.waitAvailableTimeout(200) && nrf24.recv(buf, &len)) {
      //something was received
      Serial.println("Something was received");
      for (int i = 0; i < sizeof(buf); i++) {
        confirm[i] = buf[i];
        confirm[i] = (char)buf[i];

        n = atoi(confirm);
      }

      Serial.println(confirm);
      if (sizeof(confirm) == 7) {
        Serial.println("Acknowledgement Message Confirmed!");
        check = true;
        break;
      }
    }
  }
}

void homeTurntable() {
  // read the state of the limitswitch:
  while (!turntableHomeFlag) {
    turntableClockwiseMovement(1000000);
  }
}

void turntableCounterClockwiseMovement(float turnSteps) {
  // Set the spinning direction clockwise:
  digitalWrite(turnDIR, LOW);

  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < (turnSteps); i++) {
    if (!digitalRead(turntableHomeSwitch) && !turntableHomeFlag) {
      digitalWrite(turnSTEP, HIGH);
      delayMicroseconds(200000);
      digitalWrite(turnSTEP, LOW);
      delayMicroseconds(200000);
    } else {
      turntableHomeFlag = true;
      break;
    }
  }
  delay(1000);
}

void turntableClockwiseMovement(float turnSteps) {
  // Set the spinning direction clockwise:
  digitalWrite(turnDIR, HIGH);

  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < (turnSteps); i++) {
    digitalWrite(turnSTEP, HIGH);
    delayMicroseconds(200000);
    digitalWrite(turnSTEP, LOW);
    delayMicroseconds(200000);
  }
  delay(1000);
}
