#include <BH1750.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFiNINA.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

#define DHTPIN 6
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

BH1750 lightMeter;

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
float temp = 0;
float lux = 0;

String myStatus = "";

void setup() {
  Serial.begin(115200);  // Initialize serial
  while (!Serial); //wait

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.0.0") {
  Serial.print("Firmware version: ");
  Serial.println(fv);
  }
    
  ThingSpeak.begin(client);  //Initialize ThingSpeak

  //init DHT
  dht.begin();

  // Initialize the I2C bus 
  Wire.begin();


  if (!lightMeter.begin()) {
      Serial.println("BH1750 begin() failed.");
      
}
  Serial.println(F("BH1750 Test begin"));
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("DHT read failed, skipping update.");
    delay(20000);
    return;
}

  lux = lightMeter.readLightLevel();

  // set the fields with the values
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, lux);


  // create and set the status message 
  myStatus = String("Temp: ") + temp + "C, Lux: " + lux;
  ThingSpeak.setStatus(myStatus);
  

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  

  
  delay(20000); // Wait 20 seconds to update the channel again
}
