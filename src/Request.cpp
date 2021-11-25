#include "Request.h"


Request::Request()
{
}

void Request::processRequestString(String request[])
{

    //String firstLine = request[0];
    /* Parse first request line e.g. GET /path HTTP1.1 */
/*     int indexFirstSpace = firstLine.indexOf(" ");
    this->httpMethode = firstLine.substring(0, indexFirstSpace);
    int indexSecondSpace = firstLine.indexOf(" ", indexFirstSpace+1);
    this->path = firstLine.substring(indexFirstSpace , indexSecondSpace); */
    String* splittedRequestLine = splitString(request[0],' '); 
    this->httpMethode = splittedRequestLine[0];
    this->path =  splittedRequestLine[1];
    
    

}

String Request::getPath()
{
    return this->path;
}

String Request::getFirstPathsegment() 
{
    String string = getPath();
    if(string.indexOf("/")==0)
        string = string.substring(1);
        if(string.indexOf("/")==-1)
        return string;
    return splitString(string,'/')[0];
    // getValueAtIndex(this->path,'/',0);
}

String Request::getPathSegments() 
{
    String string = getPath();
    return *splitString(string,'/');
}
String Request::getHttpMethode()
{
    return this->httpMethode;
}