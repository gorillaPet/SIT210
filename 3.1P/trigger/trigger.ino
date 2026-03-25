#include <BH1750.h>
#include "sunCheck.h"
#include <Wire.h>

BH1750 lightMeter;


bool sunOn;
bool newSunOn;

void setup() {

  Serial.begin(115200);
  while(!Serial);

  Wire.begin();
  delay(200); 

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
        reportSun(newSunOn);
        sunOn = newSunOn;
    }
    delay(1000);
}

