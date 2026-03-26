#include <BH1750.h>
#include <Wire.h>
#include <WiFiNINA.h>
#include "sunCheck.h"
#include "secrets.h"

BH1750 lightMeter;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASSWORD;

WiFiClient client;

char HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME_ON =  "/trigger/sunOn/with/key/" + String(SECRET_KEY_IFTTT);
String PATH_NAME_OFF = "/trigger/sunOff/with/key/" + String(SECRET_KEY_IFTTT);;


bool sunOn;
bool newSunOn;

void setup() {

  WiFi.begin(ssid, pass);

  Serial.begin(115200);
  while(!Serial);

  Wire.begin();
  delay(200); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  if (client.connect(HOST_NAME, 80)) {
    if (client.connect(HOST_NAME, 80)){
      Serial.println("Connected to server.");
    } else {
      Serial.println("Connection failed.");
    }

    if (!lightMeter.begin()) {
      Serial.println("BH1750 begin() failed.");
      
  }
    Serial.println(F("BH1750 Test begin"));

    sunOn = checkSun(lightMeter.readLightLevel());
    reportSun(sunOn);

}

void loop() {

    float lux = lightMeter.readLightLevel();
    Serial.print("lux: ");
    Serial.println(lux);

    newSunOn = checkSun(lux);

    if (newSunOn != sunOn) {
        Serial.println("State changed.");
        reportSun(newSunOn, client, HOST_NAME, PATH_NAME_ON, PATH_NAME_OFF);
        sunOn = newSunOn;
    }
    delay(1000);
}

