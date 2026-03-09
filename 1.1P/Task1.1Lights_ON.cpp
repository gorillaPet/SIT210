# include "Lights.h"

//declare lights, button, and button state. 

const int hallway = 5;
const int door = 12;
const int onOff = 13;
bool pressed = false;

void setup()
{
  pinMode(onOff, INPUT_PULLUP);
  pinMode(door, OUTPUT);
  pinMode(hallway, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(onOff) == LOW)
  {
    Serial.println("Lights on.");
    pressed = true;
  }

  if (pressed)
  {
    lightOn(door);
    lightOn(hallway);
    delay(10000);

    lightOff(door);
    Serial.println("Door light off.");
    delay(20000);

    lightOff(hallway);
    Serial.println("Hall light off.");
    pressed = false;
    delay(1000);
  }
}
