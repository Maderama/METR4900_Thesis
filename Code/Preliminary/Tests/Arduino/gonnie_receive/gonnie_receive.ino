#include <RadioHead.h>
#include <SPI.h>
#include <RH_NRF24.h>
#include <stdio.h>
#include <stdlib.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;

int greenLed = 3;
int redLed = 2;
int button = 4;

uint8_t buf[3];
uint8_t len = sizeof(buf);
char coords[sizeof(buf)];
int i = 0; 
int n; 

void setup()
{
  Serial.begin(9600);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(button, INPUT);

  //while (!Serial)
  ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");
}

void loop()

{
  uint8_t data[] = "yep";
  if (digitalRead(button)) {
    //button is pressed, message should be sent, turn the green LED on
    digitalWrite(greenLed, HIGH);

    // Send a message
    //   int data[1] = {90};
 
    nrf24.send(data, sizeof(data));
    nrf24.waitPacketSent();
    digitalWrite(greenLed, LOW);
  } else {
    // Wait for a message
 // uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
//    uint8_t buf[6];
//    uint8_t len = sizeof(buf);
    Serial.println("I am waiting for a message");
    while (nrf24.waitAvailableTimeout(200) && nrf24.recv(buf, &len))
    {
      //something was received, turn the right LED on
      Serial.println("Something was received");
      for (i; i < sizeof(buf); i++)
      {
        coords[i] = buf[i];
        coords[i] = (char)buf[i];
      }
      Serial.println(coords);
      digitalWrite(redLed, HIGH);
    }
    digitalWrite(redLed, LOW);
  }
}
