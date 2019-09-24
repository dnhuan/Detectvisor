#include <SPI.h>
#include "RF24.h"

const int buzzerPin = D15;
unsigned int data = 0;
unsigned long ping;

const uint8_t address[] = {"super"};
RF24 radio(D9,D10);


void alert();
void dead();

void setup() {

  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  
  // Radio
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, address);
  radio.startListening();
  //
  ping = millis();
}

void loop() {
    Serial.print("STATUS: ");
  Serial.println(radio.isChipConnected());
//  Serial.println(radio.isChipConnected());
  if(radio.available()){
      radio.read(&data, sizeof(unsigned int));
    if(data == 1){
      Serial.println("1");
      alert();
    }
    if(data == 0){
      Serial.println("0");
      ping = millis();
    }
  }
  
  if ((unsigned long)(millis() - ping) > 5000){
    Serial.println("timeout");
    dead();
    ping = millis();
  }else{
    Serial.println(millis() - ping);
  }
}

void alert(){
  for(int i = 0; i < 2; i++){
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }
}

void dead(){
  for(int i = 0; i < 10; i++){
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
}
