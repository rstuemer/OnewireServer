#ifndef __ONEWIREBUS_H__
#define __ONEWIREBUS_H__
#include "Arduino.h"
#include "OneWire/onewireConfig.h"
#include "OneWire.h"
#include "Domain/Sensor.h"
#include "Utils/Helper.h"
#include "Vector.h"

class OneWireBus{

    public:
        OneWireBus();
        OneWireBus(OneWire* onewire);
                // read device's scratchpad
        bool readScratchPad(const DeviceAddress*,ScratchPad*);

        // write device's scratchpad
        void writeScratchPad(const DeviceAddress*,const ScratchPad*);

        bool saveScratchPad(const DeviceAddress*);
        /**
         * @brief Check if device is connect to bus
         * 
         * @param deviceAddress 
         * @return true 
         * @return false 
         */
        bool isConnected(const DeviceAddress* deviceAddress);
        /**
         * @brief  Check if device is connect to bus
         * 
         * @param deviceAddress 
         * @param scratchPad 
         * @return true 
         * @return false 
         */
        bool isConnected(const DeviceAddress* deviceAddress,ScratchPad* scratchPad) ;

        bool isParasiteModeON();
        bool isParasiteModeON(DeviceAddress address);
        void searchSensors(Vector<Sensor> *sensors);
        bool crc8(const DeviceAddress *addr, uint8_t len);
        bool startConversion();
        bool startConversion(DeviceAddress* address);
         bool startConversion(Sensor* address);
         bool waitUntilConversionComplete(uint8_t);
         uint8_t readResolution(DeviceAddress* deviceAddress);
         bool isConversionComplete();
        
    private:
        OneWire onewire;
   
        bool readParasiteModefromBus();
        // if true save values from scratchpad to EEPROM on every scratchpad write
        bool autoSaveScratchPad;
        	// parasite power on or off
        bool parasite;

        // external pullup
        bool useExternalPullup;
        uint8_t pullupPin;

        // used to determine the delay amount needed to allow for the
        // temperature conversion to take place
        uint8_t bitResolution;

        // used to requestTemperature with or without delay
        bool waitForConversion;

        // used to requestTemperature to dynamically check if a conversion is complete
        bool checkForConversion;
        //Sensor* sensors[MAX_SENSORS];
        int16_t millisToWaitForConversion(uint8_t bitResolution);


};




#endif // __ONEWIREBUS_H__