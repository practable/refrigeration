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

Version 1.1.1: 15/02/2024
- sensor values fixed
- Added quick start mode for V1 and fans
- Tidied up sensor objects
- Fully Tested and Validated with Hardware Rig
- Changed naming convention from DAC (Data Aquisition Controller) to ADC (Analog to Digital Converter) to better represent the function of class methods
```
Sketch uses 50794 bytes (20%) of program storage space. Maximum is 253952 bytes.
Global variables use 6683 bytes (81%) of dynamic memory, leaving 1509 bytes for local variables. Maximum is 8192 bytes.
```

Version 1.1.2: 20/04/2024
- JSONised startup & startup error messages
```
Sketch uses 50820 bytes (20%) of program storage space. Maximum is 253952 bytes.
Global variables use 6683 bytes (81%) of dynamic memory, leaving 1509 bytes for local variables. Maximum is 8192 bytes.
```

Version 1.2.1: 20/04/2024
- JSONised all error & status messages
// {\"status\":\"    JSON Status header
// {\"error\":\"     JSON Error header
// \"}               JSON status/error footer

```
Sketch uses 50682 bytes (19%) of program storage space. Maximum is 253952 bytes.
Global variables use 6779 bytes (82%) of dynamic memory, leaving 1413 bytes for local variables. Maximum is 8192 bytes.
```

Version 1.3.0: 27/04/2024
- Removed all newline chars from JSON printout,
- Added PRETTY_PRINT_JSON option to re-enable all newline chars for debugging

```
Sketch uses 50890 bytes (20%) of program storage space. Maximum is 253952 bytes.
Global variables use 6815 bytes (83%) of dynamic memory, leaving 1377 bytes for local variables. Maximum is 8192 bytes.
```


Version 1.3.1: 28/04/2024
- Removed additional commas from JSON message - BUG FIX
- Changed double to single quotes to wrap JSON
- rebooting error detected - stackoverflow?
- Reduced size of JSON buffer from 720 to 620
- Fixed rebooting error but check for problem reappearing
- #TODO: If rebooting issue or stackoverflow reappears devolve pretty print JSON into own function & only load into memory if option is selected
```
Sketch uses 50780 bytes (19%) of program storage space. Maximum is 253952 bytes.
Global variables use 6921 bytes (84%) of dynamic memory, leaving 1271 bytes for local variables. Maximum is 8192 bytes.
```
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
#define DISABLE_SENSOR_SCALING false   // disables sensor scaling and outputs raw ADC value - useful for calibrating sensors

// User Options     
#define BUILD_JSON true  //overkill but exists to enable testing with JSON being BUILT but not PRINTED or disabled entirely to prevent issues while testing
#define PRINT_JSON true
#define PRETTY_PRINT_JSON false  // Makes JSON Human readable (But not machine readable!)
#define COMMAND_HINTS false  // Serial prints sample commands in JSON format

// Disabling Options (for debugging)
#define ADAM6052A_ACTIVE true
#define ADAM6052B_ACTIVE true
#define ADAM6217C_ACTIVE true
#define ADAM6217D_ACTIVE true

#define I2C_ACTIVE true
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;  // I2C


#define SAMPLING_DELAY 1000
#define JSON_REPORT_DELAY_mS 5000

#define JSON_BUFFER_SIZE 620  // 720 too big?  NOTE: on recieved message through backend, message is 698 char long, but this may include system overhead NOTE: this INCLUDES spaces, can remove them for non pretty print

//char JSON_status_header[15] = {"{\"status\":\""};    // JSON Status header
//char JSON_error_header[14] = {"{\"error\":\""};     //     JSON Error header
//char JSON_footer[4] = {"\"}"};                     //  JSON status/error footer

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