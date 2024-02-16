/*  adamController.cpp

  arduino/c++ library for control of generic Advantech Data Aquisition Modules (ADAM-xxxx) 

  Imogen Heard
    21/12/23


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






void adamController::begin() {
  adamController::check_modbus_connect();
}



void adamController::check_modbus_connect() {
  if (!modbusTCP.connected()) {
    // client not connected, start the Modbus TCP client
    Serial.print(moduleName);
    Serial.println(F(": Attempting to connect to Modbus TCP server"));
    modbusConnected = false;
    if (!modbusTCP.begin(serverIP, 502)) {
      Serial.println(F(": Modbus TCP Client failed to connect!"));

    } else {
      Serial.print(moduleName);
      Serial.println(F(": Modbus TCP Client connected"));
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
    if (!modbusTCP.coilWrite(d_out[coilNum], state)) {
      sprintf(buffer, "%s: Failed to set coil: %i ( %#0x ) to %i. %s", moduleName, coilNum, d_out[coilNum], coilState, modbusTCP.lastError());
      coilState = -1;
      // Serial.println(modbusTCP.lastError());
    } else {
      sprintf(buffer, "%s: Setting Coil: %i ( %#0x ) to %i", moduleName, coilNum, d_out[coilNum], coilState);
    }
  } else {
    sprintf(buffer, "%s: Unable to set Coil %i - out of range :(", moduleName, coilNum);
    coilState = -1;
  }
#if DEBUG_ADAM == true
  Serial.println(buffer);
#endif
  return coilState;
}



int16_t adamController::set_coils(uint8_t coilStates) {
  int16_t response;
  response = modbusTCP.beginTransmission(COILS, 0x10, 0x08);  // type, address (any val) , nb (no bytes to be sent)

  for (int i = 0; i < 8; i++) {
    response = modbusTCP.write(coilStates & bitmask[i]);  // Fun bitmasking operation
  }
  response = modbusTCP.endTransmission();

  char binString[9];
  itoa(coilStates, binString, 2);  //trying some magic to make sprinf work to print status in columns
  int zeroPadding = int(8 - strlen(binString));
  char buffer[64];

  if (response == 1) {
    sprintf(buffer, "%s: Set Coils:   %s%s ", moduleName, leadingZeros[zeroPadding], binString);
  } else {
    sprintf(buffer, "%s: ERROR: Unable to Set Coils to: %s%s ", moduleName, leadingZeros[zeroPadding], binString);
    coilStates = -1;
  }
  // g_coilState = coilStates;
//  Serial.println(response);
#if DEBUG == true
  Serial.println(buffer);
#endif
  return coilStates;
}



int16_t adamController::read_coil(uint8_t outputNum) {
  char buffer[64];
  int16_t outState = -1;
  if (outputNum < 8) {
    outState = modbusTCP.coilRead(d_out[outputNum]);
    if (outState == -1) {
      sprintf(buffer, "%s: Error Code %i: Unable to Read Output Status %i :(", moduleName, outState, outputNum);
    } else {
      sprintf(buffer, "%s: Output %i Status: %i", moduleName, outputNum, outState);
    }
  } else {
    sprintf(buffer, "%s: Unable to Read Output Status %i - out of range :(", moduleName, outputNum);
    outState = -1;
  }
#if DEBUG_ADAM == true
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

    sprintf(buffer, "%s: Read Coils:  %s%s ", moduleName, leadingZeros[zeroPadding], binString);
  } else {
    sprintf(buffer, "%s: ERROR: Unable to read coil status ", moduleName);
  }
  g_coilState = coilStates;
#if DEBUG_ADAM == true
  Serial.println(buffer);
#endif
  return coilStates;
}





int16_t adamController::read_digital_input(uint8_t inputNum) {
  char buffer[64];
  int16_t inputState = -1;
  if (inputNum < 8) {
    inputState = modbusTCP.discreteInputRead(inputNum);
    if (inputState == -1) {
      sprintf(buffer, "%s: Error Code %i: Unable to Read Input %i :(", moduleName, inputState, inputNum);
    } else {
      sprintf(buffer, "%s: Input %i Status: %i", moduleName, inputNum, inputState);
    }
  } else {
    sprintf(buffer, "%s: Unable to Read Input %i - out of range :(", moduleName, inputNum);
    inputState = -1;
  }
#if DEBUG_ADAM == true
  Serial.println(buffer);
#endif
  return inputState;
}




int16_t adamController::read_digital_inputs() {
  int response = modbusTCP.requestFrom(DISCRETE_INPUTS, d_in[0], 0x08);
  int numReadings = modbusTCP.available();  // Is this line even needed? requestFrom returns number of readings
  int readBuffer[numReadings];
  int inputStates = 0;
  char buffer[64];
  if (response > 0) {
    for (int i = 0; i < numReadings; i++) {
      readBuffer[i] = modbusTCP.read();                      // this array fill in reverse?
      inputStates = inputStates + readBuffer[i] * (1 << i);  // This calculates the total value of all the coils so it can be displayed in binary
    }
    char binString[9];
    itoa(inputStates, binString, 2);  //trying some magic to make sprinf work to print status in columns
    int zeroPadding = int(8 - strlen(binString));

    sprintf(buffer, "%s: Read Digital Inputs: %s%s ", moduleName, leadingZeros[zeroPadding], binString);
  } else {
    sprintf(buffer, "%s: ERROR: Unable to read input status ", moduleName);
    inputStates = -1;
  }
  g_inputState = inputStates;
#if DEBUG_ADAM == true
  Serial.println(buffer);
#endif
  return inputStates;
}

void adamController::printBin(int16_t binaryVal) {
  char buffer[42];
  char binString[9];
  itoa(binaryVal, binString, 2);  //trying some magic to make sprinf work to print status in columns
  int zeroPadding = int(8 - strlen(binString));
  sprintf(buffer, "%s: Read Digital Inputs: %s%s ", moduleName, leadingZeros[zeroPadding], binString);
  Serial.println(buffer);
}


adamController::dataArray adamController::read_analog_inputs() {
  // dataArray analogVals; // Use the global variable its easier!
  int response = modbusTCP.requestFrom(INPUT_REGISTERS, a_in[0], 0x08);  //HOLDING_REGISTERS
  int numReadings = modbusTCP.available();                               // Is this line even needed? requestFrom returns number of readings
  uint16_t readBuffer[numReadings];
  int inputStates = 0;
  char buffer[514] = { 0 };
  if (response > 0) {
    for (int i = 0; i < numReadings; i++) {
      readBuffer[i] = modbusTCP.read();
      d_array.i_data[i] = readBuffer[i];  // always save the DAQ reading to the i_data buffer
      d_array.timeStamp_mS[i] = millis();
      switch (analogType) {
        case DAC_OUTPUT:
          // no other conversion needed, just copy int data to float variable to avoid breaking things when changes are made and user forgets to change i_data to f_data
          d_array.f_data[i] = float(d_array.i_data[i]);
          break;
        case VOLTAGE_OUTPUT:
          d_array.f_data[i] = adamController::daq_to_voltage(readBuffer[i]);  // do the conversion to voltage/current here
          break;
        case CURRENT_OUTPUT:
          d_array.f_data[i] = adamController::daq_to_current(readBuffer[i]);  // do the conversion to voltage/current here
          break;
        default:
          Serial.print(moduleName);
          Serial.println(F(": Error: Unknown analog data type requested"));
          break;
      }
    }
    sprintf(buffer, "%s: Read Analog Inputs (DAC): %u, %u, %u, %u, %u, %u ", moduleName, readBuffer[0], readBuffer[1], readBuffer[2], readBuffer[3], readBuffer[4], readBuffer[5]);
  } else {
    sprintf(buffer, "%s: ERROR: Unable to read input status ", moduleName);
    inputStates = -1;
  }

#if PRINT_RAW_DATA == true
  Serial.println(buffer);
#endif
  //delete buffer;  // doesnt work
  return d_array;
}

float adamController::daq_to_voltage(uint16_t daq_value) {
  float voltage = float(daq_value) - 32768.0;
  voltage = voltage / 3257.333;
  return voltage;
}

float adamController::daq_to_current(uint16_t daq_value) {
  float current = float(daq_value);  // - 32768.0;
  current = current / 3276.799;
  return current;
}
