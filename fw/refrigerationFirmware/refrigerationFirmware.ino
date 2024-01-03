/* refrogerationFirmware.ino

    Firmware for Remote Labs Refrigeration Experiment

    Imogen Heard
    21/12/23



*/


#include <SPI.h>
#include <Ethernet.h>




#include "globals.h"
#include "ArduinoJson-v6.9.1.h"
#include "stateMachine.h"
#include "adamController.h"
#include "sensorObj.h"

#define DEBUG_FIRMWARE false


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
  Serial.println("\nRefrigeration Experiment - Control Firmware");
}

void ethernet_begin() {
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Arduino: Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1);  // do nothing, no point running without Ethernet hardware
    }
  }
  delay(500);
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Arduino: Ethernet cable is not connected.");
  }
}

void adams_begin() {
  adam6052A.begin();
  // adam6052B.begin();
  adam6217A.begin();
  delay(1000);
  adam6052A.set_coils(0b00000000);
  // adam6052B.set_coils(0b00000000);
}

void sensors_begin() {
  // init Temp Sensors
  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    temp_s[i].set_range_min(0, -10);  // (processVariable, measuredVal)
    temp_s[i].set_range_max(100, 10);
    temp_s[i].setCalibration();
  }
}





void loop() {
  adam6052A.check_modbus_connect();
  // adam6052B.check_modbus_connect();
  adam6217A.check_modbus_connect();
  // function here to gather all data
  adamAnalogController();
  build_json();
  //sm_Run();

  delay(1000);
}


void adamAnalogController() {

  adam6217A.read_analog_inputs();  // read all temperature sensor inputs


  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    ts_vals[i] = temp_s[i].calcProcessVar(adam6217A.d_array.f_data[i]);  // calculate the process variable and save to temperature sensor array
    ts_times[i] = adam6217A.d_array.timeStamp_mS[i];                     // save the timestamp to the 2D array
                                                                         // temp_s[i].updateHistory(temp);                                    // this is only needed if doing maths in firmware(future use case?)
#if DEBUG_FIRMWARE == true
    Serial.print(ts_vals[i]);
    Serial.print(" degC, time: ");
    Serial.print(ts_times[i]);
    Serial.println(" mS");
#endif
  }
  // Serial.println("");
}


void adamDigitalController() {

  adam6052A.check_modbus_connect();
  int error;
  int randomVal = random(256);
  if (adam6052A.modbusConnected) {
    error = adam6052A.set_coils(randomVal);
    if (error == -1) {
      Serial.println("Arduino: Error setting coils");
    }
    int value = adam6052A.read_coils();
    if (value == randomVal) {
      Serial.println("Arduino: values match coils written successfully");
    } else {
      Serial.println("Arduino: Error: Mismatch between coils written & coils read");
    }
    adam6052A.read_digital_inputs();
  }  // if modbusConnected
  else {
    Serial.println("Arduino: Error: Modbus connection dropped");
  }
}


void build_json() {
  char json_header[] = " {\"";
  char json_buffer[256];// = {"\n"};  // WEIRD BUG HERE - If string isnt null terminated it prints buffer from adamController::dataArray adamController::read_analog_inputs() NO IDEA WHY both arrays should be large enough
  char float_buffer[16];
  char json_footer[] = " \"}";


  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
   // dtostrf(ts_vals[i], 6, 2, float_buffer);
  //  Serial.println(float_buffer);
   // sprintf(json_buffer, "%s\"TS%i\": %6s \n",json_buffer, i + 1, float_buffer);    
  }
  Serial.println(json_buffer);
 // Serial.print("\n");
}





// Comment here for reasons