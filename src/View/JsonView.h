
#ifndef JSONVIEW_H // include guard
#define JSONVIEW_H
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include "JsonView.h"
#include <ArduinoJson.h>
#include "../Domain/Sensor.h"

class JsonView {
public:
  JsonView(EthernetClient& client);
  void addToJson(Sensor *sensors);
  void render();

private:
  EthernetClient client;
  StaticJsonDocument<500> doc;

  void printResponseHeader(EthernetClient& client, size_t size, String content_typ);
  void printJsonHeader(EthernetClient& client, size_t size);
};

#endif