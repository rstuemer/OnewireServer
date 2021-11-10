#ifndef HELPER_H // include guard
#define HELPER_H

#include "Arduino.h"



// no-cost stream operator as described at 
// http://sundial.org/arduino/?page_id=119
template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }



 String getValueAtIndex(String data, char separator, int index);

 String* splitString(String data,char separator);


#endif /* HELPER_H */
