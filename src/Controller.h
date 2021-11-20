#ifndef CONTROLLER_H // include guard
#define CONTROLLER_H

#include "helper.h"
#include "config.h"
#include "Ethernet.h"
#include "ArduinoJson.h"
#include "OneWire/OneWireBus.h"
#include "Domain/Sensor.h"

class Controller
{
public:
    Controller();
          // Setup a oneWire instance to communicate with any OneWire devices (not just
  // Maxim/Dallas temperature ICs)
    OneWire oneWire;
    OneWireBus oneWireBus;

    Sensor* listAllSensors();
    void debugInformations();
    void searchSensors();
    Sensor getSensor(int id);
    Sensor getSensorWithValue(int id);
private:
    String getLinkStatus();
    Sensor sensors[50];
};

#endif