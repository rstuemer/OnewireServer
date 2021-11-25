

/*
 * To use this demo,  enter one of the following USLs into your browser.
 * Replace "host" with the IP address assigned to the Arduino.
 *
 * http://host/
 * http://host/json
 *
 * This URL brings up a display of the values READ on digital pins 0-9
 * and analog pins 0-5.  This is done with a call to defaultCmd.
 * 
 * 
 * http://host/form
 *
 * This URL also brings up a display of the values READ on digital pins 0-9
 * and analog pins 0-5.  But it's done as a form,  by the "formCmd" function,
 * and the digital pins are shown as radio buttons you can change.
 * When you click the "Submit" button,  it does a POST that sets the
 * digital pins,  re-reads them,  and re-displays the form.
 * 
 */

#include "SPI.h"
#include "Ethernet.h"
#include "config.h"
#include "helper.h"
#include "Domain/Sensor.h"
#include "RestWebServer.h"
#include "Controller.h"



RestWebServer* server;
 Controller* controller;


// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer ethernetServer(80);



// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
// CHANGE THIS TO YOUR OWN UNIQUE VALUE
static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// CHANGE THIS TO MATCH YOUR HOST NETWORK
static uint8_t ip[] = { 192, 168, 178, 55 };




 /**
  * @brief 
  * Init RestServer
  * Search for OneWire Sensors
  * 
  */
void setup()
{
  Serial.begin(9600);
  #ifdef SERIAL_DEBUGGING
    Serial.println("Starting");
  #endif




     server = new RestWebServer(&ethernetServer);
       Serial.println("RestServer Initialiezed");
     // server->initEthernet();

   controller = new Controller();
  Serial.println("Controller Initialiezed");

  Ethernet.begin(mac, ip);
      Serial.println("Ethernet.begin Initialiezed");

  ethernetServer.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

   //Serial.println(server->initEthernet());
    //server->startEthernetServer();
    //Serial.println("Start search sensors");
    //controller->searchSensors();
    Serial.println("Startup done.");

       

}

void loop()
{
    
  server->run(controller);
  
}
   