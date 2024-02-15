/* refrogerationFirmware.ino

    Firmware for Remote Labs Refrigeration Experiment

    Imogen Heard
    21/12/23

## As of V1.0.0: 21/12/23
```
Sketch uses 42130 bytes (16%) of program storage space. Maximum is 253952 bytes.
Global variables use 6650 bytes (81%) of dynamic memory, leaving 1542 bytes for local variables. Maximum is 8192 bytes.
```


4. Version 1.1.0: 14/02/24 
- Added i2c sensor for Atmospheric temp, pressure & humidity
- Improved debugging and unit disabling options
- Devolved functions from .ino to organised tabs
- Increased JSON buffer size to 720 bytes
```
Sketch uses 49912 bytes (19%) of program storage space. Maximum is 253952 bytes.
Global variables use 6613 bytes (80%) of dynamic memory, leaving 1579 bytes for local variables. Maximum is 8192 bytes.
```

Version 1.1.1:
_still in production_
- sensor values are incorrect again.

*/


#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Hardware Options
#define ETHERNET_SHIELD 'A'     // Select from 'A' or 'B' (Only applies to practable.io hardware - for your own hardware change byte mac[] in globals.h to match your ethernet shield)

// Debugging Options
#define DEBUG_SAMPLING false
#define DEBUG_ADAM false
#define PRINT_RAW_DATA false
#define DEBUG_STATE_MACHINE false
#define DEBUG_STATES false
#define DEBUG_SENSOR_CALC false
#define DEBUG_SENSOR_HISTORY false
#define DEBUG_SERIAL false
#define DEBUG_JSON false

// User Options
#define BUILD_JSON true  //overkill but exists to enable testing with JSON being BUILT but not PRINTED or disabled entirely to prevent issues while testing
#define PRINT_JSON true
#define COMMAND_HINTS false

// Disabling Options (for debugging)
#define ADAM6052A_ACTIVE true
#define ADAM6052B_ACTIVE true
#define ADAM6217C_ACTIVE true
#define ADAM6217D_ACTIVE true

#define I2C_ACTIVE true
#define BME_POWER_PIN 13    // Power for BME280 is supplied via DO pin
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;  // I2C


#define SAMPLING_DELAY 1000
#define JSON_REPORT_DELAY_mS 5000

#define JSON_BUFFER_SIZE 720


// Include all other files here

// Library Files
#include "globals.h"
#include "ArduinoJson-v6.9.1.h"
#include "adamController.h"
#include "sensorObj.h"

// Organised Defined Functions (outside of libraries)
#include "stateMachine.h"
#include "jsonFunctions.h"
#include "adamFunctions.h"
#include "sensorFunctions.h"
#include "otherFunctions.h"

void setup() {
  serial_begin();
  ethernet_begin();
  adams_begin();
  sensors_begin();
  Serial.println(F(" "));
}



void loop() {
  sm_Run();  // Runs JSON parser, selects operational state & sets output hardware

  // Sample all Data inputs
  if (millis() - lastSample >= SAMPLING_DELAY) {
    lastSample = millis();
#if ADAM6052A_ACTIVE == true
    adam6052_A.check_modbus_connect();
    sample_adam6052A();
#endif
#if ADAM6052B_ACTIVE == true
    adam6052_B.check_modbus_connect();
    sample_adam6052B();
#endif

#if ADAM6217C_ACTIVE == true
    adam6217_C.check_modbus_connect();
    sample_adam6217C();
#endif
#if ADAM6217D_ACTIVE == true
    adam6217_D.check_modbus_connect();
    sample_adam6217D();
#endif
#if I2C_ACTIVE == true
    sample_bme280();
#endif
  }

  if (millis() - lastReport >= JSON_REPORT_DELAY_mS) {
    if (BUILD_JSON) { build_json(); };
    lastReport = millis();
  }
}










// Comment here for reasons