
#ifndef RESTWEBSERVER_H // include guard
#define RESTWEBSERVER_H
/*
  Web Server

 A simple rest web server 
 using an Arduino Wiznet Ethernet shield.
 */
#include <SPI.h>
#include <Ethernet.h>
#include <SPI.h>
#include <Ethernet.h>
#include "config.h"
#include "helper.h"
#include "Controller.h"
#include "Request.h"

class RestWebServer{
    public:
        RestWebServer();
        String initEthernet();
        void startEthernetServer();
        void run(Controller* controller);
        Request waitTillRequestEnded(EthernetClient client);
    private:
        EthernetServer* server;
        void printJsonHeader(EthernetClient client,size_t size);
        /* maximum URL length (GET) is 2048 characters */
            char line[2048]; /* array to store the get-answer, can be less if you know the max. size */
            int getAnswerCount = 0; /* counter for getAnswer array */
            char answerValue[10]; /* array to store the actual value, can be less if you know the max. length */
            int answerValueCount = 0; /* counter for getAnswer array */
};


#endif