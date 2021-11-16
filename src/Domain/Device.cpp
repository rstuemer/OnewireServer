#include "Device.h"

Device::Device()
{
}

Device::Device(OneWire *)
{
}

Device::Device(OneWire *, DeviceAddress address)
{
}
void Device::setDeviceAddress(DeviceAddress *address){
    deviceAddress = address;
} 


DeviceAddress *Device::getDeviceAddress() {
    this->deviceAddress;
}

bool Device::checkCrC()
{
    if (OneWire::crc8(*deviceAddress, 7) != *deviceAddress[7])
    {
        Serial.println("CRC is not valid!");
        return;
    }
}