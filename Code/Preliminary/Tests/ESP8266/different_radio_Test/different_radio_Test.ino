#include  <SPI.h> //Include SPI Code Library which can be downloaded below
#include "nRF24L01.h" //Include NRF24L01 Code Library which can be downloaded below
#include "RF24.h" //Inlcude NRF24 Code Library which can be downloaded below
 
int msg[1];
RF24 radio(9,10); // The NRF24L01 Pin CE and Pin CSN
const uint64_t pipe = 0xE8E8F0F0E1LL; //Communication Pip Address
int switchButton = 7; // Push button connected to Arduino pin 7
 
void setup(void){
 Serial.println("here"); 
 Serial.begin(9600); //Start Serial Communication at baud rate 9600
 radio.begin();
 Serial.println("here at begin"); 
 radio.openWritingPipe(pipe);} //Open Communication Pipe
 
void loop(void){
 Serial.println("in loop"); 
 if (digitalRead(switchButton) == HIGH){ // When the push button has been press it will send radio signal to the RX to turn the LED into HIGH
 msg[0] = 111; //Send the 111 to the reciever 
 radio.write(msg, 1);}}
