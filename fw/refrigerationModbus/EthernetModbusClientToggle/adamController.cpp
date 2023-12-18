/*  adamController.cpp

  arduino/c++ library for control of generic Advantech Data Aquisition Modules (ADAM-xxxx) 


*/


#include "adamController.h"


void adamController::begin() {
    if (!modbusTCPClient.connected()) {
    // client not connected, start the Modbus TCP client
    Serial.println("Attempting to connect to Modbus TCP server");
    
    if (!modbusTCPClient.begin(server, 502)) {
      Serial.println("Modbus TCP Client failed to connect!");
    } else {
      Serial.println("Modbus TCP Client connected");
    }
  } 
}



int adamController::set_coil(int coilNum, bool coilState) {
}




int adamController::set_coils(uint8_t coilStates = 0b00000000) {
}



bool adamController::read_input(uint8_t inputNum) {
}



uint8_t adamController::read_inputs() {
}
