#include "Arduino.h"
#include "Enlight.h"
#include <WiFiUDP.h>
#include <ESP8266WiFi.h>
#include <OSCMessage.h>

Enlight::Enlight()
{

}

void Enlight::begin(IPAddress enlightIp, const unsigned int enlightPort)
{
  _enlightIp   = enlightIp;
  _enlightPort = enlightPort;

  WiFiUDP Udp;

  DEBUG_PRINTLN();
  DEBUG_PRINTLN(F("Connecting to wifi"));
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Udp.begin(64533);

  DEBUG_PRINTLN();
  DEBUG_PRINTLN(F("Listening on: "));
  DEBUG_PRINT(WiFi.localIP());
  DEBUG_PRINT(F(":"));
  DEBUG_PRINT(Udp.localPort());
  DEBUG_PRINTLN();

  this->connect();
}

void Enlight::setColor(int lightId, int color, int fadeTime)
{
  DEBUG_PRINT(F("Set color: "));
  DEBUG_PRINTLN(color);

  int value = map(color,0,100,2200,9000);

  this->sendMessage("setCT", lightId, value, fadeTime);
}

void Enlight::setBrightness(int lightId, int brightness, int fadeTime)
{
  DEBUG_PRINT(F("Set brightness: "));
  DEBUG_PRINTLN(brightness);

  int value = map(brightness,0,100,0,65535);

  this->sendMessage("setDimLevel", lightId, value, fadeTime);
}

void Enlight::sendMessage(char command[], int lightId, int value, int fadeTime) {
  char commandArray[] = "/Enlight/";

  //Add the specific command to the full command array
	strcat(commandArray,command);

  OSCMessage msg(commandArray);
  msg.add(lightId);
  msg.add(2);
  msg.add(value);
  msg.add(fadeTime);
  Udp.beginPacket(_enlightIp, _enlightPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

void Enlight::connect()
{
  DEBUG_PRINTLN(F("Connecting to Enlights"));
    OSCMessage msg("/Enlight/connect");
    Udp.beginPacket(_enlightIp, _enlightPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
}
