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

#include "globals.h"
#include "ArduinoJson-v6.9.1.h"
#include "stateMachine.h"
#include "adamController.h"
#include "sensorObj.h"

#include "jsonFunctions.h"


void setup() {
  serial_begin();
  ethernet_begin();
  adams_begin();
  sensors_begin();
  Serial.println(" ");
}

void serial_begin() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  Serial.println(F("\n"));
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(F("\nRefrigeration Experiment - Control Firmware"));
}

void ethernet_begin() {
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println(F("Arduino: Ethernet shield was not found. can't run without hardware"));
    while (true) {
      delay(1);  // do nothing, no point running without Ethernet hardware
    }
  }
  delay(500);
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println(F("Arduino: Ethernet cable is not connected."));
  }
}

void adams_begin() {
#if ADAM6052A_ACTIVE == true
  adam6052_A.begin();
  adam6052_A.set_coils(0b00000000);
#endif
#if ADAM6052B_ACTIVE == true
  adam6052_B.begin();
  adam6052_B.set_coils(0b00000000);
#endif
#if ADAM6217A_ACTIVE == true
  adam6217_C.begin();
#endif
#if ADAM6217B_ACTIVE == true
  adam6217_D.begin();
#endif
  delay(1000);
}

void sensors_begin() {
  // init Temp Sensors
  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    temp_s[i].set_range_min(0, 0);  // (processVariable, measuredVal)
    temp_s[i].set_range_max(100, 10);
    temp_s[i].setCalibration();
  }
  for (int i = 0; i < NUM_PRESSURE_SENSORS; i++) {
    pressure_s[i].set_range_min(1, 0);
    pressure_s[i].set_range_max(6, 30);
    pressure_s[i].setCalibration();
  }
  flow_s.set_range_min(4, 0);
  flow_s.set_range_max(20, 25);
  flow_s.setCalibration();
  power_s.set_range_min(0, 0);
  power_s.set_range_max(20, 1053);
  power_s.setCalibration();
  // No longer needed as using i2C sensor
  //  t_ambi.set_range_min(4, -10);  // guessing at these values for now
  //  t_ambi.set_range_max(20, 100);
  //  t_ambi.setCalibration();
  //  p_ambi.set_range_min(4, 600);  // mBar
  //  p_ambi.set_range_max(20, 1500);
  //  p_ambi.setCalibration();
  // Instead use!
  unsigned status;
  status = bme.begin(0x76);
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
#endif
  }

  if (millis() - lastReport >= JSON_REPORT_DELAY_mS) {
    build_json();
    lastReport = millis();
  }
}

void sample_adam6052A() {
  adam6052_A.read_coils();
//adam6052A.read_digital_inputs();  // not needed in this iteration
#if ADAM6052A_ACTIVE == true
#if DEBUG_SAMPLING == true
  adam6052A.printBin(adam6052A.g_coilState);
#endif
#endif
}


void sample_adam6052B() {
  adam6052_B.read_coils();
//adam6052A.read_digital_inputs();  // not needed in this iteration
#if ADAM6052B_ACTIVE == true
#if DEBUG_SAMPLING == true
  adam6052B.printBin(adam6052B.g_coilState);
#endif
#endif
}


void sample_adam6217C() {
  adam6217_C.read_analog_inputs();  // read all temperature sensor inputs
  sampleTimestamp = millis();       // This takes a "generic" timestamp that should be accurate enough for most purposes
  for (int i = 0; i < NUM_PRESSURE_SENSORS; i++) {
    ps_vals[i] = pressure_s[i].calcProcessVar(adam6217_C.d_array.f_data[i]);
#if DEBUG_SAMPLING == true
    Serial.print(ps_vals[i]);
    Serial.print(F(" Bar"));
#endif
  }
  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    ts_vals[i] = temp_s[i].calcProcessVar(adam6217_C.d_array.f_data[i + 3]);  // index for temp sensors starts at 3// calculate the process variable and save to temperature sensor array
                                                                              //   ts_times[i] = adam6217A.d_array.timeStamp_mS[i];                     // save the timestamp to the 2D array - depreciated no space left
                                                                              // temp_s[i].updateHistory(temp);                                    // this is only needed if doing maths in firmware(future use case?)
#if DEBUG_SAMPLING == true
    Serial.print(ts_vals[i]);
    Serial.print(F(" degC"));
#endif
  }
}

void sample_adam6217D() {
  adam6217_D.read_analog_inputs();  // This samples { "flow", "power", "PSA", "TSA" };
  //  sampleTimestamp = millis();  // This takes a "generic" timestamp that should be accurate enough for most purposes (not needed here unless running without the temp & pressure sensors)
  misc_vals[0] = flow_s.calcProcessVar(adam6217_D.d_array.f_data[0]);
  misc_vals[1] = power_s.calcProcessVar(adam6217_D.d_array.f_data[1]);
  // misc_vals[2] = t_ambi.calcProcessVar(adam6217_D.d_array.f_data[2]);  // These are now i2c sensors
  //  misc_vals[3] = p_ambi.calcProcessVar(adam6217_D.d_array.f_data[3]); // NOTE: This will cause errors in setion below unless loop is changed

#if DEBUG_SAMPLING == true
  for (int i = 0; i < 2; i++) {  // changed loop from i < 4 to i < 2
    Serial.print(misc_names[i]);
    Serial.print(F(" : "));
    Serial.print(misc_vals[i]);
    Serial.print(F(" "));
    Serial.println(misc_units[i]);
  }
#endif
}

// #TODO: is it worth seperating misc vals into 2 different arrays now? - lets try not to


void sample_bme280() {
  misc_vals[2] = bme.readTemperature();        // °C
  misc_vals[3] = bme.readPressure() / 100.0F;  // hPa
  misc_vals[4] = bme.readHumidity();           // %
#if DEBUG_SAMPLING == true
  for (int i = 2; i < 5; i++) {  // changed loop from i < 4 to i < 2
    Serial.print(i);
    Serial.print(": ");
    Serial.print(misc_names[i]);
    Serial.print(F(" : "));
    Serial.print(misc_vals[i]);
    Serial.print(F(" "));
    Serial.println(misc_units[i]);
    delay(2000);
  }
#endif
}








// Comment here for reasons