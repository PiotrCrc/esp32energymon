#include "timeout.h"

#define DEBUG 3

// global varialbles


void setup() {
  // starting serial
  Serial.begin(115200);
  #if DEBUG >= 3 
    Serial.print("Serial started (115200)"); 
  #endif
  
}

void loop() {

}
