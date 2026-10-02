/* refrogerationFirmware.ino

    Firmware for Remote Labs Refrigeration Experiment

    Imogen Heard
    21/12/23

    V2.0.0 Dev Starts
    01/10/2026




V
Version 1.4.0: 
# IN DEVELOPMENT 15/04/2024
- Adding status/error messages for low/high pressure to indicate to user that compressor may be close to deactivation.
- Moved Sample Timestamp to main loop for flexibility
- Added definitions for experiment type & firmware version

V2.0.0
# Starting work on firmware for V2.0 fridge
- adding analog output control for fan speed
- seperate fan control for evap and cond




*/


#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Firmware Options

#define EXPERIMENT_NAME "frig01"
#define FIRMWARE_VERSION "refrigerationFirmware_V2.0.0"

// Hardware Options
#define ETHERNET_SHIELD 'D'  // Select from 'A' or 'B' (Only applies to practable.io hardware - for your own hardware change byte mac[] in globals.h to match your ethernet shield)

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
#define DISABLE_SENSOR_SCALING false  // disables sensor scaling and outputs raw ADC value - useful for calibrating sensors

// User Options
#define BUILD_JSON true  //overkill but exists to enable testing with JSON being BUILT but not PRINTED or disabled entirely to prevent issues while testing
#define PRINT_JSON true
#define PRETTY_PRINT_JSON false  // Makes JSON Human readable (But not machine readable!)
#define COMMAND_HINTS false      // Serial prints sample commands in JSON format

// Disabling Options (for debugging)
#define ADAM6052A_ACTIVE true
#define ADAM6052B_ACTIVE true
#define ADAM6217C_ACTIVE true
#define ADAM6217D_ACTIVE true

#define I2C_ACTIVE true
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;  // I2C

#define LIGHTS_ACTIVE_TIME_mS 3600000 // = 15 min
#define GLOBAL_TIMEOUT_mS    3600000 // = 1h


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
    lastSample = millis();
    sampleTimestamp = lastSample;  // This takes a "generic" timestamp that should be accurate enough for most purposes
  }

  if (millis() - lastReport >= JSON_REPORT_DELAY_mS) {
    if (BUILD_JSON) { build_json(); };
    lastReport = millis();
  }
}










// Comment here for reasons