#include "Arduino.h"
#include "Controller.h"

  /**
 * @brief Return all Sensors as json
 * 
 * 
 */


Controller::Controller(){
    
}



void Controller::listAllSensors()
{
    
    /**
    //server.httpSuccess(false, "application/json");
    //server.httpSuccess("application/json");

    

    int i;
    //server << "{ ";
    for (i = 0; i <= 9; ++i)
    {
        // ignore the pins we use to talk to the Ethernet chip
        //int val = digitalRead(i);
        //server << "\"d" << i << "\": " << val << ", ";
    }

    for (i = 0; i <= 5; ++i)
    {
      //  int val = analogRead(i);
       // server << "\"a" << i << "\": " << val;
       // if (i != 5)
           // server << ", ";
    }

   // server << " }";

   */
}



void Controller::debugInformations()
{

    //server.httpSuccess(false, "application/json");
    //this->server.httpSuccess("application/json");


    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    }
    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println("MayBe Ethernet cable is not connected.");
    }
}

String Controller::getLinkStatus()
{
    auto link = Ethernet.linkStatus();
    //Serial.print("Link status: ");
    switch (link)
    {
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
  


