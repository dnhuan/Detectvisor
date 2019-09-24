#include <SPI.h>
#include "RF24.h"

const int sensorPin = 2;
unsigned int data = 0;

RF24 radio(9,10);

const uint8_t address[] = {"super"};

void triggerAlert(){
  Serial.println("Alert!!");
  data = 1;
  if(!radio.write(&data, sizeof(unsigned int))){
     Serial.println(F("Sending alert failed"));
  }
  data = 0;
}

void setup() {
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(sensorPin), triggerAlert, FALLING);

  // Radio
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(address);
}

void loop() {
      Serial.print("STATUS: ");
  Serial.println(radio.isChipConnected());
  Serial.println(digitalRead(sensorPin));
  radio.stopListening(); //Disable RX
  radio.write(&data, sizeof(unsigned int)); 
  delay(1000);
}
