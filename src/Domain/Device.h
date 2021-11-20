
#ifndef DEVICE_H // include guard
#define DEVICE_H
#include "Arduino.h"

#include "OneWire/onewireConfig.h"

class Device{
    public:
        Device();
      
        Device(const uint8_t * address);
        bool setDeviceAddress(const uint8_t *address);
        bool setDeviceAddress(DeviceAddress* address);

         uint8_t* getDeviceAddress();
        bool validAddress();
        int getId();
        void setId(int id);
        bool startConversion();
        bool isConnected();
        bool isConnected(uint8_t* scratchPad);

    protected:
       
        DeviceAddress* deviceAddress;
        int id;
};

#endif
