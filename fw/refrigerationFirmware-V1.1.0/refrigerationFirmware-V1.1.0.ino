/* refrogerationFirmware.ino

    Firmware for Remote Labs Refrigeration Experiment

    Imogen Heard
    21/12/23

## As of V1.0.0: 21/12/23
```
Sketch uses 42130 bytes (16%) of program storage space. Maximum is 253952 bytes.
Global variables use 6650 bytes (81%) of dynamic memory, leaving 1542 bytes for local variables. Maximum is 8192 bytes.

```


## V1.1.0 Development started 13/02/24
- Adding BME280 i2c atmospheric sensor, inc temp, pressure, humidity

1. Testing Different BME280 Libraries
  - Adafruit BME280
    - Lots of dependancies
  - BME280 by Tyler Glenn
  - BME280_Zanshin
```
Sketch uses 14792 bytes (5%) of program storage space. Maximum is 253952 bytes.
Global variables use 870 bytes (10%) of dynamic memory, leaving 7322 bytes for local variables. Maximum is 8192 bytes.

```

2. Completed adding i2c sensors UNTESTED

```
Sketch uses 41498 bytes (16%) of program storage space. Maximum is 253952 bytes.
Global variables use 6415 bytes (78%) of dynamic memory, leaving 1777 bytes for local variables. Maximum is 8192 bytes.

```

*/


#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


// Debugging Options
#define DEBUG_SAMPLING true
#define DEBUG_ADAM false
#define PRINT_RAW_DATA false
#define DEBUG_STATE_MACHINE false
#define DEBUG_STATES false
#define DEBUG_SENSOR_CALC false
#define DEBUG_SENSOR_HISTORY false
#define DEBUG_SERIAL false
#define DEBUG_JSON false

// User Options
#define PRINT_JSON false
#define COMMAND_HINTS false

#define ADAM6052A_ACTIVE false
#define ADAM6052B_ACTIVE false
#define ADAM6217C_ACTIVE false
#define ADAM6217D_ACTIVE false

#define I2C_ACTIVE true
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;  // I2C

#define SAMPLING_DELAY 1000
#define JSON_REPORT_DELAY_mS 5000


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
  Serial.println(" ");
}



void loop() {
  Serial.println("Testing Blackout START");
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
    Serial.println("Testing Blackout END");
    delay(1000);
#endif
  }

  if (millis() - lastReport >= JSON_REPORT_DELAY_mS) {
    build_json();
    lastReport = millis();
  }
}










// Comment here for reasons