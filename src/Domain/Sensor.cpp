#include "Sensor.h"




Sensor::Sensor(){

}
/**
 * @brief Construct a new Sensor:: Sensor object
 * 
 */
Sensor::Sensor(uint8_t address[8]) {
    rawaddress = address;
}

void Sensor::setFamilyCode(uint8_t family){
     this->family = family;
}

String Sensor::getName(){
    return this->name;
}

uint8_t Sensor::getFamilyCode(){
    return family;
}
/**
 * @brief 
 * 
 * @return String 
 */
String Sensor::getValue() { return this->value; }
/**
 * @brief 
 * 
 * @return int 
 */
int Sensor::getValueAsInt() { return this->value.toInt(); }
/**
 * @brief 
 * 
 * @param value 
 */
void Sensor::setValue(String value) { this->value = value; }
void Sensor::setName(String name) { this->name = name; }

String Sensor::getAddress(){
    String addressString;
    for (uint8_t i = 0; i < 8; i++)
      {
       addressString += "0x";
        if (this->rawaddress[i] < 0x10)  addressString +="0";
        Serial.print(this->rawaddress[i],HEX);
        
        addressString +=  this->rawaddress[i];
        if (i < 7) Serial.print(", ");
      }
    return addressString;
}


float TempSensor::getTemperatur(){
    return this->getValueAsInt();
}
void TempSensor::setTemperatur(float newtemp){
     temp=newtemp;
}

TempSensor::TempSensor(){

}

uint8_t TempSensor::readResolution(){
    return resolution;
}
uint8_t TempSensor::getResolution(){
	return resolution;
}

void TempSensor::setResolution(uint8_t newResolution){
	resolution = newResolution;
}


