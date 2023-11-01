#include <Arduino.h>

void setup() {
  // Status LED
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, HIGH); // Default to unilluminated

  Serial.begin(115200);
}

void loop() {
  
  Serial.println("Hello");

  // Flash LED for status update
  const unsigned long flashPeriod   =  100; 
  const unsigned long overallPeriod = 1000; // Overall period between messages
  digitalWrite(PC13, LOW); // LED is lit when LOW
  delay(flashPeriod);
  digitalWrite(PC13, HIGH);
  delay(overallPeriod - flashPeriod);
}