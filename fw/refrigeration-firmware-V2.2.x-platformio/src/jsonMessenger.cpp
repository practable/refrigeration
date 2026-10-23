

#include "jsonMessenger.h"

/*

VERSION V0.2.0 REFACTORED TO USE ARRAYs instead of std::map


*/

// #define DEBUG_JSON_MESSENGER true

jsonMessenger::jsonMessenger() {}

void jsonMessenger::jsonBegin() {
    Serial.begin(115200);
    Serial.print("{\"json\":\"messenger\",\"version\":\"");
    Serial.print(JSON_MESSENGER_VERSION);
    Serial.println("\"}");
}

void jsonMessenger::printJSON(StaticJsonDocument<JSON_RX_SIZE> *jsonDoc) {
#if PRETTY_PRINT_JSON == true
#pragma JSON set to Pretty Print !-May experience problems with Machine Parsing
    serializeJsonPretty(*jsonDoc, Serial);
#else
#pragma JSON set to standard JSON output - For human readability try enabling Pretty Print !
    serializeJson(*jsonDoc, Serial);
#endif
    Serial.print(F("\n"));
}

void jsonMessenger::jsonReadSerialLoop(jsonStateData_t &jsonRX_data) {

    jsonRX_data = emptyJsonData; // jsonStateData_t{STATE_NULL,EMPTY 0, 0, 0.0, false, "", "", false}; // Default message that will be passed out if no data received or cannot be parsed

    if (Serial.available() > 0) {
        // Serial.println("Serial Available");
        char command[JSON_RX_SIZE];
        // create JSON document
        StaticJsonDocument<JSON_RX_SIZE> jsonRXdoc;
        // Receive Command
        Serial.readBytesUntil(10, command, JSON_RX_SIZE); // 10 = "\n"

        for (int i = 0; i < JSON_RX_SIZE; i++) { // trim command down to remove redundent characters
            if (command[i] == '}') {
                command[i + 1] = '\0';
                break;
            }
        }

#if PRINT_RX_COMMAND == true
        Serial.print(F("\n{\"rxed\": \""));
        Serial.print(command);
        Serial.println(F("\"}"));
#endif

        // Serial.read();  // clear any additional data left in the buffer

        // NEW FUNCTION, try deserializing directly from stream
        // deserializeJson(jsonRXdoc, Serial);  // less overhead but harder to debug
        [[maybe_unused]] DeserializationError error = deserializeJson(jsonRXdoc, command); // more overhead but can print message before processing (good for debugging)

#if PRINT_DESERIAL_ERROR == true
        Serial.print("{\"deserialization\":\"");
        Serial.print(error.c_str());
        Serial.println(F("\"}"));
#endif

        JsonObject root = jsonRXdoc.as<JsonObject>(); // this was previously doc.to<JsonObject>(); DID NOT WORK! does now with "as"
                                                      // Now to parse the JSON message
                                                      // First get number of elements in the jsonStates enum numValues = NUM_VALUES;
                                                      // Then loop through all keys & see if root contains key

        bool set_keyword_used = false; // Make the assumption that set keyword has not been used,
                                       // NOTE THIS LINE CHANGED 27/11/25 to try and fix compiler warning about unititialised var
        //  const char *keyString;  // If the root contains "set" -> preload value (which contains key) into valueString and compare this along with root.key in loop below (2 birds, 1 stone)
        const char *keyString = {"\n"};
        if (root.containsKey("set")) {
            keyString = jsonRXdoc["set"];
            set_keyword_used = true; // if set has been used, then we need to extract the data in a slightly different way
        }

        for (uint16_t i = 0; i < NUM_CMDS; i++) {
            //  Serial.print(i);  // loop through all the keys
            //  Serial.print("  Checking against key: ");
            //  Serial.println(jsonCommandKeys[i]);

            if (root.containsKey(jsonStateMap[i].cmd) || strcmp(keyString, jsonStateMap[i].cmd) == 0) { // Match is found, i holds the correct ENUM reference for the state

                //   jsonRX_data.data_type = dataTypes_array[jsonStateMap[i].data_type]; // this should contain the correct enum for the datatype
                jsonRX_data.data_type = jsonStateMap[i].data_type;

#if DEBUG_JSON_MESSENGER == true
                Serial.print(F("{\"cmd\":\""));
                Serial.print(jsonStateMap[i].cmd);
                Serial.print(F("\",\"num\":\""));
                Serial.print(i);
                Serial.print(F("\",\"dataType\":\""));
                Serial.print(jsonStateMap[i].data_type);
                Serial.print("\",\"typeName\":\"");
                Serial.print(typeNames[jsonStateMap[i].data_type]);
                Serial.print("\",");
                // Set the flags to trigger the state change
                Serial.print("\"state\":\"");
                Serial.print(jsonStateMap[i].state);
                Serial.print("\",");
                Serial.print(F("\"data\":\""));
#endif

                //  jsonRX_data.cmdState = i;  //
                jsonRX_data.stateEnum = jsonStateMap[i].state;
                //    jsonRX_data.cmdState = jsonStates(jsonStateMap[i].cmd);  // these two lines should be identical, except one passes the ENUM, the other (the same) int value
                jsonRX_data.cmd_received = true; // Set flag to be passed outside of library and notify a command has been sent (depreciated if using queue)

                // Copy data into  correct place in data structure, and convert to string for debugging printing
                // then deal with data depending on state

                if (jsonRX_data.data_type == EMPTY) { // ____________############# NO DATA TO EXTRACT ####################____________________
                                                      // Do nothing
#if DEBUG_JSON_MESSENGER == true
                    Serial.print("empty");
#endif
                } else if (jsonRX_data.data_type == INTEGER) { // ____________############# PARSING INTEGERS ####################____________________
                    jsonMessenger::extract_int(jsonRX_data, root, i, set_keyword_used);
                } else if (jsonRX_data.data_type == UINT) { // ____________############# PARSING UNSIGNED INTEGERS ####################____________________
                    jsonMessenger::extract_uint(jsonRX_data, root, i, set_keyword_used);
                } else if (jsonRX_data.data_type == FLOAT) { // ____________############# PARSING FLOATS ####################____________________
                    jsonMessenger::extract_float(jsonRX_data, root, i, set_keyword_used);
                } else if (jsonRX_data.data_type == BOOL) { // ____________############# PARSING BOOLS ####################____________________
                    jsonMessenger::extract_bool(jsonRX_data, root, i, set_keyword_used);
                } else if (jsonRX_data.data_type == CSTRING) { // ____________############# PARSING C-STYLE STRINGS (char arrays) ####################____________________
                    jsonMessenger::extract_cstring(jsonRX_data, root, i, set_keyword_used);
                } else if (jsonRX_data.data_type == DUAL_INT) { // ____________############# PARSING DUAL INTEGERS ####################____________________
                    jsonMessenger::extract_dual_int(jsonRX_data, root, i, set_keyword_used);
                } else if (jsonRX_data.data_type == AUTH_INT) { // ____________############# PARSING INT WITH AUTH ####################____________________// if auth then two datas must be extracted
                    jsonMessenger::extract_auth_int(jsonRX_data, root, i, set_keyword_used);
                } else if (jsonRX_data.data_type == AUTH_FLOAT) { // ____________############# PARSING FLOAT WITH AUTH ####################____________________//
                    jsonMessenger::extract_auth_float(jsonRX_data, root, i, set_keyword_used);
                } else if (jsonRX_data.data_type == AUTH_MSG) { // ____________############# PARSING MSG (cstring) WITH AUTH ####################____________________//
                    jsonMessenger::extract_auth_msg(jsonRX_data, root, i, set_keyword_used);
                } else {
#if DEBUG_JSON_MESSENGER == true
                    Serial.println(F("dataType-exception"));
#endif
                }
#if DEBUG_JSON_MESSENGER == true
                Serial.println("\"}");
#endif
#if JSON_USE_QUEUE == true
                if (jsonMessenger::enque_cmd(&jsonRX_data) == -1) {
                    Serial.println(F("{\cmd\":\"enque-failed\"}"));
                }
#endif
                return; //  no longer returns data as uses pass by reference // jsonRX_data;  // return the structure as the data has been extracted
            } else {
                if (i == NUM_CMDS - 1) { // if i = NUM_VALUES we have reached the end of the for loop, if no match has been found, print the unknown cmd
                    Serial.println(F("{\"cmd\":\"unknown\"}"));
                }
                // We have pre-parsed the alternative set command so now else doesnt need to do anything
            }
        }
    }
    return; // now returns data passed by reference jsonRX_data;
}

// const char *jsonMessenger::getCMDkey(jsonStates state) {
// std::cout << jsonCommandKeys[state] << "\0";
//  return jsonStateMap[state].cmd;
// }

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DATA EXTRACTION FUNCTIONS >>>>>>>>>>>>>>>>>>>>

void jsonMessenger::extract_int(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword) { // jsonRX_data.
    if (set_keyword) {
        data.intData = root["to"].as<int16_t>();
    } else {
        data.intData = root[jsonStateMap[map_number].cmd].as<int16_t>();
    }
#if DEBUG_JSON_MESSENGER == true
    Serial.print(data.intData);
#endif
}

void jsonMessenger::extract_uint(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword) {
    if (set_keyword) {
        data.uintData = root["to"].as<uint16_t>();
    } else {
        data.uintData = root[jsonStateMap[map_number].cmd].as<uint16_t>();
    }
#if DEBUG_JSON_MESSENGER == true
    Serial.print(data.uintData);
#endif
}

void jsonMessenger::extract_float(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword) {
    if (set_keyword) {
        data.floatData = root["to"].as<float>();
    } else {
        // jsonRX_data.floatData = jsonRXdoc[jsonCommandKeys[i]].as<float>();   // this line not working and stalling everything ( may have been unrelated!)
        data.floatData = root[jsonStateMap[map_number].cmd].as<float>(); // try extracted from root doc instead
    }
#if DEBUG_JSON_MESSENGER == true
    Serial.print(data.floatData);
#endif
}

void jsonMessenger::extract_bool(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword) {
    if (set_keyword) {
        data.boolData = root["to"].as<bool>(); // # NOTE FOR LATER, AT THE MOMENT THIS IS EXTRACTING FROM ROOT DOC, could also try jsonRXdoc
    } else {
        data.boolData = root[jsonStateMap[map_number].cmd].as<bool>();
    }
#if DEBUG_JSON_MESSENGER == true
    if (data.boolData) {
        Serial.print("true");
    } else {
        Serial.print("false");
    }
#endif
}

void jsonMessenger::extract_cstring(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword) {
    const char *extracted;
    if (set_keyword) {
        extracted = root["to"].as<const char *>();
    } else {
        extracted = root[jsonStateMap[map_number].cmd].as<const char *>();
    }
    memcpy(data.msg, extracted, JSON_MSG_LENGTH);
    data.msg[JSON_MSG_LENGTH - 1] = '\0';
#if DEBUG_JSON_MESSENGER == true
    Serial.print(data.msg);
#endif
}

void jsonMessenger::extract_dual_int(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword) {
    if (set_keyword) {
        data.intData = root["to"].as<int16_t>();
        data.uintData = root["num"].as<uint16_t>();
    } else {
        data.uintData = root[jsonStateMap[map_number].cmd].as<uint16_t>();
        data.intData = root["state"].as<int16_t>();
    }
#if DEBUG_JSON_MESSENGER == true
    Serial.print("dataA: ");
    Serial.print(data.uintData);
    Serial.print(" dataB: ");
    Serial.print(data.intData);

#endif
}

void jsonMessenger::extract_auth_int(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword) {
    const char *extract_secret;
    if (set_keyword) {
        data.intData = root["to"].as<int16_t>();
    } else {
        data.intData = root[jsonStateMap[map_number].cmd].as<int16_t>();
    }
    //  extract_secret = jsonRXdoc["auth"].as<const char *>();                                      // this will always use auth keyword
    JsonVariant auth = root["auth"]; /// safer? method

    if (auth.is<const char *>()) {
        const char *extract_secret = auth.as<const char *>();

        jsonMessenger::safe_copy_string(data.auth, extract_secret, sizeof data.auth); //// new version using strcpy and wrapped in function
                                                                                      //  memcpy(jsonRX_data.auth, extract_secret, AUTH_MSG_LENGTH-1);  // old version using memcpy
                                                                                      //   jsonRX_data.auth[AUTH_MSG_LENGTH-1] = '\0';
    } else {
        data.auth[0] = '\0';
    }
#if DEBUG_JSON_MESSENGER == true
    Serial.print("data: ");
    Serial.print(data.intData);
    Serial.print(" auth: ");
    Serial.print(data.auth);
#endif
}

void jsonMessenger::extract_auth_float(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword) {
    const char *extract_secret;
    if (set_keyword) {
        data.floatData = root["to"].as<float>();
    } else {
        data.floatData = root[jsonStateMap[map_number].cmd].as<float>();
    }
    extract_secret = root["auth"].as<const char *>();                             // this will always use auth keyword
    jsonMessenger::safe_copy_string(data.auth, extract_secret, sizeof data.auth); //// new version using strcpy and wrapped in function
//  memcpy(jsonRX_data.auth, extract_secret, AUTH_MSG_LENGTH-1);  // old version using memcpy
//   jsonRX_data.auth[AUTH_MSG_LENGTH-1] = '\0';
#if DEBUG_JSON_MESSENGER == true
    Serial.print("data: ");
    Serial.print(data.floatData);
    Serial.print(" auth: ");
    Serial.print(data.auth);
#endif
}

void jsonMessenger::extract_auth_msg(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword) {
    const char *extract_msg;
    const char *extract_secret;
    // first get the msg data
    if (set_keyword) {
        extract_msg = root["to"].as<const char *>();
    } else {
        extract_msg = root[jsonStateMap[map_number].cmd].as<const char *>();
    }
    jsonMessenger::safe_copy_string(data.msg, extract_msg, sizeof data.msg);
    // then use similar method for auth msg
    extract_secret = root["auth"].as<const char *>();                             // this will always use auth keyword
    jsonMessenger::safe_copy_string(data.auth, extract_secret, sizeof data.auth); // new version using strcpy and wrapped in function
                                                                                  // memcpy(jsonRX_data.auth, extract_secret, AUTH_MSG_LENGTH-1);  old version using
                                                                                  // memcpy jsonRX_data.auth[AUTH_MSG_LENGTH-1] = '\0';
#if DEBUG_JSON_MESSENGER == true
    Serial.print("data: ");
    Serial.print(data.msg);
    Serial.print(" auth: ");
    Serial.print(data.auth);
#endif
}

const char *jsonMessenger::getDataType(dataTypes_t type) {
    // std::cout << typeNames[type] << "\0";
    return typeNames[type];
}

const char *jsonMessenger::getStateEnum(stateDef_t state) { return stateNames[state]; }

void jsonMessenger::printStateData(jsonStateData_t &data) { // Use -> to assess members of a pointer to a struct
    // Serial.print(F("state: "));
    // Serial.print(jsonMessenger::getCMDkey(data->stateEnum));   // this no longer works as there is no way to back translate the current state back into
    // the command, but we can just print the actual triggered state, though this is now saved in PROGMEM so is a pain. Excluding for now
    Serial.print("stateEnum: ");
    Serial.println(jsonMessenger::getStateEnum(data.stateEnum));
    Serial.print(F(" dataType: "));
    Serial.println(jsonMessenger::getDataType(data.data_type));
    Serial.print(F(" intData: "));
    Serial.println(data.intData);
    Serial.print(F(" uintData: "));
    Serial.println(data.uintData);
    Serial.print(F(" Float: "));
    Serial.println(data.floatData);
    Serial.print(F(" bool: "));
    Serial.println(data.boolData);
    Serial.print(F(" msg: "));
    Serial.println(data.msg);
    Serial.print(F(" cmd: "));
    Serial.println(data.cmd_received);
    Serial.println();
}

/*
void jsonMessenger::print_cmds() {
  char printBuffer[200];
  for (int i = 0; i < NUM_VALUES; i++) {
    char descriptionBuffer[64];
    char rangeBuffer[32];
    strcpy_P(descriptionBuffer, (char *)pgm_read_ptr(&(jsonCmdDescription[i])));  // Necessary casts and dereferencing, just copy.
    strcpy_P(rangeBuffer, (char *)pgm_read_ptr(&(jsonCmdRange[1])));              // Necessary casts and dereferencing, just copy.
                                                                                  //  char printBuffer[200];
                                                                                  // formatted JSON string to print
    sprintf(printBuffer, "{\" %s \": \" %s \", \"desc\":\" %s \" }", jsonCommandKeys[i], rangeBuffer, descriptionBuffer);
    Serial.println(printBuffer);
  }
}
*/

// Call this in this format secretObject::safe_copy_string(target, newString , sizeof target);
void jsonMessenger::safe_copy_string(char *target, const char *newString, uint8_t targetLength) {
    strncpy(target, newString, targetLength - 1);
    target[targetLength - 1] = '\0'; // null terminator
}

#if JSON_USE_QUEUE == true
// Returns the number of items in the queue, or -1 on fail
int8_t jsonMessenger::enque_cmd(jsonStateData_t *newItem) {
    Serial.print(F("enque -> length:  "));
    if (queue_size < CMD_QUEUE_LENGTH) {
        jsonQueue[queue_size] = *newItem;
        queue_size++;
        Serial.println(queue_size);
        return queue_size;
    } else {
        Serial.println(-1);
        return -1;
    }
}
#endif

#if JSON_USE_QUEUE == true
// returns first queue item or 0 if queue is empty when called
jsonStateData_t jsonMessenger::dequeue_cmd() {
    jsonStateData_t first_item = {NONE, EMPTY, 0, 0.0, "", false};
    if (queue_size > 0) {
        jsonStateData_t first_item = jsonQueue[0];

        for (int i = 0; i < queue_size; i++) {
            // std::cout << "i: " << i << " i+1: " << i + 1 << std::endl;
            jsonQueue[i] = jsonQueue[i + 1];
        }
        queue_size--;
        Serial.print(F("Dequeue -> length:  "));
        Serial.println(queue_size);
        return first_item;
    } else {
        return first_item;
    }
}
#endif