
#ifndef DEVICE_H // include guard
#define DEVICE_H
#include "Arduino.h"
#include "DallasTemperature.h"


class Device{
    public:
        Device();
        Device(OneWire*);
        Device(OneWire*,DeviceAddress address);
        
    private:
        void setDeviceAddress(DeviceAddress address);
        DeviceAddress* getDeviceAddress();

};

#endif
