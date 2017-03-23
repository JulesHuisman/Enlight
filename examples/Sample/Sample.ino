#include <ESP8266WiFi.h>
#include <OSCMessage.h>
#include <Enlight.h>

Enlight enlight;

char ssid[] = "...";
char pass[] = "...";

const IPAddress enlightIp(192,168,1,102);
const unsigned int enlightPort = 12000;


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  enlight.begin(enlightIp,enlightPort);
}

void loop() {
  //enlight.setColor(0,20);
  //enlight.setBrightness(0,20);
}
