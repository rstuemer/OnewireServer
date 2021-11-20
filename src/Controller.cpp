#include "Arduino.h"
#include "Controller.h"


/**
*@brief Return all Sensors as json
*
*
*/

Controller::Controller() {


  
    oneWireBus = OneWireBus();
    oneWireBus.searchSensors();
    
    
}



void Controller::searchSensors(){
  
}

Sensor* Controller::listAllSensors() {
  return oneWireBus.getSensors();
}

Sensor Controller::getSensor(int id){
    size_t count = sizeof(sensors);
    Sensor sensor; 
    for (size_t i = 0; i < count; i++)
    {
        if(sensors[i].getId() == id){
          sensor = sensors[i];
        }
    }

    return sensor;
    
}

Sensor Controller::getSensorWithValue(int id){
    Sensor sensor = getSensor(id);
  
    if(sensor.getFamilyCode() == DS18B20MODEL)
      if(oneWireBus.startConversion(&sensor)){
          TempSensor* pB = static_cast<TempSensor*>(&sensor);
             pB->getValue();
      }
       
   
    

    return sensor;
}

void Controller::debugInformations() {

  // server.httpSuccess(false, "application/json");
  // this->server.httpSuccess("application/json");

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without "
                   "hardware. :(");
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("MayBe Ethernet cable is not connected.");
  }
}

String Controller::getLinkStatus() {
  auto link = Ethernet.linkStatus();
  // Serial.print("Link status: ");
  switch (link) {
  case Unknown:
    return "Unknown";
    break;
  case LinkON:
    return "ON";
    break;
  case LinkOFF:
    return "OFF";
    break;
  }

  return "FAIL";
}

