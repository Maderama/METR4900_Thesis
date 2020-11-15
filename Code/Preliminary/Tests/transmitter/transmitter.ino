#include <RadioHead.h>
#include <SPI.h>
#include <RH_NRF24.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24(2,15);

int button = 4;
int buttonState = 0; 

uint8_t buf[3];
uint8_t len = sizeof(buf);
char confirm[sizeof(buf)];
uint8_t fin[sizeof(buf)];
int i = 0;
int n;
bool check;


void setup() {
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

 
void loop() {
  buttonState = digitalRead(button); 
  Serial.println(buttonState);
  uint8_t data[] = "180";
  if (buttonState == HIGH) { 
    nrf24.send(data, sizeof(data));
    nrf24.waitPacketSent();
    Serial.println("I am sending a message");
     

  } else {
    // Wait for a message
    Serial.println("I am waiting for a message");
    while (nrf24.waitAvailableTimeout(200) && nrf24.recv(buf, &len)) {
      //something was received
      Serial.println("Something was received");
      for (i; i < sizeof(buf); i++) {
        confirm[i] = buf[i];
        confirm[i] = (char)buf[i];

        n = atoi(confirm);
      }

      Serial.println(confirm);
      if (sizeof(confirm) == 3) {
        Serial.println("here!");
        check = true;
        break;
      }
    }
  }
}
