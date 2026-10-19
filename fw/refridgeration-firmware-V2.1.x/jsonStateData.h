/*   stateDatatypes.h

 - Lists all shared data Structures & Enums for all jsonMessenger alighned modules


*/

#include "Arduino.h"

#ifndef jsonStateData_h
#define jsonStateData_h

// Prereq -> define message and auth message char lengths

#define JSON_MSG_LENGTH 17  // Length of msg array in json data structure
#define AUTH_MSG_LENGTH 9

// 1. Define all the valid states for the state machine with an enum.
//    - This should include states triggered by user input, but may also contain states that are only accessable programatically
// - Must start with "NULL_STATE"
// - Must end with "NUM_STATES"
typedef enum {
  STATE_NULL,
  STATE_INIT,
  STATE_WAIT,
  STATE_STOP,
  STATE_RUNNING,
  STATE_SET_VALVE,
  STATE_COMP,
  STATE_LIGHTS,
  STATE_FANS,
  STATE_EVAP_FAN,
  STATE_COND_FAN,
  STATE_FANS_SPEED,
  STATE_EVAP_SPEED,
  STATE_COND_SPEED,
  STATE_REGAS,
  STATE_QUICKSTART,
  STATE_SAMPLERATE,
  STATE_PRINTRATE,
  STATE_STARTSTREAM,
  STATE_STOPSTREAM,
  STATE_SETSECRET,
  STATE_RESET,
  STATE_INFO,  // report settings, cal data and validity to user
  STATE_HELP,
  NUM_STATES  // Sentinal value lets us get the total number of states without manually counting. Do not forget this value, it is important for correct function
} stateDef_t;

// 1b. Also define the names for the ENUMs as const char strings
constexpr const char *stateNames[NUM_STATES] = {  // force newline
  "NULL",                                         /// can I comment here
  "INIT",                                         // or here?
  "WAIT",                                         //
  "STOP",                                         //
  "RUNNING",                                      //
  "VALVE",                                        //
  "COMP",                                         //
  "LIGHTS",                                       //
  "FANS",                                         //
  "EVAP",                                         //
  "COND",
  "FANS_SPEED",
  "EVAP_SPEED",  //
  "COND_SPEED",  //
  "REGAS",       //
  "QUICKSTART",
  "SMPLRT",     //
  "PRINTRT",    //
  "STREAM",     //
  "STPSTREAM",  //
  "SETSECRET",  //
  "RESET",      //
  "INFO",       //
  "HELP"
};  //

// 2. Define an enum to define variable type used, These will be linked to a state enum so when a keyword is received, we can look up what data type should be sent with it
typedef enum {  // enum to pass variable types between functions
  EMPTY,
  INTEGER,
  UINT,
  FLOAT,
  CSTRING,
  BOOL,
  DUAL_INT,    // 19/10/26 new datatype,
  AUTH_INT,    // 14/07/25 adding new datatype, this will tell jsonMessenger that 2 datas will be present, but will use already existing datatypes in RX data structure
  AUTH_FLOAT,  // 12/12/25 auth with float data
  AUTH_MSG     // 27/11/25 adding new datatype, auth with char message
} dataTypes_t;

// 2b. Place these enums into an array to enable lookup by index (This shouldnt be nessissary but it fixed a bug at one point)
const dataTypes_t dataTypes_array[10] = { EMPTY, INTEGER, UINT, FLOAT, CSTRING, BOOL, DUAL_INT, AUTH_INT, AUTH_FLOAT, AUTH_MSG };

// these are just to silence compiler warnings, maybe there is a better way of doing this but I havnt figured it out yet
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

// 2c. List the same enums as cStrings, this will enable human readability of enum above
static char typeNames[][8] = { "EMPTY", "INTEGER", "UINT", "FLOAT", "CSTRING", "BOOL", "DUALINT", "AUTHINT", "AUTHFLT", "AUTHMSG" };

#pragma GCC diagnostic pop

// 3. Define a structure that will hold our command word to enter a state, the datatype to be passed to that state, and the ENUM for the state it triggers
// This will enable to user to build a table showing each state, the command to enter the state and the datatype passed to the state

typedef struct {
  const char cmd[10];     //< Defines the command
  dataTypes_t data_type;  //< Defines the ENUM for the data type
  stateDef_t state;
} jsonStateMapData_t;

// 3b. Fill out state map for each command word

const jsonStateMapData_t jsonStateMap[] = { { "na", dataTypes_t::EMPTY, STATE_NULL },
                                            // Unique States
                                            { "stop", dataTypes_t::EMPTY, STATE_STOP },
                                            { "valve", dataTypes_t::DUAL_INT, STATE_SET_VALVE },
                                            { "comp", dataTypes_t::INTEGER, STATE_COMP },
                                            { "lamp", dataTypes_t::INTEGER, STATE_LIGHTS },
                                            { "fans", dataTypes_t::INTEGER, STATE_FANS },
                                            { "evap", dataTypes_t::INTEGER, STATE_EVAP_FAN },
                                            { "cond", dataTypes_t::INTEGER, STATE_COND_FAN },
                                            { "fanspeed", dataTypes_t::INTEGER, STATE_FANS_SPEED },
                                            { "evapspeed", dataTypes_t::INTEGER, STATE_EVAP_SPEED },
                                            { "condspeed", dataTypes_t::INTEGER, STATE_COND_SPEED },
                                            { "regas", dataTypes_t::EMPTY, STATE_REGAS },
                                            { "quickst", dataTypes_t::EMPTY, STATE_REGAS },
                                            // Common States
                                            { "sample", dataTypes_t::UINT, STATE_SAMPLERATE },
                                            { "print", dataTypes_t::UINT, STATE_PRINTRATE },
                                            { "stream", dataTypes_t::EMPTY, STATE_STARTSTREAM },
                                            { "endst", dataTypes_t::EMPTY, STATE_STOPSTREAM },
                                            { "secret", dataTypes_t::CSTRING, STATE_SETSECRET },
                                            { "reset", dataTypes_t::EMPTY, STATE_RESET },
                                            { "info", dataTypes_t::EMPTY, STATE_INFO },
                                            { "help", dataTypes_t::EMPTY, STATE_HELP } };

constexpr size_t NUM_JSON_CMDS = sizeof(jsonStateMap) / sizeof(jsonStateMap[0]);

// 4. Declare a structure that will hold all the data that is needed by the state machine AND any states within the state machine
typedef struct {
  stateDef_t stateEnum;   // This likely supercedes the commandState enum, as we can just direcly plug this variable into smState, saving another list of if/elses
  dataTypes_t data_type;  // The type of data being passed along with structure (though state should know what data to expect anyway), this could be removed to save space
  int16_t signedInt;      // empty generic data slots for each data type
  uint16_t uInt;
  float floatData;
  bool boolData;
  char msg[JSON_MSG_LENGTH];
  char auth[AUTH_MSG_LENGTH];
  bool cmd_received;  // Flag set true by jsonLoop when cmd is received
} jsonStateData_t;

// 5. Define a structure that will be used to build a table, tying together a state ENUM with the function for the associated state

//   void (*func)(jsonStateData_t &stateData);
#endif
