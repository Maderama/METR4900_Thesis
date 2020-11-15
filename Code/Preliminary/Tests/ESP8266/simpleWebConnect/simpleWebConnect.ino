#include <ESP8266WiFi.h>
#include <SPI.h>            // For SPI comm (needed for not getting compile error)
#include <Wire.h>
WiFiClient client;

//--------------SSID of your Wi-Fi router && Password of your Wi-Fi router------------------------------
const char* ssid = "Telstra1751";
const char* password = "0819721227";
const IPAddress server(192, 168, 15, 3);
const int httpPort = 5000;

//const char* ssid = "Madison's iPhone";
//const char* password = "Madison1997";
//const IPAddress server(172, 20, 10, 8);
//const int httpPort = 5000;


//------------------------------------------------------------------------------------------------------

void sendGET() //client function to send/receive GET request data.
{
  if (client.connect(server, httpPort)) {
    Serial.println("Client Connected");
    Serial.println("stuckhere");

    client.println("GET / HTTP/1.1"); //download text
    client.println("Host: 192.168.15.3");
//        client.println("Host: 172.20.10.8");
    client.println("Connection: close");  //close 1.1 persistent connection
    client.println(); //end of get request
  } else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }

  while (client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    String line = client.readString();
    //Serial.println(line);
    int contentBodyIndex = line.lastIndexOf('\n');
    if (contentBodyIndex > 0) {
      Serial.print(line.substring(contentBodyIndex));
    }
    client.stop();
    client.flush();
  }
}

void setup() {
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

void loop() {
  //result = "";
  delay(5000);
  sendGET();
}
