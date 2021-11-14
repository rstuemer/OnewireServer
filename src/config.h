
#include <Arduino.h>

#ifndef CONFIG_H // include guard
#define CONFIG_H

#ifndef ONE_WIRE_BUS
#define ONE_WIRE_BUS 14
#endif
// add "#define SERIAL_DEBUGGING 1" to your application
// before including to have incoming requests logged to
// the serial port.
#ifndef SERIAL_DEBUGGING
#define SERIAL_DEBUGGING 1
#endif

// declare a static string
#ifdef __AVR__
#define P(name)   static const unsigned char name[] __attribute__(( section(".progmem." #name) ))
#else
#define P(name)   static const unsigned char name[]
#endif



#ifndef SERVER_PORT
#define SERVER_PORT 80
#endif

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
// CHANGE THIS TO YOUR OWN UNIQUE VALUE
static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// CHANGE THIS TO MATCH YOUR HOST NETWORK
static uint8_t ip[] = { 192, 168, 178, 77 };



#define PREFIX ""

#endif