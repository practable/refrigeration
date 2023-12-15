/* Refrigeration - State Machine



State machine boilerplate from https://www.edn.com/electronics-blogs/embedded-basics/4406821/Function-pointers---Part-3--State-machines



*/

#include "ArduinoJson-v6.9.1.h"
#define COMMAND_SIZE 64

StaticJsonDocument<COMMAND_SIZE> doc;
char command[COMMAND_SIZE];

bool debug = true;

/**
 * Defines the valid states for the state machine
 * 
 */
typedef enum {
  STATE_INIT,
  STATE_WAIT,
  STATE_STOP,
  STATE_RUNNING,
  STATE_SELECT_VALVE,
  STATE_SELECT_RELAY,
  STATE_FANS_ON,
  STATE_FANS_OFF
} StateType;

// State Names Array (Makes printing the current state prettier)
char stateNames[][32] = {
  "STATE_INIT",
  "STATE_WAIT",
  "STATE_STOP",
  "STATE_RUNNING",
  "STATE_SELECT_VALVE",
  "STATE_SELECT_RELAY",
  "STATE_FANS_ON",
  "STATE_FANS_OFF"
};

//state Machine function prototypes
void sm_state_init(void);
void sm_state_wait(void);
void sm_state_stop(void);
void sm_state_running(void);
void sm_state_valve(void);
void sm_state_relay(void);
void sm_state_fans_on(void);
void sm_state_fans_off(void);

/**
 * Type definition used to define the state
 */




typedef struct
{
  StateType State;     //< Defines the command
  void (*func)(void);  //< Defines the function to run
} StateMachineType;



/**
 * A table that defines the valid states of the state machine and
 * the function that should be executed for each state
 */
StateMachineType StateMachine[] = {
  { STATE_INIT, sm_state_init },
  { STATE_WAIT, sm_state_wait },
  { STATE_STOP, sm_state_stop },
  { STATE_RUNNING, sm_state_running },
  { STATE_SELECT_VALVE, sm_state_valve },
  { STATE_SELECT_RELAY, sm_state_relay },
  { STATE_FANS_ON, sm_state_fans_on },
  { STATE_FANS_OFF, sm_state_fans_off }
};

int NUM_STATES = 8;

/**
 * Stores the current state of the state machine
 */

StateType smState = STATE_INIT;
StateType lastState;


// Global Variables

int valveNum = 0;    // when command is Rxed theses values are updated so when state_valves is called, the valve and its new state are saved globally.
int valveState = 0;  // after state has finished setting valves it should set these variables back to 0





/**
* Define the functions for each state
*/

void sm_state_init() {
  Serial.println("State Machine: Init");
  // Init all o/ps to default state
  smState = STATE_WAIT;
}

char exampleCommands[][64] = {
  "{\"mode\":\"stop\"}",
  "{\"cmd\":\"fans\",\"param\":0}",
  "{\"valve\":1, \"state\":1}",
  "{\"fans\":1}",
  "{\"comp\":0}"
};


void sm_state_wait() {
  // Check to see if first time state has been called in sequence
  if (lastState != smState) {
    // If first iteration print state machine status
    Serial.println("State Machine: Waiting");
    Serial.println("Enter Command in format:");
    int numExamples = sizeof(exampleCommands)/sizeof(exampleCommands[0]);   // just get the size of the example commands array
    for (int i = 0; i < numExamples; i++) {
      Serial.println(exampleCommands[i]);          // print example commands
    }

    lastState = smState;
    // Do anything else that needs to happen first time state is called
  }
  // Do everything that repeats in this state

  // Define the next state if required
  // smState = STATE_WAIT;
}

void sm_state_stop() {
  Serial.println("State Machine: Stop");
  // Stop Compressor
  // Stop Fans
  // Close V1-4
  // Close V5 & V6
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_running() {
  Serial.println("State Machine: Running");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_valve() {
  Serial.println("State Machine: Set Valve");
  Serial.print("Valve Num: ");
  Serial.print(valveNum);
  Serial.print(",  Valve Status: ");
  Serial.println(valveState);
  valveNum = 0;
  valveState = 0;
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_fans_on() {
  Serial.println("State Machine: Fans On");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_fans_off() {
  Serial.println("State Machine: Fans Off");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_relay() {
  Serial.println("State Machine: Set Relay");
  lastState = smState;
  smState = STATE_WAIT;
}



/**
* Define the State Machine Function
*/

void sm_Run(void) {
  smState = readSerialJSON(smState);

  if (smState < NUM_STATES) {
    if (lastState != smState) {
      if (debug) {
        Serial.print("{\"State\":");
        Serial.print(stateNames[smState]);
        Serial.println("}");
      }
    }
    (*StateMachine[smState].func)();
  } else {
    Serial.println("Exception in State Machine");
  }
}



/**
* Define the JSON Parsing Function
*/

StateType readSerialJSON(StateType smState) {
  if (Serial.available() > 0) {
    char start[] = "start";
    char stop[] = "stop";

    char cmd_wd[] = "cmd";
    char vlv_wd[] = "valve";
    char md_wd[] = "mode";
    char valve[] = "valve";
    char fans[] = "fans";
    char comp[] = "comp";




    Serial.readBytesUntil(10, command, COMMAND_SIZE);

    Serial.print("command received: ");
    Serial.println(command);

    deserializeJson(doc, command);

    // First work out what the command word is

    // First check if the first index is "valve"
    valveNum = doc["valve"];

    if (valveNum > 0) {
      Serial.print("valveNum: ");
      Serial.print(valveNum);
      Serial.print("   Valve Status: ");
      valveState = doc["state"];
      Serial.println(valveState);
      smState = STATE_SELECT_VALVE;
    }

    // Then check if first index contains a mode change

    const char* cmd = doc["cmd"];
    if (cmd > 0) {
    }
    Serial.println(cmd);


    if (strcmp(cmd, stop) == 0) {
      smState = STATE_STOP;
      Serial.println("{\"result\":\"ok\"}");
    } else {
      // Serial.println("{\"error\":\"Unable to stop\"}");
    }


    if (strcmp(cmd, valve) == 0) {
      int valveNum = doc["param"];
      if ((valveNum >= 0) && (valveNum <= 6)) {
        smState = STATE_SELECT_VALVE;
        Serial.println("{\"result\":\"ok\"}");
      } else {
        Serial.println("{\"error\":\"Unknown Valve Selected)\"}");
      }
    }


    if (strcmp(cmd, fans) == 0) {
      int fanState = doc["param"];
      if (fanState > 0) {
        smState = STATE_FANS_ON;
        Serial.println("{\"result\":\"ok\"}");
      } else {
        smState = STATE_FANS_OFF;
        Serial.println("{\"result\":\"ok\"}");
      }
    }

  }  //if bytes available
  return smState;
}



void setup() {
  Serial.begin(115200);
  Serial.println("\n\nDeploying Refrigeration State Machine");
}

void loop() {
  sm_Run();
}
