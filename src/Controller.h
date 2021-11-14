#ifndef CONTROLLER_H // include guard
#define CONTROLLER_H

#include "helper.h"
#include "config.h"
#include "Ethernet.h"
#include "ArduinoJson.h"
#include "Domain/Sensor.h"
#include <OneWire.h>
#include "DallasTemperature.h"
class Controller
{
public:
    Controller();
          // Setup a oneWire instance to communicate with any OneWire devices (not just
  // Maxim/Dallas temperature ICs)
    OneWire oneWire;
    // Pass our oneWire reference to Dallas Temperature.
    DallasTemperature dallasSensors;
    Sensor* listAllSensors();
    void debugInformations();

private:
    String getLinkStatus();
    Sensor* sensors[50];
};

#endif