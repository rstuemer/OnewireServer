
#ifndef DEVICE_H // include guard
#define DEVICE_H
#include "Arduino.h"
#include "DallasTemperature.h"


class Device{
    public:
        Device();
        Device(OneWire*);
        Device(OneWire*,DeviceAddress address);
        void setDeviceAddress(DeviceAddress *address);
        DeviceAddress* getDeviceAddress();
        bool checkCrC();
    private:
        DeviceAddress* deviceAddress;
};

#endif
