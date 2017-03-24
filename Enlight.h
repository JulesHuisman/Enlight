/*
  Created by Jules Huisman, March 22, 2017.
  Released into the public domain.
*/

#ifndef Enlight_h
#define Enlight_h

#include "Arduino.h"
#include <WiFiUDP.h>

#define DEBUG //Comment to remove debugging serial prints

#ifdef DEBUG
  #define DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
  #define DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
  #define DEBUG_PRINT(...) {}
  #define DEBUG_PRINTLN(...) {}
#endif

class Enlight
{
  public:
    Enlight();
    void begin(IPAddress enlightIp, const unsigned int enlightPort);
    void setColor(int _group, int color, int fadeTime);
    void setBrightness(int _group, int brightness, int fadeTime);
  private:
    WiFiUDP Udp;
    IPAddress _enlightIp;
    void connect();
    void sendMessage(char command[], int lightId, int value, int fadeTime);
    unsigned int _enlightPort;
};

#endif
