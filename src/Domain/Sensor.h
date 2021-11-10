#ifndef SENSOR_H // include guard
#define SENSOR_H
#include "Arduino.h"
#include "DallasTemperature.h"

class Sensor{
  
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
        double getTemperatur();
        int getResolution();
    private:
        int resolution;

};


#endif