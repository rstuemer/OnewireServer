#ifndef REQUEST_H // include guard
#define REQUEST_H
#include <Arduino.h>
#include "helper.h"

class Request{
    public: 
        Request();
        void  processRequestString(String request[]); 
        String getHttpMethode();
        String getPath();
    private: 
        String httpMethode;
        String path;   
       

};

#endif