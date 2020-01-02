#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "secrets.h"

#include <Wire.h>

// I2C pin numbers on the wemos d1 mini
#define D1 5
#define D2 4
#define SCL_PIN D1
#define SDA_PIN D2

const int16_t I2C_SLAVE_ADDRESS = 0x08; // must match address refered to by CiClyde

void setup() {
  Serial.begin(115200);
  
  Wire.begin(SDA_PIN, SCL_PIN, I2C_SLAVE_ADDRESS);
  Wire.onRequest(checkBamboo);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wifipw);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void checkBamboo() {
  boolean isActive = false;
  boolean wasSuccessful = true;
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
    if (http.begin(client, plan_url)) {
      http.setAuthorization(bamboo_user, bamboo_pw);
      http.addHeader("Accept", "application/json");

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          wasSuccessful = true; // TODO: parse payload response json
          isActive = false; // TODO: parse payload response json
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
      wasSuccessful = false; // TODO: send separate error information, instead of overloading build status
      isActive = true;
    }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  Wire.write(wasSuccessful); // first byte
  Wire.write(isActive); // second byte
}

void loop() {
  delay(50);
}
