#ifndef CONTROLLER_H // include guard
#define CONTROLLER_H

#include "helper.h"
#include "config.h"
#include "Ethernet.h"
#include "ArduinoJson.h"
#include "Domain/Sensor.h"
class Controller
{
public:
    Controller();
    Sensor* listAllSensors();
    void debugInformations();

private:
    String getLinkStatus();
};

#endif