#include <Wire.h>
#include <EEPROM.h>
#include <Clyde.h>
#include <SoftwareSerial.h>
#include <MPR121.h>

#define FIRMWARE_VERSION 1

void setup() {
  Serial.begin(9600);
  Clyde.begin();
  Serial.println("Clyde is Ready!");
}

void loop() {
  //update the lights
  Clyde.updateAmbientLight();
  Clyde.updateWhiteLight();
}

