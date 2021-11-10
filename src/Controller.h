#ifndef CONTROLLER_H // include guard
#define CONTROLLER_H

#include "helper.h"
#include "config.h"
#include "Ethernet.h"
#include "ArduinoJson.h"

class Controller
{
public:
    Controller();
    void listAllSensors();
    void debugInformations();

private:
    String getLinkStatus();
};

#endif