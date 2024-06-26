#include <Arduino.h>

#ifdef ARDUINO_ARCH_STM32
const int LED = PC13;
#else
const int LED = LED_BUILTIN;
#endif

void floatByBytes(float data);

void setup() {
  // Status LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // Default to unilluminated

  Serial.begin(115200);
  
  while (!Serial) delay(100); // Wait for USB to initialize communications
}

void loop() {
  
  /* the order of data going into the vision system:
  
  Airspeed, Altimeter,
  GyroX, GyroY, GyroZ, GyroW, (-1 , 1)
  heading, (0,360)
  GPSX, GPSY, (-180, 180)
  totalEnergy, energyLossRate, efficiency,
  temp, pressure,
  windX, windY, windZ

  Realistically we will make a function for this in the final aircraft
  to hold all these function calls with a bunch of parameters passed in
  for all the system characteristics.
  */
  floatByBytes(32.000); // 32 is 0x4200_0000 in hex, if the byte order is reversed (0x0000_0042) then it will be interpreted as 9.24856986454e-44
  floatByBytes(23.151); // 0x41b9353f, if reversed then 0.709858000278

  floatByBytes((millis()/1000) % 360);

  floatByBytes((random(35999)-18000)/1000.0);
  floatByBytes((random(35999)-18000)/1000.0);

  floatByBytes(567.32);
  floatByBytes(555.50);
  floatByBytes(0.9875);

  floatByBytes(18.74);
  floatByBytes(1020.57);

  floatByBytes(2.7);
  floatByBytes(-6.8);
  floatByBytes(34.93);

  // Flash LED for status update
  const unsigned long flashPeriod   =  100; 
  const unsigned long overallPeriod = 1000; // Overall period between messages
  digitalWrite(LED, LOW); // LED is lit when LOW
  delay(flashPeriod);
  digitalWrite(LED, HIGH);
  delay(overallPeriod - flashPeriod);
}

void floatByBytes(float data) {
  char * dataPointer = (char *) & data;

  //for (int i = 4; i > 0; i--) Serial.write(dataPointer[i-1]); // Most significant byte first
  for (int i = 0; i < 4; i++) Serial.write(dataPointer[i]); // Least significant byte first
}