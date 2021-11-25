
#ifndef RESTWEBSERVER_H // include guard
#define RESTWEBSERVER_H
/*
  Web Server

 A simple rest web server 
 using an Arduino Wiznet Ethernet shield.
 */
#include <SPI.h>
#include <Ethernet.h>
#include "config.h"
#include "helper.h"
#include "Controller.h"
#include "Request.h"

class RestWebServer{
    public:
        RestWebServer(EthernetServer* server);
        String initEthernet();
        void startEthernetServer();
        void run(Controller* controller);
        Request waitTillRequestEnded(EthernetClient client);
        void printResponseHeader(EthernetClient client,size_t size,String content_typ);
    private:
       EthernetServer* server;
        void printJsonHeader(EthernetClient client,size_t size);
          
};


#endif