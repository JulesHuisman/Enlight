/*
  Library for controller the milight lights with an esp8266
  Created by Jules Huisman, March 19, 2017.
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
    void setColor(int lightId, int color);
    void setBrightness(int lightId, int brightness);
  private:
    WiFiUDP Udp;
    IPAddress _enlightIp;
    void connect();
    void sendMessage(String command, int lightId, int value);
    unsigned int _enlightPort;
};

#endif
