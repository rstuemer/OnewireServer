#include "Arduino.h"
#include "Controller.h"

/**
*@brief Return all Sensors as json
*
*
*/

Controller::Controller() {
    oneWire = OneWire(ONE_WIRE_BUS);
    dallasSensors = DallasTemperature(&oneWire);
    dallasSensors.begin();

      // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(dallasSensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

}

Sensor* Controller::listAllSensors() {
  
 // OneWire ow(ONE_WIRE_BUS);
  uint8_t count = 0;
  uint8_t dummy_address[8];
  // dummy_address[0] = 0xA0; // TLSB --> 10 degC as std
  // dummy_address[1] = 0x00; // TMSB
  // dummy_address[2] = 0x4B; // THRE --> Trigger register TH
  // dummy_address[3] = 0x46; // TLRE --> TLow
  // dummy_address[4] = 0x7F; // Conf
  // // = 0 R1 R0 1 1 1 1 1 --> R=0 9bit .... R=3 12bit
  // dummy_address[5] = 0xFF; // 0xFF
  // dummy_address[6] = 0x00; // Reset
  // dummy_address[7] = 0x10; // 0x10

  // Sensor dummy_sensor = Sensor(dummy_address);
  // dummy_sensor.setValue("21");
  // dummy_sensor.setFamilyCode(28);
  // sensors[count++] = dummy_sensor;
  uint8_t address[8];
  byte type_s;



  
  if (oneWire.search(address)) {
        do {

          Sensor* sensor;
          // the first ROM byte indicates which chip
      switch (address[0]) {
        case 0x10:
          Serial.println("  Chip = DS18S20");  // or old DS1820
          type_s = 1;
          break;
        case 0x28:
          Serial.println("  Chip = DS18B20");
           sensor =  new TempSensor();
          sensor->setFamilyCode(28);
          ((TempSensor*)sensor)->setTemperatur(dallasSensors.getTempC(address));
          sensors[count++]=sensor;
          type_s = 0;
          break;
        case 0x22:
          Serial.println("  Chip = DS1822");
          type_s = 0;
          break;
        default:
          Serial.println("Device is not a DS18x20 family device.");
          break;
      } 
      if(address[0] == 28){
        Serial.println("IS DS18B20");
          float tempC = dallasSensors.getTempC(address);
          //sensor.setValue(String(tempC));
      }else{
        Serial.print("FamilyCode");
        Serial.println(address[0],HEX);
      }
      
     
      //sensors[count] = sensor;
      //count++;

    } while (oneWire.search(address));

    Serial.print("Sensors found:");
    Serial.println(count);
  }else{
    Serial.println("Nothing found");
  }

  return sensors;
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
/*
void outputPins()
{
    //P(htmlHead) =
        "<html>"
        "<head>"
        "<title>Arduino Web Server</title>"
        "<style type=\"text/css\">"
        "BODY { font-family: sans-serif }"
        "H1 { font-size: 14pt; text-decoration: underline }"
        "P  { font-size: 10pt; }"
        "</style>"
        "</head>"
        "<body>";

    int i;
    //server.httpSuccess();
    //server.printP(htmlHead);

  //  if (addControls)
  //      server << "<form action='" PREFIX "/form' method='post'>";

 //   server << "<h1>Digital Pins</h1><p>";

    for (i = 0; i <= 9; ++i)
    {
        // ignore the pins we use to talk to the Ethernet chip
        int val = digitalRead(i);
    //    server << "Digital " << i << ": ";
    //    if (addControls)
    //    {
            char pinName[4];
            pinName[0] = 'd';
            itoa(i, pinName + 1, 10);
            server.radioButton(pinName, "1", "On", val);
            server << " ";
            server.radioButton(pinName, "0", "Off", !val);
      //  }
       // else
         //   server << (val ? "HIGH" : "LOW");

        server << "<br/>";
    }

    //server << "</p><h1>Analog Pins</h1><p>";
    for (i = 0; i <= 5; ++i)
    {
        int val = analogRead(i);
        server << "Analog " << i << ": " << val << "<br/>";
    }

    server << "</p>";

    if (addControls)
        server << "<input type='submit' value='Submit'/></form>";

    server << "</body></html>";
}
*/
