# include "Lights.h"

//declare lights, button, and button state. 

const int hallway = 3;
const int door = 2;
const int onOff = 5;
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
    delay(30000);

    lightOff(door);
    Serial.println("Door light off.");
    delay(30000);

    lightOff(hallway);
    Serial.println("Hall light off.");
    pressed = false;
    delay(1000);
  }
}
