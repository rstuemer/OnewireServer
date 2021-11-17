#include "OneWireBus.h"


OneWireBus::OneWireBus(){
    onewire = OneWire(ONEWIRE_CONFIG);

}
OneWireBus::OneWireBus(OneWire *onewire)
{
    onewire = onewire;
	parasite = false;
	bitResolution = 9;
	waitForConversion = true;
	checkForConversion = true;
    autoSaveScratchPad = true;
    sensors[MAX_SENSORS];
}

bool OneWireBus::readScratchPad(const DeviceAddress* deviceAddress,ScratchPad* scratchPad)
{
    // send the reset command and fail fast
	int b = onewire.reset();
	if (b == 0)
		return false;

	onewire.select(*deviceAddress);
	onewire.write(READSCRATCH);

	// Read all registers in a simple loop
	// byte 0: temperature LSB
	// byte 1: temperature MSB
	// byte 2: high alarm temp
	// byte 3: low alarm temp
	// byte 4: DS18S20: store for crc
	//         DS18B20 & DS1822: configuration register
	// byte 5: internal use & crc
	// byte 6: DS18S20: COUNT_REMAIN
	//         DS18B20 & DS1822: store for crc
	// byte 7: DS18S20: COUNT_PER_C
	//         DS18B20 & DS1822: store for crc
	// byte 8: SCRATCHPAD_CRC
	for (uint8_t i = 0; i < 9; i++) {
		*scratchPad[i] = onewire.read();
	}

	b = onewire.reset();
	return (b == 1);
}

void OneWireBus::writeScratchPad(const DeviceAddress* deviceAddress,const ScratchPad* scratchPad)
{
    onewire.reset();
	onewire.select(*deviceAddress);
	onewire.write(WRITESCRATCH);
	onewire.write(*scratchPad[HIGH_ALARM_TEMP]); // high alarm temp
	onewire.write(*scratchPad[LOW_ALARM_TEMP]); // low alarm temp

	// DS1820 and DS18S20 have no configuration register
	if (*deviceAddress[DSROM_FAMILY] != DS18S20MODEL)
		onewire.write(*scratchPad[CONFIGURATION]);

  if (autoSaveScratchPad)
    saveScratchPad(deviceAddress);
  else
    onewire.reset();
}



// attempt to determine if the device at the given address is connected to the bus
bool OneWireBus::isConnected(const DeviceAddress *deviceAddress)
{

    ScratchPad scratchPad;
    return isConnected(deviceAddress, &scratchPad);
}

// attempt to determine if the device at the given address is connected to the bus
// also allows for updating the read scratchpad
bool OneWireBus::isConnected(const DeviceAddress *deviceAddress,
                             ScratchPad *scratchPad)
{
    bool b = readScratchPad(deviceAddress, scratchPad);
    return b && !Helper::isAllZeros(*scratchPad,SCRATCHPAD_SIZE) && (onewire.crc8(*scratchPad, 8) == *scratchPad[SCRATCHPAD_CRC]);
}


// Sends command to one or more devices to save values from scratchpad to EEPROM
// If optional argument deviceAddress is omitted the command is send to all devices
// Returns true if no errors were encountered, false indicates failure
bool OneWireBus::saveScratchPad(const DeviceAddress* deviceAddress) {
  
  if (onewire.reset() == 0)
    return false;
  
  if (deviceAddress == nullptr)
    onewire.skip();
  else
    onewire.select(*deviceAddress);
  
  onewire.write(COPYSCRATCH,parasite);

  // Specification: NV Write Cycle Time is typically 2ms, max 10ms
  // Waiting 20ms to allow for sensors that take longer in practice
  if (!parasite) {
    delay(20);
  } else {
      //TODO Implement External PullUP
    //activateExternalPullup();
    delay(20);
    //deactivateExternalPullup();
  }
  
  return onewire.reset() == 1;
  
}

bool OneWireBus::isParasiteModeON()
{
    onewire.reset();
    onewire.skip();
    return readParasiteModefromBus();
}

bool OneWireBus::isParasiteModeON(DeviceAddress address)
{
    onewire.reset();
    onewire.select(address);
    return readParasiteModefromBus();
}

bool OneWireBus::readParasiteModefromBus()
{
    bool parasiteMode = false;
    onewire.write(READPOWERSUPPLY);
    if (onewire.read_bit() == 0)
        parasiteMode = true;
    onewire.reset();
    return parasiteMode;
}

bool OneWireBus::startConversion(){
    onewire.reset();
	onewire.skip();
	onewire.write(STARTCONVO, parasite);

	// ASYNC mode?
	if (!waitForConversion)
		return;
	return waitUntilConversionComplete(bitResolution);
}


bool OneWireBus::startConversion(Sensor* sensor){
     onewire.reset();
     onewire.select(sensor->getDeviceAddress());
     onewire.write(STARTCONVO, 1);        // start conversion, with parasite power on at the end

     // ASYNC mode?
	if (!waitForConversion)
		return true;

	return waitUntilConversionComplete(bitResolution);
}

bool OneWireBus::startConversion(DeviceAddress* address){
     onewire.reset();
     onewire.select(*address);
     onewire.write(STARTCONVO, 1);        // start conversion, with parasite power on at the end

     // ASYNC mode?
	if (!waitForConversion)
		return true;

	bool waitUntilConversionComplete(bitResolution);
}

bool OneWireBus::waitUntilConversionComplete(uint8_t bitResolution){
    
  if (checkForConversion && !parasite) {
    unsigned long start = millis();
    while (!isConversionComplete() && (millis() - start < MAX_CONVERSION_TIMEOUT ))
      yield();
  } else {
    unsigned long delms = millisToWaitForConversion(bitResolution);
    //activateExternalPullup();
    delay(delms);
    //deactivateExternalPullup();
  }

}

// returns number of milliseconds to wait till conversion is complete (based on IC datasheet)
int16_t OneWireBus::millisToWaitForConversion(uint8_t bitResolution) {

	switch (bitResolution) {
	case 9:
		return 94;
	case 10:
		return 188;
	case 11:
		return 375;
	default:
		return 750;
	}

}


Sensor* OneWireBus::getSensors(){
    return *sensors;
}

bool OneWireBus::isConversionComplete(){
    uint8_t b = onewire.read_bit();
	return (b == 1);
}



Sensor* OneWireBus::searchSensors()
{
    uint8_t count = 0;
    uint8_t address[8];
    byte type_s;
    if (onewire.search(address))
    {
        do
        {

            Sensor* sensor;
            // the first ROM byte indicates which chip
            switch (address[0])
            {
            case 0x10:
                Serial.println("  Chip = DS18S20"); // or old DS1820
                type_s = 1;
                break;
            case 0x28:
                Serial.println("  Chip = DS18B20");
                sensor = new TempSensor();
                sensor->setFamilyCode(28);
                sensor->setId(count);
                ((TempSensor*)sensor)->readResolution();
                sensors[count++] = sensor;
                type_s = 0;
                break;
            case 0x22:
                Serial.println("  Chip = DS1822");
                type_s = 0;
                break;
            default:
                Serial.println("Device is not a DS18x20 family device.");
                break;
            }

        } while (onewire.search(address));

        Serial.print("Sensors found:");
        Serial.println(count);
    }
    else
    {
        Serial.println("Nothing found");
    }
    return *sensors;
}

bool OneWireBus::crc8(const DeviceAddress *addr, uint8_t len){
    return onewire.crc8(*addr,len);
}

// returns the current resolution of the device, 9-12
// returns 0 if device not found
uint8_t OneWireBus::readResolution(DeviceAddress* deviceAddress) {

	// DS1820 and DS18S20 have no resolution configuration register
	if ( DS18S20MODEL == *deviceAddress[DSROM_FAMILY])
		return 12;

	ScratchPad scratchPad;
	if (this->isConnected(deviceAddress, &scratchPad)) {
		switch (scratchPad[CONFIGURATION]) {
		case TEMP_12_BIT:
			return 12;

		case TEMP_11_BIT:
			return 11;

		case TEMP_10_BIT:
			return 10;

		case TEMP_9_BIT:
			return 9;
		}
	}
	return 0;

}
