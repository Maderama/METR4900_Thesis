/* 
 *  Get Chip ID
 */

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("");
  Serial.println("");
  Serial.println("Check ID in:");
  Serial.println("https://www.wemos.cc/verify_products");
  Serial.printf("Chip ID = %08Xn", ESP.getChipId());
  Serial.println("");
  Serial.println("");
  delay(5000);
}
