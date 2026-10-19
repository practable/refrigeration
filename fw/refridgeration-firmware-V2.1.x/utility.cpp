/*   otherFunctions.h

  All other utility and setup functions



*/


#include "utility.h"




void ethernet_begin() {
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println(F("{\"error\":\"Arduino: Ethernet shield not found. Can't run without hardware\"}"));
    while (true) {
      delay(1);  // do nothing, no point running without Ethernet hardware
    }
  }
  delay(500);
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println(F("{\"error\":\"Arduino: Ethernet cable not connected.\"}"));
  }
}

void print_json_state_data(jsonStateData_t &data) {
    printf("CMD recieved: %i, %i, %i, %u, %f, %d, %s, %s, %d \n", data.stateEnum, data.data_type, data.signedInt, data.uInt, data.floatData, data.boolData, data.msg, data.auth, data.cmd_received);
}

void print_program_info() {
    Serial.println();
    Serial.print(PROGRAM_NAME);
    Serial.print(F(" V"));
    Serial.print(FIRMWARE_VERSION);
    Serial.print(F(" by: "));
    Serial.println(DEVELOPER);
}