#include "Arduino.h"
#include "Controller.h"


/**
*@brief Return all Sensors as json
*
*
*/

Controller::Controller() {


  
    oneWireBus = OneWireBus();
    this->vector.setStorage(storage);

    //
    
    
}

Controller::Controller(OneWire oneWire) {


  
    oneWireBus = OneWireBus(&oneWire);
    this->vector.setStorage(storage);

    //
    
    
}



void Controller::searchSensors(){
   oneWireBus.searchSensors( &vector);
}

Vector<Sensor> Controller::listAllSensors() {
  Serial.print("listAllSensors:");
  Serial.println(vector.size());
  return vector;
}

Sensor Controller::getSensor(int id){
    size_t count = vector.size();

    Sensor sensor; 
    for (size_t i = 0; i < count; i++)
    {
        if(vector.at(i).getId() == id){
          sensor = vector.at(i);
        }
    }

    return sensor;
    
}

Sensor Controller::getSensorWithValue(int id){
    Sensor sensor = vector.at(id);
    float celsius, fahrenheit;

    if(sensor.getFamilyCode() == DS18B20MODEL){
      if(oneWireBus.startConversion(&sensor)){
          //TODO move Code to Driver Class

          TempSensor* pB = static_cast<TempSensor*>(&sensor);
             
             oneWireBus.waitUntilConversionComplete(9);
             ScratchPad scratchPad;
             oneWireBus.readScratchPad(pB->getDeviceAddressObject(),&scratchPad);
               // Convert the data to actual temperature
          // because the result is a 16 bit signed integer, it should
          // be stored to an "int16_t" type, which is always 16 bits
          // even when compiled on a 32 bit processor.
          int16_t raw = (scratchPad[1] << 8) | scratchPad[0];
          //Original Code type_s = 1 for old DS18S20
          if (0) {
            raw = raw << 3; // 9 bit resolution default
            if (scratchPad[7] == 0x10) {
              // "count remain" gives full 12 bit resolution
              raw = (raw & 0xFFF0) + 12 - scratchPad[6];
            }
          } else {
            byte cfg = (scratchPad[4] & 0x60);
            // at lower res, the low bits are undefined, so let's zero them
            if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
            else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
            else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
            //// default is 12 bit resolution, 750 ms conversion time
          }
          celsius = (float)raw / 16.0;
  pB->setTemperatur(celsius);pB->getValue();
  //Daten in Sensor Value Speichern ? oder Temp Sensor .getValue() Überladen ? 
  
             //TODO read Temp from Bus ; 
      }
    }else{
      Serial.println("---------------------NO DS");
    }
       
   
    

    return sensor;
}


