/* refrogerationFirmware.ino

    Firmware for Remote Labs Refrigeration Experiment

    Imogen Heard
    21/12/23



*/


#include <SPI.h>
#include <Ethernet.h>


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
#define PRINT_JSON true
#define COMMAND_HINTS false

#define ADAM6052A_ACTIVE true
#define ADAM6052B_ACTIVE true
#define ADAM6217C_ACTIVE true
#define ADAM6217D_ACTIVE true

#define SAMPLING_DELAY 1000
#define JSON_REPORT_DELAY_mS 5000


// Include all other files here

#include "globals.h"
#include "ArduinoJson-v6.9.1.h"
#include "stateMachine.h"
#include "adamController.h"
#include "sensorObj.h"




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
  Serial.println("\n");
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
    temp_s[i].setCalibration(0, 100, 0, 10);      // (process low, process high, voltage low, voltage high, postoffset) Linear sensor scaling
  }


  pressure_s[0].setCalibration(-0.8, 7, 1, 6, -0.48);   // (process low, process high, voltage low, voltage high, postoffset) Linear sensor scaling
  pressure_s[1].setCalibration(0, 30, 1, 6);     // (process low, process high, voltage low, voltage high) Linear sensor scaling
  pressure_s[2].setCalibration(0, 30, 1, 6);     // (process low, process high, voltage low, voltage high) Linear sensor scaling



  flow_s.setCalibration(0, 25, 0, 20);           // (process low, process high, current low, current high) Linear sensor scaling
  power_s.setCalibration(0, 1300, 0, 20);        // (process low, process high, current low, current high) Linear sensor scaling
  t_ambi.setCalibration(-10, 100, 4, 20);        // (process low, process high, current low, current high) Linear sensor scaling
  p_ambi.setCalibration(600, 1500, 4, 20);       // (process low, process high, current low, current high) Linear sensor scaling
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
  }

  if (millis() - lastReport >= JSON_REPORT_DELAY_mS) {
    build_json();
    lastReport = millis();
  }
}

void sample_adam6052A() {
  adam6052_A.read_coils();
//adam6052A.read_digital_inputs();  // not needed in this iteration
#if DEBUG_SAMPLING == true
  adam6052A.printBin(adam6052A.g_coilState);
#endif
}


void sample_adam6052B() {
  adam6052_B.read_coils();
//adam6052A.read_digital_inputs();  // not needed in this iteration
#if DEBUG_SAMPLING == true
  adam6052B.printBin(adam6052B.g_coilState);
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
  misc_vals[2] = t_ambi.calcProcessVar(adam6217_D.d_array.f_data[2]);
  misc_vals[3] = p_ambi.calcProcessVar(adam6217_D.d_array.f_data[3]);

#if DEBUG_SAMPLING == true
  for (int i = 0; i < 4; i++) {
    Serial.print(misc_names[i]);
    Serial.print(F(" : "));
    Serial.print(misc_vals[i]);
    Serial.print(F(" "));
    Serial.println(misc_units[i]);
  }
#endif
}



void build_json() {
  char json_header[] = "\"{";
  char json_buffer[620] = { "" };  // this needs to be sized correctly 512 is too small 600 seems to work for now
  char float_buffer[16];
  char json_footer[] = "\n}\"";
  char valves[] = "valves";
  char relays[] = "relays";
  char sensors[] = "sensors";
  char temperature[] = "temperature";
  char pressure[] = "pressure";
  char misc[] = "misc";
  char s_status[] = "status";


  // start json string building
  sprintf(json_buffer, "%s\n  \"timestamp\" : %lu,", json_header, sampleTimestamp);


  // load valve data
  sprintf(json_buffer, "%s\n  \"%s\" : {", json_buffer, valves);
  for (int i = 0; i < 8; i++) {
    sprintf(json_buffer, "%s\n    \"V%i\" : %i,", json_buffer, i + 1, bool(adam6052_A.g_coilState & 1 << i));  // fancy binary operation to bitmask the valvestate variable with a power of 2 to get true or false for each valve based on valvestate int
  }
  sprintf(json_buffer, "%s\n  },", json_buffer);

  //load power relay data
  sprintf(json_buffer, "%s\n  \"%s\" : {", json_buffer, relays);
  for (int i = 0; i < 3; i++) {
    sprintf(json_buffer, "%s\n    \"%s\" : %i,", json_buffer, relay_names[i], bool(adam6052_B.g_coilState & 1 << i));
  }
  sprintf(json_buffer, "%s\n  },", json_buffer);

  // Load sensor data
  sprintf(json_buffer, "%s\n  \"%s\" : {", json_buffer, sensors);

  // load pressure sensors
  sprintf(json_buffer, "%s\n    \"%s\" : {", json_buffer, pressure);
  for (int i = 0; i < NUM_PRESSURE_SENSORS; i++) {
    dtostrf(ps_vals[i], 6, 2, float_buffer);
    sprintf(json_buffer, "%s\n      \"PS%i\" : %6s,", json_buffer, i + 1, float_buffer);
  }
  sprintf(json_buffer, "%s\n    },", json_buffer);


  // load temp sensors
  sprintf(json_buffer, "%s\n    \"%s\" : {", json_buffer, temperature);
  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    dtostrf(ts_vals[i], 6, 2, float_buffer);
    sprintf(json_buffer, "%s\n      \"TS%i\" : %6s,", json_buffer, i + 1, float_buffer);
  }
  sprintf(json_buffer, "%s\n    },", json_buffer);


  // load misc sensors
  sprintf(json_buffer, "%s\n    \"%s\" : {", json_buffer, misc);
  for (int i = 0; i < 4; i++) {
    dtostrf(misc_vals[i], 6, 2, float_buffer);
    sprintf(json_buffer, "%s\n      \"%s\" : %6s,", json_buffer, misc_names[i], float_buffer);
  }
  sprintf(json_buffer, "%s\n    }", json_buffer);

  // close sensors
  sprintf(json_buffer, "%s\n  },", json_buffer);

  // load status message
  sprintf(json_buffer, "%s\n\"%s\" : {", json_buffer, s_status);
  sprintf(json_buffer, "%s\n    \"%s\" : %i,", json_buffer, status_names[0], status.ok);
  sprintf(json_buffer, "%s\n    \"%s\" : \"%s\",", json_buffer, status_names[1], status.state);
  sprintf(json_buffer, "%s\n    \"%s\" : %i,", json_buffer, status_names[2], status.code);
  sprintf(json_buffer, "%s\n    \"%s\" : \"%s\"", json_buffer, status_names[3], status.message);
  sprintf(json_buffer, "%s\n  }", json_buffer);


  // close json string
  sprintf(json_buffer, "%s%s", json_buffer, json_footer);

  if (PRINT_JSON) {
    Serial.println(json_buffer);
  }
}





// Comment here for reasons