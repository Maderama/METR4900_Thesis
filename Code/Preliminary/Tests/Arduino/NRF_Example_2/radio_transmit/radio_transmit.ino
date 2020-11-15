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

void setup()
{
  Serial.begin(9600);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(button, INPUT);
  uint8_t buf[0];

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
  uint8_t data[] = "111111";
  if (digitalRead(button)) {
    //button is pressed, message should be sent, turn the green LED on
    digitalWrite(greenLed, HIGH);

    // Send a message
    Serial.println("I am sending a message");
    nrf24.send(data, sizeof(data));
    nrf24.waitPacketSent();
    digitalWrite(greenLed, LOW);

  } else {
    // Wait for a message
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    Serial.println("I am waiting for a message");

    //    if (sizeof(buf) != 0) {
    while (nrf24.waitAvailableTimeout(200) && nrf24.recv(buf, &len))
    {
      //something was received, turn the right LED on
      Serial.println("Something was received");
      for (int i = 0; i < sizeof(buf); i++)
      {
        Serial.println(buf[i]);
        Serial.write(buf[i]);
        Serial.println();
      }
      digitalWrite(redLed, HIGH);
    }
    digitalWrite(redLed, LOW);
  }
}
