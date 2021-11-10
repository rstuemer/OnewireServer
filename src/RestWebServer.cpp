#include "RestWebServer.h"
#include <ArduinoJson.h>


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

    StaticJsonDocument<500> doc;

    EthernetClient client = this->server->available();
     if (client)
    {
        Request request = this->waitTillRequestEnded(client);

        this->printJsonHeader(client, measureJsonPretty(doc));
        serializeJson(doc, Serial);
        serializeJsonPretty(doc, client);

        // give the web browser time to receive the data
        delay(10);
        // close the connection:
        client.stop();
        //Serial.print("REQUEST[1]:");
        //Serial.println(request[1]);
      
            Serial.println(request.getPath());
        
        
    }
}

 Request RestWebServer::waitTillRequestEnded(EthernetClient client)
{

    if (client)
    {
        Serial.println("new client");
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        String line = "";
        bool newLine = true;
        String *request = new String[20];
        int lineCount = 0;
        bool firstLine = true;
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
                    newLine = true;

                    request[lineCount++] = line;            
                    firstLine = false;
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
        Request requestObj =  Request();
        requestObj.processRequestString(request);
        return requestObj;
    }
}

void RestWebServer::printJsonHeader(EthernetClient client, size_t size)
{
    // send a standard http response header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type:  application/json");
    client.println("Connection: close"); // the connection will be closed after completion of the response
    client.print(F("Content-Length: "));
    client.println(size);
    //client.println("Refresh: 5");         refresh the page automatically every 5 sec

    client.println();
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