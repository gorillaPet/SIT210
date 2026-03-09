#include "Lights.h"

void lightOn(int light)
{
  digitalWrite(light, HIGH);
}

void lightOff(int light)
{
  digitalWrite(light, LOW);
}
