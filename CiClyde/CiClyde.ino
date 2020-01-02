#include <Wire.h>
#include <EEPROM.h>
#include <Clyde.h>
#include <SoftwareSerial.h>
#include <MPR121.h>

#define FIRMWARE_VERSION 1

#define COLOR_SUCCESS      RGB(32,230,150)
#define COLOR_SUCCESS_DARK RGB(0,192,64)
#define COLOR_FAIL         RGB(255,32,0)
#define COLOR_FAIL_DARK    RGB(128,0,0)

#define PULSE_TRANSITION 0.2f
#define PULSE_DURATION 750

RGB pulseColors[2][2]; // initialized in setup()

// stateful data
boolean wasSuccessful = true;
boolean isActive = false;
boolean darkPulse = false; // track pulse going bright/dark/bright/dark/...

void updateColor() {
  Clyde.fadeAmbient(pulseColors[wasSuccessful][darkPulse], PULSE_TRANSITION);
}

void setup() {
  pulseColors[0][0] = COLOR_FAIL;
  pulseColors[0][1] = COLOR_FAIL_DARK;
  pulseColors[1][0] = COLOR_SUCCESS;
  pulseColors[1][1] = COLOR_SUCCESS_DARK;
  Serial.begin(9600);
  Clyde.begin();
  Serial.println("Clyde is Ready!");
}

unsigned long now, lastPulse = 0;
void loop() {
  if(isActive) {
    now = millis();
    if(now-lastPulse > PULSE_DURATION) {
      darkPulse = !darkPulse;
      lastPulse = now;
      updateColor();
    }
  }

  //update the lights
  Clyde.updateAmbientLight();
  Clyde.updateWhiteLight();
}

