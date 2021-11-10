#include "Request.h"

Request::Request()
{
}

void Request::processRequestString(String *request)
{

    String firstLine = request[0];
    int indexFirstSpace = firstLine.indexOf(" ");
    this->httpMethode = firstLine.substring(0, indexFirstSpace);
    int indexSecondSpace = firstLine.indexOf(" ", indexFirstSpace);
    this->path = firstLine.substring(indexFirstSpace + 1, indexSecondSpace);
}

String Request::getPath()
{
    return this->path;
}

String Request::getHttpMethode()
{
    return this->httpMethode;
}