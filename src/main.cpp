/* Web_Demo.pde -- sample code for Webduino server library */

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
#include "Controller.h"
#include "RestWebServer.h"

RestWebServer* server;
 Controller* controller;
void setup()
{
  Serial.begin(9600);
  #ifdef SERIAL_DEBUGGING
    Serial.println("Starting");
  #endif

   server = new RestWebServer();
   controller = new Controller();
    server->initEthernet();
    server->startEthernetServer();
   
}

void loop()
{
  server->run(controller);
  
}