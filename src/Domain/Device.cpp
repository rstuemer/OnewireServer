#include "Device.h"

Device::Device()
{
}

Device::Device(OneWire * onewire)
{
    onewire = onewire;
}

Device::Device(OneWire * onewire, const uint8_t* address)
{
        onewire = onewire;
        deviceAddress = address;

}
void Device::setDeviceAddress(const uint8_t *address){
    deviceAddress = address;
} 

uint8_t* Device::getDeviceAddress() {
    this->deviceAddress;
}

bool Device::checkCrC()
{
    if (OneWire::crc8(deviceAddress, 7) != deviceAddress[7])
    {
        Serial.println("CRC is not valid!");
        return;
    }
}

int Device::getId(){
    return id;
}

void Device::setId(int newId){
    

    id = newId;
}

bool Device::startConversion(){
  onewire->reset();
  onewire->select(deviceAddress);
  onewire->write(0x44, 1);        // start conversion, with parasite power on at the end
}