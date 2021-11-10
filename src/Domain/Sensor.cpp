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


double TempSensor::getTemperatur(){
    return this->getValueAsInt();
}

