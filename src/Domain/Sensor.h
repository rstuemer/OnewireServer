#ifndef SENSOR_H // include guard
#define SENSOR_H
#include "Arduino.h"

#include "Device.h"

class Sensor: public Device {
  
    public:
        Sensor();
        Sensor(uint8_t address[8]);
         String getValue();
        int getValueAsInt();
        uint8_t getFamilyCode();
        String getAddress();
        void setValue(String value);
        void setFamilyCode(uint8_t value);
        void setAddress(uint8_t  raw_address[8]);
    protected:
        
       
    private:
        String value;
        uint8_t family;
        String name;
        uint8_t* rawaddress;
      
};

class TempSensor: public Sensor{
    public:
        TempSensor();
        TempSensor(uint8_t address[8]);
        float getTemperatur();
        void setTemperatur(float temp);
        uint8_t getResolution();
        uint8_t readResolution();
        void setResolution(uint8_t newResolution);
    
    
    private:
        int resolution;
        float temp;

};


#endif