


#ifndef jsonStateMachine_h
#define jsonStateMachine_h

#define DEBUG_STATE_MACHINE false
#define DEBUG_STATES true

#include "cmds.h"
#include "jsonStateData.h"
// 4. Define the state machine function prototypes.
//    Any function that will be passed data from a user input will be passed the same jsonStateData_t structure as an argument.
// make sure every state named in step one has a prototype here!

// Required States

// #define TOTAL_NUM_STATES 22

// After finishing this list -> try running https://github.com/ImogenWren/json-state-machine/blob/main/state-machine-generator.py script to auto generate
// the StateMachine[] array, and template functions for each state!

// extern const uint16_t stateTableCount;

class stateMachine {
public:
  // constructor
  stateMachine();



  // stateHandler_t stateHandler[];  // ties together states with the state ENUM   // previously extern
  void change_state(stateDef_t new_state);
  stateDef_t get_state();

  void sm_Run(jsonStateData_t &stateData);

  // user defined state prototypes
  void sm_state_null(jsonStateData_t &stateData);
  void sm_state_init(jsonStateData_t &stateData);
  void sm_state_wait(jsonStateData_t &stateData);
  // Experiment Specific States
  void sm_state_stop(jsonStateData_t &stateData);       // stop compressor, after delay, close valves
  void sm_state_running(jsonStateData_t &stateData);    // Dont know if needed any longer
  void sm_state_valve(jsonStateData_t &stateData);      // Set Valve to State
  void sm_state_comp(jsonStateData_t &stateData);       // Set compressor state
  void sm_state_lights(jsonStateData_t &stateData);     // set lights state
  void sm_state_fans(jsonStateData_t &stateData);       // set both fans state
  void sm_state_evap(jsonStateData_t &stateData);       // set the state of the evaporation fan
  void sm_state_cond(jsonStateData_t &stateData);       // set the state of the condensing fan
  void sm_state_fanspeed(jsonStateData_t &stateData);   // set both fan speeds to the same value
  void sm_state_evapspeed(jsonStateData_t &stateData);  // set the speed of the evaporation fan
  void sm_state_condspeed(jsonStateData_t &stateData);  // Set the speed of the condensing fan
  void sm_state_regas(jsonStateData_t &stateData);      // enter regas state (what does this mean rn?)
  void sm_state_quickstart(jsonStateData_t &stateData); // set up fridge with default working values (what does this mean?)


  // Common & Utility States
  void sm_state_samplerate(jsonStateData_t &stateData);
  void sm_state_printrate(jsonStateData_t &stateData);
  void sm_state_start_stream(jsonStateData_t &stateData);
  void sm_state_stop_stream(jsonStateData_t &stateData);
  void sm_state_set_secret(jsonStateData_t &stateData);
  void sm_state_reset(jsonStateData_t &stateData);
  void sm_state_info(jsonStateData_t &stateData);
  void sm_state_help(jsonStateData_t &stateData);






    // stateHandler_t stateHandler[];
    typedef void (stateMachine::*stateFunc_t)(jsonStateData_t &stateData);

  typedef struct {
    stateDef_t State;  //< Defines thestate enum
    stateFunc_t func;  // void (*func)(stateMachine* self, jsonStateData_t &stateData);  //< Defines the function to run
  } stateHandler_t;

  uint16_t stateTableCount = NUM_STATES;

const stateHandler_t stateHandler[NUM_STATES] = {
    { STATE_NULL,       &stateMachine::sm_state_null },
    { STATE_INIT,       &stateMachine::sm_state_init },
    { STATE_WAIT,       &stateMachine::sm_state_wait },
    { STATE_STOP,       &stateMachine::sm_state_stop },
    { STATE_RUNNING,    &stateMachine::sm_state_running },
    { STATE_SET_VALVE,  &stateMachine::sm_state_valve },
    { STATE_COMP,       &stateMachine::sm_state_comp },
    { STATE_LIGHTS,     &stateMachine::sm_state_lights },
    { STATE_FANS,       &stateMachine::sm_state_fans },
    { STATE_EVAP_FAN,   &stateMachine::sm_state_evap },
    { STATE_COND_FAN,   &stateMachine::sm_state_cond },
    { STATE_FANS_SPEED, &stateMachine::sm_state_fanspeed },
    { STATE_EVAP_SPEED, &stateMachine::sm_state_evapspeed },
    { STATE_COND_SPEED, &stateMachine::sm_state_condspeed },
    { STATE_REGAS,      &stateMachine::sm_state_regas },
    { STATE_QUICKSTART, &stateMachine::sm_state_quickstart },
    { STATE_SAMPLERATE, &stateMachine::sm_state_samplerate },
    { STATE_PRINTRATE,  &stateMachine::sm_state_printrate },
    { STATE_STARTSTREAM,&stateMachine::sm_state_start_stream },
    { STATE_STOPSTREAM, &stateMachine::sm_state_stop_stream },
    { STATE_SETSECRET,  &stateMachine::sm_state_set_secret },
    { STATE_RESET,      &stateMachine::sm_state_reset },
    { STATE_INFO,       &stateMachine::sm_state_info },
    { STATE_HELP,       &stateMachine::sm_state_help }
};



private:
  stateDef_t smState = STATE_INIT;   // use library methods to get & set state when outside of library
  stateDef_t lastState;
};

#endif
