#ifndef CONTROLLER_H // include guard
#define CONTROLLER_H

#include "helper.h"
#include "config.h"
#include "Vector.h"

#include "ArduinoJson.h"
#include "OneWire/OneWireBus.h"
#include "Domain/Sensor.h"

class Controller
{
public:
    Controller();
     Controller(OneWire onewire);
          // Setup a oneWire instance to communicate with any OneWire devices (not just
  // Maxim/Dallas temperature ICs)
    OneWire oneWire;
    OneWireBus oneWireBus;

    Vector<Sensor> listAllSensors();
    void searchSensors();
    Sensor getSensor(int id);
    Sensor getSensorWithValue(int id);
private:

    Sensor storage[MAX_SENSORS];

    Vector<Sensor> vector;

};

#endif