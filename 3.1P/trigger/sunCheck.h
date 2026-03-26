#ifndef SUNCHECK_H
#define SUNCHECK_H

bool checkSun(float lux);
void reportSun(bool sunOn, WiFiClient &client, char* host, String pathOn, String pathOff);

#endif