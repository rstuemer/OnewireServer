#ifndef __HELPER_H__
#define __HELPER_H__
#include "Arduino.h"

class Helper{
    public:
  
     // Returns true if all bytes of array are '\0'

    static bool isAllZeros(const uint8_t * const array, const size_t length) {
            for (size_t i = 0; i < length; i++) {
                if (array[i] != 0) {
                    return false;
                }
            }

            return true;
    }
};



#endif // __HELPER_H__