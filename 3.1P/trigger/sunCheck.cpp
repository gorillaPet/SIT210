#include "sunCheck.h"
#include <Arduino.h>
#include <WiFiNINA.h>
//#include wifi library

/*

Check Sun
Takes the light reading and determines whether the light 
is On or Off the terrarium.

*/

bool checkSun(float lux){

    bool sunOn;

    if (lux < 60){
    sunOn = false;

  } else {

    sunOn = true;

  }
    return sunOn;  
}

/*

Report Sun
Checks current sun state after change detected
and reports whether light is now on or off.

*/

void reportSun(bool sunOn, char* host, String pathOn, String pathOff){

    // fresh connection

  WiFiClient client; 
    
  if (!client.connect(host, 80)) {
    Serial.println("Connection failed.");
    return;
  }

  if(!sunOn){

    //light off email:
    client.println("GET " + pathOff + " HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Connection: close");
    client.println();
 
    Serial.println("Sunlight has moved off ");

  
    
  }else{

    //light on email:
    client.println("GET " + pathOn + " HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Connection: close");
    client.println();

    Serial.println("Sunlight is on terrarium ");

    

  }
  delay(500); //give a little buffer time
  client.stop(); 
}