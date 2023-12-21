/* refrogerationFirmware.ino

    Firmware for Remote Labs Refrigeration Experiment

    Imogen Heard
    21/12/23



*/


#include <SPI.h>
#include <Ethernet.h>


#define DEBUG true

#include "globals.h"

#include "stateMachine.h"
#include "adamController.h" 
#include "sensorObj.h"




void setup() {
  serial_begin();
  ethernet_begin();
  adams_begin();
  sensors_begin();
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
  adam6052B.begin();
  //adam6024.begin();
  delay(1000);
  adam6052A.set_coils(0b00000000);
  adam6052B.set_coils(0b00000000);
}

void sensors_begin() {
  // init Temp Sensors
  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    temp_s[i].set_range_min(-10);
    temp_s[i].set_range_max(10);
    temp_s[i].setCalibration();
  }
}





void loop() {
  adam6052A.check_modbus_connect();
  adam6052B.check_modbus_connect();
 // adam6024.check_modbus_connect();
  // function here to gather all data
  sm_Run();

}

/*
void adamAnalogController() {
 // adam6024.check_modbus_connect();

 // adam6024.read_analog_inputs();

  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    Serial.print(adam6024.d_array.i_data[i]);
    Serial.print(" : ");
    float voltage = temp_s[i].calcProcessVar(adam6024.d_array.i_data[i]);
    Serial.print(" ");
    Serial.print(voltage);
    Serial.print(" V, ");
    temp_s[i].updateHistory(voltage);
    Serial.println("");
  }
  Serial.println("");
}
*/

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








// Comment here for reasons