//char coords[7];
uint8_t coords[] = "1234567";
char shelf[sizeof(coords)]; 
char xcoord[sizeof(coords)];
char ycoord[sizeof(coords)]; 
int n; 

void setup() {
}

void loop() {
  for (int j = 0; j < sizeof(coords); j++) {
    if (j < 1) {
      shelf[j] = coords[j]; 
      shelf[j] = (char)coords[j];
      n = atoi(shelf);
    }
    if (j >= 1 && j < 4) {
      xcoord[j] = coords[j];
    }
    if (j >= 4 && j < sizeof(coords)) {
      ycoord[j] = coords[j];
    }
  } Serial.println("SHELF =" + shelf); 
}
