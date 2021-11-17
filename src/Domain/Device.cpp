#include "Device.h"
#include "Utils\Helper.h"
#include "OneWire.h"

Device::Device()
{
}


Device::Device( const uint8_t* address)
{
        setDeviceAddress(address);

}

bool Device::setDeviceAddress(DeviceAddress* address){
    //TODO VALIDATE ADDRESS
    deviceAddress = address;
    return true;
}

bool Device::setDeviceAddress(const uint8_t* address){
    for (size_t i = 0; i < 8; i++)
    {
      *deviceAddress[i]=address[i];
    }
   return  validAddress();
} 

uint8_t* Device::getDeviceAddress() {
    return *deviceAddress;
}

bool Device::validAddress()
{
    if (OneWire::crc8(*deviceAddress, DSROM_CRC) != *deviceAddress[DSROM_CRC])
    {
        Serial.println("CRC is not valid!");
        return false;
    }
    return true;
}

int Device::getId(){
    return id;
}

void Device::setId(int newId){
    id = newId;
}





