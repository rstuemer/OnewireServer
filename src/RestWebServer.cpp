#include "RestWebServer.h"
#include "Domain/Sensor.h"
#include "View/JsonView.h"

RestWebServer::RestWebServer(EthernetServer* server)
{
    // Initialize the Ethernet server library
    // with the IP address and port you want to use
    // (port 80 is default for HTTP):
    this->server =  server;
   
}

void RestWebServer::run(Controller *controller)
{
    // listen for incoming clients
 
    
    EthernetClient client = this->server->available();
    if (client)
    {
        Serial.println("client available");
        Request request = this->waitTillRequestEnded(client);
        //Serial.println("w");
       // Serial.println(request.getFirstPathsegment());
        if (request.getPath() == "/" && request.getHttpMethode() == "GET")
        {
            Vector<Sensor> sensors = controller->listAllSensors();
            JsonView view = JsonView(client);
            view.addToJson(sensors);
            view.render();
            // PATH /sensors/{1}
        }else if(request.getFirstPathsegment() == "search" && request.getHttpMethode() == "GET"){
            Serial.println("Search Sensors");
            controller->searchSensors();
             Vector<Sensor> sensors =  controller->listAllSensors();
              JsonView view = JsonView(client);
            view.addToJson(sensors);
            view.render();
        }else if(request.getFirstPathsegment() == "sensors" && request.getHttpMethode() == "GET"){
            int id = request.getPathSegments()[1];
            Serial.print("ID:");
            Serial.println(id);
            Sensor sensor = controller->getSensorWithValue(id);
            JsonView view = JsonView(client);
            Sensor sensors[1];
            sensors[0]=sensor;
             view.addToJson(sensors);



        }
        else 
        {
            Serial.print("PATH:");
            client << "FirstPathSegment";
            client << request.getFirstPathsegment();
            Serial.println(request.getPath());
            client << request.getPath();
        }

        // give the web browser time to receive the data
        delay(10);
        // close the connection:
        client.stop();
    }
    else
    {
    }
}

Request RestWebServer::waitTillRequestEnded(EthernetClient client)
{
    Request requestObj = Request();

    if (client)
    {
        Serial.println("new client");
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        String line = "";
        String request[10] = {};
        int lineCount = 0;

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
                    line += c;
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }else{
                Serial.println("Cleint not available");
            }
        }

        requestObj.processRequestString(request);
        Serial.println("Request Processed");
    }
    return requestObj;
}

void RestWebServer::startEthernetServer()
{
    // start the server
       Serial.print("SERVER BEGIN: ");

    server->begin();
    Serial.print("SERVER ON AT: ");
    Serial.println(Ethernet.localIP());
   

}

