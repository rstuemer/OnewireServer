
#include "View/JsonView.h"



JsonView::JsonView(EthernetClient& client){
    this->client = client;
}


void JsonView::render(){
       



        this->printJsonHeader(client,0);
        serializeJson(doc, Serial);
        serializeJsonPretty(doc, client);
}

void JsonView::printJsonHeader(EthernetClient& client, size_t size)
{

    this->printResponseHeader(client,size,"application/json");
    //client.println("Refresh: 5");         refresh the page automatically every 5 sec

    client.println();
}

void JsonView::printResponseHeader(EthernetClient& client, size_t size,String content_typ)
{
    // send a standard http response header
    Serial.println("Print HEader");
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: "+content_typ);
    client.println("Connection: close"); // the connection will be closed after completion of the response
    if(size > 0){
        client.print(F("Content-Length: "));
        client.println(size);
    }
    //client.println("Refresh: 5");         refresh the page automatically every 5 sec

    //client.println();
}


void JsonView::addToJson(Sensor * sensors){
    JsonObject obj = doc.to<JsonObject>();
    size_t size = sizeof(sensors);

    Serial.println("Add new Sensor:");
    Serial.print(size);
    for (size_t i = 0; i < size; i++)
    {
       JsonObject newSensorJson = obj.createNestedObject(String(i));
        Sensor s = sensors[i];
        newSensorJson["address"] = s.getAddress();
        newSensorJson["family"] = s.getFamilyCode();
        newSensorJson["value"] = s.getValue();
    }

        Serial.println("READY Add new Sensor");

}
