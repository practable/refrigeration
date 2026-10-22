#ifndef globals_h
#define globals_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <wProgram.h>
#endif

// #pragma "Use ESP32 Version 3.x.x"

#include "libs.h" // include all libraries used in project
#include "jsonMessenger.h"
#include "jsonStateMachine.h"

#include "jsonReporter.h"

// Program Attributes
#define PROGRAM_NAME "refrigeration-V2"
#define FIRMWARE_VERSION "2.2.0"
#define DEVELOPER "Imogen-Wren"

#define ETHERNET_SHIELD 'D'

extern byte mac[];

extern const jsonStateData_t emptyData;
extern jsonStateData_t nextState_data;

// jsonMessenger Object to handle incoming Serial JSON commands
extern jsonMessenger jsonRX; // create a jsonMessenger object to handle commands received over Serial connection

// stateMachine Object now handles all state machine transitions
extern stateMachine sm;

// JSON error reporting
extern jsonError error;

// JSON data reporting
extern jsonReporter report;

// BELOW HERE UNCHECKED FOR NOW 19/10/26

// Power Relay globals
extern char relay_names[][7];

// Sensor & Sampling Globals
// NOTE: these were all 32bit values, reduced to save space
extern uint32_t lastSample; // holds the time of the last sample
extern uint32_t lastReport; // holds the time of the last JSON report

extern uint32_t sampleTimestamp; // variable to hold the timestamp taken at the end of all sensor readings (use this instead of timestamps taken PRECISELY at the sample time - I think for this use case a few mS will not matter)
// keeping the more precise timestamps in code in case of future use case.

// Temp Sensor Globals

#define NUM_TEMP_SENSORS 5
extern sensorObj temp_s[NUM_TEMP_SENSORS];

// Arrays for temp Sensor Vals
extern float ts_vals[NUM_TEMP_SENSORS]; // create array for TS data
// uint32_t ts_times[NUM_TEMP_SENSORS] = { 1000, 1000, 1000, 1000, 1000 };  // create array for TS timestamps  not enough space!

// Pressure Sensor Globals
#define NUM_PRESSURE_SENSORS 3
extern sensorObj pressure_s[NUM_PRESSURE_SENSORS];

// Arrays for Pressure Sensor Vals
extern float ps_vals[NUM_PRESSURE_SENSORS]; // create array for TS data
// uint32_t ps_times[NUM_PRESSURE_SENSORS] = { 1000, 1000, 1000 };  // create array for TS timestamps

// Define limits for pressure high side and low side switched (NOTE: This just affects when warning message is sent to UI)
#define PS1_MIN 0
#define PS1_MAX 0
#define PS3_MIN 0
#define PS3_MAX 0

// Misc Sensor Globals
extern sensorObj flow_s;
extern sensorObj power_s;
// sensorObj t_ambi(CURRENT_SENSOR, "degC", "TS_ambi"); Not required as i2c sensor data is delivered directly by object
// sensorObj p_ambi(CURRENT_SENSOR, "mBar", "PS_ambi");

// Arrays for Misc Sensor Vals
extern float misc_vals[5]; // create array for misc data
// uint32_t misc_times[4] = { 1000, 1000, 1000, 1000 };  // create array for TS timestamps
extern char misc_names[][6];
extern char misc_units[][6];

// names for status
extern char status_names[][8];

extern bool lights_active;
extern uint32_t lights_active_time_mS;

extern bool experiment_active;
extern uint32_t last_cmd_rx_mS;

// Define the ip address for the client (local modbus controller) (the device this firmware is running on)
extern IPAddress ip;

// Define the IP for the server (remote modbus device)
extern IPAddress adam6052A_ip; // update with the IP Address of your Modbus server (the remote IO controller)
extern IPAddress adam6052B_ip; // update with the IP Address of your Modbus server (the remote IO controller)
extern IPAddress adam6217C_ip; // update with the IP Address of your Modbus server (the remote IO controller)
extern IPAddress adam6217D_ip; // update with the IP Address of your Modbus server (the remote IO controller)

// Create an Ethernet Client
extern EthernetClient ethClient;

#include "adamFunctions.h"

extern adamFunctions adams;

#endif