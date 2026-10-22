/* jsonMessenger.h

_Library to simplify two way communication over Serial interfaces using JSON formatted messages_

Imogen Heard
17/10/24

Please see: https://github.com/ImogenWren/jsonMessenger_library for latest version and usage instructions
NOTE: This library is memory intensive and may not be suitable for lightweight microcontrollers (uno, nano, AtTiny etc)

Version V1.0.0
- Focus on receiving & parsing incoming Serial CMD messages in JSON format

Version v3
- Tying everything together finally


*/

#ifndef jsonMessenger_h
#define jsonMessenger_h

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <ArduinoJson.h>
#include <stdio.h>

#include "jsonStateData.h"

#define JSON_MESSENGER_VERSION "4.0.0"

#define DEBUG_JSON_MESSENGER true

#define JSON_USE_QUEUE false       // At least one of these should be true
#define JSON_USE_SINGLE_FRAME true // Single frame is always valid, but this can be used to disable features not wanted when using queue

#define JSON_RX_SIZE 64    // 32 Working on Arduino Nano
#define CMD_QUEUE_LENGTH 3 // 3 Working on Arduino Nano
// #define JSON_MSG_LENGTH 17  // Length of msg array in json data structure
// #define AUTH_MSG_LENGTH 9

#define PRINT_DESERIAL_ERROR true
#define DEBUG_JSON_MESSENGER true

class jsonMessenger
{
private:
  uint16_t NUM_CMDS = NUM_JSON_CMDS;

public:
  // constructor
  jsonMessenger();

  void jsonBegin();

  void jsonReadSerialLoop(jsonStateData_t &jsonRX_data); // function needs to be called periodically to accept incoming serial messages, parse & return jsonStateData_t with new state /and data required for new state

  void printJSON(StaticJsonDocument<JSON_RX_SIZE> *jsonDoc); // Prints the static jsonRXdoc

  // const char *getCMDkey(jsonStates state);  // to print the state in human readable form without coping the entire list of keys to global scope

  const char *getDataType(dataTypes_t type);
  const char *getStateEnum(stateDef_t state);

  void printStateData(jsonStateData_t &data);

  //  void print_cmds();

#if JSON_USE_QUEUE == true
  int8_t enque_cmd(jsonStateData_t *newItem); // Returns the number of items in the queue, or -1 on fail

  jsonStateData_t dequeue_cmd(); // returns first queue item or 0 if queue is empty when called
#endif

private:
  void safe_copy_string(char *target, const char *newString, uint8_t targetLength);

  void extract_int(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword); // private function for parsing INTEGER variable from jsonMessage
  void extract_uint(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword);
  void extract_float(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword);
  void extract_cstring(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword);
  void extract_bool(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword);
  void extract_dual_int(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword);
  void extract_auth_int(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword);
  void extract_auth_float(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword);
  void extract_auth_msg(jsonStateData_t &data, JsonObject &root, uint8_t map_number, bool set_keyword);

#if JSON_USE_QUEUE == true
  jsonStateData_t jsonQueue[CMD_QUEUE_LENGTH];
  int8_t queue_size = 0; // must be managed "manually"
#endif
};

#endif
