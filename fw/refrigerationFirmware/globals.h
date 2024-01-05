/*   globals.h

Global variables for Refrigeration Experiment


*/

#pragma once

#ifndef globals_h
#define globals_h

#include "ArduinoJson-v6.9.1.h"
#include "adamController.h"
#include "sensorObj.h"



// valve globals


// Power Relay globals
char relay_names[][5] = { "W1", "W2", "comp" };

// Sensor & Sampling Globals
uint32_t lastSample = 0;  // holds the time of the last sample
uint32_t lastReport = 0;  // holds the time of the last JSON report

uint32_t sampleTimestamp = 0;  // variable to hold the timestamp taken at the end of all sensor readings (use this instead of timestamps taken PRECISELY at the sample time - I think for this use case a few mS will not matter)
// keeping the more precise timestamps in code in case of future use case.

// Temp Sensor Globals

#define NUM_TEMP_SENSORS 5
sensorObj temp_s[NUM_TEMP_SENSORS] = {
  sensorObj(VOLTAGE_SENSOR, "degC", "TS1"),
  sensorObj(VOLTAGE_SENSOR, "degC", "TS2"),
  sensorObj(VOLTAGE_SENSOR, "degC", "TS3"),
  sensorObj(VOLTAGE_SENSOR, "degC", "TS4"),
  sensorObj(VOLTAGE_SENSOR, "degC", "TS5")
};

// Arrays for temp Sensor Vals
float ts_vals[NUM_TEMP_SENSORS] = { 0.0, 0.0, 0.0, 0.0, 0.0 };  // create array for TS data
//uint32_t ts_times[NUM_TEMP_SENSORS] = { 1000, 1000, 1000, 1000, 1000 };  // create array for TS timestamps  not enough space!

// Pressure Sensor Globals
#define NUM_PRESSURE_SENSORS 3
sensorObj pressure_s[NUM_PRESSURE_SENSORS] = {
  sensorObj(VOLTAGE_SENSOR, "bar", "PS1"),
  sensorObj(VOLTAGE_SENSOR, "bar", "PS2"),
  sensorObj(VOLTAGE_SENSOR, "bar", "PS3")
};

// Arrays for Pressure Sensor Vals
float ps_vals[NUM_PRESSURE_SENSORS] = { 0.0, 0.0, 0.0 };  // create array for TS data
//uint32_t ps_times[NUM_PRESSURE_SENSORS] = { 1000, 1000, 1000 };  // create array for TS timestamps


// Misc Sensor Globals
sensorObj flow_s(CURRENT_SENSOR, "flow", "flow");
sensorObj power_s(CURRENT_SENSOR, "W", "power");
sensorObj t_ambi(CURRENT_SENSOR, "degC", "TS_ambi");
sensorObj p_ambi(CURRENT_SENSOR, "mBar", "PS_ambi");

// Arrays for Misc Sensor Vals
float misc_vals[4] = { 0.0, 0.0, 0.0, 0.0 };  // create array for TS data
//uint32_t misc_times[4] = { 1000, 1000, 1000, 1000 };  // create array for TS timestamps
char misc_names[][6] = { "flow", "power", "PSA", "TSA" };
char misc_units[][6] = {"l/h", "W", "degC", "mBar"};


// struct for status
struct _status {
  bool ok;
  char state[20];
  int code;
  char message[16];
} status = { true, " ", 0, " " };

// names for status
char status_names[][8] = { "ok", "state", "code", "message" };



// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
// The IP address will be dependent on your local network:
//byte mac[] = { 0xA8, 0X61, 0x0A, 0xAE, 0xE1, 0x48 };  // FOR SHIELD A
byte mac[] = { 0xA8, 0X61, 0x0A, 0xAE, 0xF3, 0x23 };  // FOR SHIELD B

//Define the ip address for the client (local modbus controller) (the device this firmware is running on)
IPAddress ip(192, 168, 1, 100);

// Define the IP for the server (remote modbus device)
IPAddress adam6052A_ip(192, 168, 1, 111);  // update with the IP Address of your Modbus server (the remote IO controller)
IPAddress adam6052B_ip(192, 168, 1, 116);  // update with the IP Address of your Modbus server (the remote IO controller)
IPAddress adam6217C_ip(192, 168, 1, 112);  // update with the IP Address of your Modbus server (the remote IO controller)
IPAddress adam6217D_ip(192, 168, 1, 115);  // update with the IP Address of your Modbus server (the remote IO controller)

// Create an Ethernet Client
EthernetClient ethClient;


// Create an adamController object and pass the Ethernet Client and IP Address for the server
adamController adam6052_A(ethClient, adam6052A_ip, DAC_OUTPUT, "ADAM-6052-A");
adamController adam6052_B(ethClient, adam6052B_ip, DAC_OUTPUT, "ADAM-6052-B");
adamController adam6217_C(ethClient, adam6217C_ip, VOLTAGE_OUTPUT, "ADAM-6217-C");
adamController adam6217_D(ethClient, adam6217D_ip, CURRENT_OUTPUT, "ADAM-6217-D");




#endif
