
#ifndef DEVICE_H // include guard
#define DEVICE_H
#include "Arduino.h"
#include "DallasTemperature.h"


class Device{
    public:
        Device();
        Device(OneWire* onewire);
        Device(OneWire* onewire,const uint8_t * address);
        void setDeviceAddress(const uint8_t *address);
         uint8_t* getDeviceAddress();
        bool checkCrC();
        int getId();
        void setId(int id);
        bool startConversion();
    private:
        OneWire* onewire;
        DeviceAddress deviceAddress;
        int id;
};

#endif
