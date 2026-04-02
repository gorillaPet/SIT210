#ifndef SUNCHECK_H
#define SUNCHECK_H

#include <Arduino.h>
#include <WiFiNINA.h>


bool checkSun(float lux);
void reportSun(bool sunOn, char* host, String pathOn, String pathOff);

#endif