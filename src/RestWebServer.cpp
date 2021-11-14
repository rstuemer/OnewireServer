#include "RestWebServer.h"
#include "Domain/Sensor.h"
#include "View/JsonView.h"

RestWebServer::RestWebServer()
{
    // Initialize the Ethernet server library
    // with the IP address and port you want to use
    // (port 80 is default for HTTP):
    this->server = new EthernetServer(SERVER_PORT);
}

void RestWebServer::run(Controller *controller)
{
    // listen for incoming clients

  

    EthernetClient client = this->server->available();
     if (client)
    {
        Request request = this->waitTillRequestEnded(client);
        Serial.println("Request Ended");
        if(request.getPath() == "/" && request.getHttpMethode() =="GET"){
            Serial.println("Path is /");
         Sensor* sensors = controller->listAllSensors();
         Serial.println("Create JsonView");
         JsonView view = JsonView(client);
                 Serial.println("1");

         view.addToJson(sensors);
         Serial.println("Render");
         view.render();
        }else{
            Serial.print("PATH:");
            Serial.println(request.getPath());
            client << request.getPath();
        }

  
        // give the web browser time to receive the data
        delay(10);
        // close the connection:
        client.stop();
        
    }else{
         
         
    }
}

 Request RestWebServer::waitTillRequestEnded(EthernetClient client)
{
      Request requestObj =  Request();

    if (client)
    {
        Serial.println("new client");
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        String line = "";
        String request[10] =  {};
        int lineCount=0;
      
        while (client.connected())
        {

            if (client.available())
            {
                char c = client.read();
                //Serial.write(c);

                // if you've gotten to the end of the line (received a newline
                // character) and the line is blank, the http request has ended,
                // so you can send a reply
                if (c == '\n' && currentLineIsBlank)
                {
                    break;
                }
                if (c == '\n')
                {
                    // you're starting a new line
                    currentLineIsBlank = true;
                    request[lineCount++] = line;            
                    line = "";
                }
                else if (c != '\r')
                {
                    line+= c;
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
      
        requestObj.processRequestString(request);
    }
        return requestObj;
}


void RestWebServer::startEthernetServer()
{
        // start the server
        this->server->begin();
    #ifdef SERIAL_DEBUGGING
        Serial.print("SERVER ON AT: ");
        Serial.println(Ethernet.localIP());
    #endif
}

String RestWebServer::initEthernet()
{
    // You can use Ethernet.init(pin) to configure the CS pin
    //Ethernet.init(10);  // Most Arduino shields
    //Ethernet.init(5);   // MKR ETH shield
    //Ethernet.init(0);   // Teensy 2.0
    //Ethernet.init(20);  // Teensy++ 2.0
    //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
    //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet
    #ifdef SERIAL_DEBUGGING
        Serial.println("Ethernet WebServer Example");
    #endif

        // start the Ethernet connection and the server:
        Ethernet.begin(mac, ip);

        // Check for Ethernet hardware present
        if (Ethernet.hardwareStatus() == EthernetNoHardware)
        {
    #ifdef SERIAL_DEBUGGING
            Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    #endif
            return "Ethernet shield was not found.  Sorry, can't run without hardware. :(";
        }
        if (Ethernet.linkStatus() == LinkOFF)
        {
    #ifdef SERIAL_DEBUGGING
            Serial.println("Ethernet cable is not connected.");
    #endif
        return "Ethernet cable is not connected.";
    }

    return "OK";
}