#include <RadioHead.h>
#include <SPI.h>
#include <RH_nRF24.h>
#include <stdio.h>
#include <stdlib.h>


// Singleton instance of the radio driver
RH_NRF24 nrf24;

//uint8_t buf[7];
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

void setup()
{
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
}

void loop() {
  Serial.println("I am waiting for a message");
  uint8_t data[] = "yep";
  while (nrf24.waitAvailableTimeout(200) && nrf24.recv(buf, &len))
  {
    //something was received, turn the right LED on
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
     
//    Serial.println(yCoords); 

    Serial.println(coords);
    check = true;

    if (check == true) {
      while (i <= 50) {
        //delay(1000);
        delay(1000);
        //sending data back now
        nrf24.send(data, sizeof(data));
        nrf24.waitPacketSent();
        Serial.println("something was sent");
        i++;
      }
    }
  }
}
