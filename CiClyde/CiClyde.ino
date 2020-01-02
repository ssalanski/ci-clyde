#include <Wire.h>
#include <EEPROM.h>
#include <Clyde.h>
#include <SoftwareSerial.h>
#include <MPR121.h>

#define FIRMWARE_VERSION 1

#define COLOR_SUCCESS RGB(32,230,150)
#define COLOR_FAIL    RGB(255,32,0)

void updateColor(boolean buildSuccess) {
  if(buildSuccess) {
    Clyde.fadeAmbient(COLOR_SUCCESS, 0.5f);
  } else {
    Clyde.fadeAmbient(COLOR_FAIL, 0.5f);
  }
}

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

