
#include "helper.h"

String getValueAtIndex(String data, char separator, int index)
{
  Serial.println(data);  
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


String* splitString(String data,char separator){

    size_t maxIndex = data.length()-1;
    static String buffer[10] = {};
    int found = 0;
    int startIndex  = 0;

    for (size_t i = 0; i <= maxIndex; i++)
    {
         if(data.charAt(i)==separator || i==maxIndex){
             buffer[found++] = data.substring(startIndex,i);
            startIndex= i+1;
         }
       
    }
    
    return buffer;
}

