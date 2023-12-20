/*  adamController.cpp

  arduino/c++ library for control of generic Advantech Data Aquisition Modules (ADAM-xxxx) 


*/

/*  Anatomy of a ModBus Message


  0x  (in hex)
message prefix
  01  station address
  0F  function code   (01, 02, 03, 04,05, 06, 08, 0f, 10 )
  00  end of prefix
message contents
  10  coil/register address High Byte
  17  coil/register address low byte
  0A  ??
  02  ??
  CD  ??
  01  ??

ASCII Commands
$aaM  = $01M


*/


#include "adamController.h"

#define DEBUG true




void adamController::begin() {
}



void adamController::check_modbus_connect() {
  if (!modbusTCP.connected()) {
    // client not connected, start the Modbus TCP client
    Serial.println("Attempting to connect to Modbus TCP server");
    modbusConnected = false;
    if (!modbusTCP.begin(serverIP, 502)) {
      Serial.println("Modbus TCP Client failed to connect!");

    } else {
      Serial.println("Modbus TCP Client connected");
      modbusConnected = true;
    }
  }
}





int16_t adamController::set_coil(int coilNum, bool coilState) {
  uint8_t state;
  if (coilState) {
    state = 0x01;
  } else {
    state = 0x00;
  }

  char buffer[64];

  if ((coilNum >= 0) && (coilNum < 8)) {
    if (!modbusTCP.coilWrite(0x10, state)) {
      sprintf(buffer, "Failed to set coil: %i ( %#0x ) to %i. %s", coilNum, d_out[coilNum], coilState, modbusTCP.lastError());
      coilState = -1;
      // Serial.println(modbusTCP.lastError());
    } else {
      sprintf(buffer, "Setting Coil: %i ( %#0x ) to %i", coilNum, d_out[coilNum], coilState);
    }
  } else {
    sprintf(buffer, "Unable to set Coil %i - out of range :(", coilNum);
    coilState = -1;
  }
#if DEBUG == true
  Serial.println(buffer);
#endif
return coilState;
}



int16_t adamController::set_coils(uint8_t coilStates = 0b00000000) {
  int16_t response;
  response = modbusTCP.beginTransmission(COILS, 0x10, 0x08);  // type, address (any val) , nb (no bytes to be sent)

  response = modbusTCP.write(coilStates & 0b00000001);
  response = modbusTCP.write(coilStates & 0b00000010);  // Fun bitmasking operation
  response = modbusTCP.write(coilStates & 0b00000100);
  response = modbusTCP.write(coilStates & 0b00001000);
  response = modbusTCP.write(coilStates & 0b00010000);
  response = modbusTCP.write(coilStates & 0b00100000);
  response = modbusTCP.write(coilStates & 0b01000000);
  response = modbusTCP.write(coilStates & 0b10000000);

  response = modbusTCP.endTransmission();

  char binString[9];
  itoa(coilStates, binString, 2);  //trying some magic to make sprinf work to print status in columns
  int zeroPadding = int(8 - strlen(binString));
  char buffer[64];

  if (response == 1) {
    sprintf(buffer, "Set Coils:   %s%s ", leadingZeros[zeroPadding], binString);
  } else {
    sprintf(buffer, "ERROR: Unable to Set Coils to: %s%s ", leadingZeros[zeroPadding], binString);
    coilStates = -1;
  }
//  Serial.println(response);
#if DEBUG == true
  Serial.println(buffer);
#endif
  return coilStates;
}



int16_t adamController::read_coil(uint8_t outputNum) {
  char buffer[64];
  if (outputNum < 8) {
    int16_t outState = modbusTCP.coilRead(d_out[outputNum]);
    if (outState == -1) {
      sprintf(buffer, "Error Code %i: Unable to Read Output Status %i :(", outState, outputNum);
    } else {
      sprintf(buffer, "Output %i Status: %i", outputNum, outState);
    }
  } else {
    sprintf(buffer, "Unable to Read Output Status %i - out of range :(", outputNum);
    outState = -1;
  }
#if DEBUG == true
  Serial.println(buffer);
#endif
  return outState;
}



int16_t adamController::read_coils() {
  int response = modbusTCP.requestFrom(COILS, d_out[0], 0x08);
  int numReadings = modbusTCP.available();  // Is this line even needed? requestFrom returns number of readings
  int readBuffer[numReadings];
  int coilStates = 0;
  char buffer[64];
  if (response > 0) {
    for (int i = 0; i < numReadings; i++) {
      readBuffer[i] = modbusTCP.read();                    // this array fill in reverse?
      coilStates = coilStates + readBuffer[i] * (1 << i);  // This calculates the total value of all the coils so it can be displayed in binary
    }

    char binString[9];
    itoa(coilStates, binString, 2);  //trying some magic to make sprinf work to print status in columns
    int zeroPadding = int(8 - strlen(binString));

    sprintf(buffer, "Read Coils:  %s%s ", leadingZeros[zeroPadding], binString);
  } else {
    sprintf(buffer, "ERROR: Unable to read coil status ");
  }

#if DEBUG == true
  Serial.println(buffer);
#endif
  return coilStates;
}





int16_t adamController::read_digital_input(uint8_t inputNum) {
  char buffer[64];
  if  (inputNum < 8) {
    int16_t inputState = modbusTCP.discreteInputRead(inputNum);
    if (inputState == -1) {
      sprintf(buffer, "Error Code %i: Unable to Read Input %i :(", inputState, inputNum);
    } else {
      sprintf(buffer, "Input %i Status: %i", inputNum, inputState);
    }
  } else {
    sprintf(buffer, "Unable to Read Input %i - out of range :(", inputNum);
    inputState = -1;
  }

#if DEBUG == true
  Serial.println(buffer);
#endif
  return inputState;
}




int16_t adamController::read_digital_inputs() {
  int response = modbusTCP.requestFrom( DISCRETE_INPUTS, d_in[0], 0x08);
  int numReadings = modbusTCP.available();  // Is this line even needed? requestFrom returns number of readings
  int readBuffer[numReadings];
  int inputStates = 0;
  char buffer[64];
  if (response > 0) {
    for (int i = 0; i < numReadings; i++) {
      readBuffer[i] = modbusTCP.read();  // this array fill in reverse?
      inputStates = inputStates + readBuffer[i] * (1 << i);  // This calculates the total value of all the coils so it can be displayed in binary
    }
    char binString[9];
    itoa(inputStates, binString, 2);  //trying some magic to make sprinf work to print status in columns
    int zeroPadding = int(8 - strlen(binString));

    sprintf(buffer, "Read Inputs: %s%s ", leadingZeros[zeroPadding], binString);
  } else {
    sprintf(buffer, "ERROR: Unable to read input status ");
    inputStates = -1
  }

#if DEBUG == true
  Serial.println(buffer);
#endif
  return inputStates;
}
