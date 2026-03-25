#include "sunCheck.h"
#include <Arduino.h>
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

void reportSun(bool sunOn){

  if(!sunOn){
    //add IFTTT logic
    Serial.println("Sunlight has moved off ");
    
  }else{
    //add IFTTT logic
    Serial.println("Sunlight is on terrarium ");
}
    
}