
// included headers to pull datatypes


#include "jsonStateData.h" // self contained

#ifndef datastore_h
#define datastore_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <wProgram.h>
#endif

// Global datastore
// Moving to a more difinitive global variables storage template.
// bundle all queryable data into one place?
// Should this also be wrapped in a class?
// Maybe, just try this for now

// First data is organised into different catigorys
/*
- Sensors
- Outputs
- Commands
- Status
- Alarms
- Settings
- Lifetime
*/

// sensors_t: Measured & calculated data from system
typedef struct {
    uint32_t timestamp_mS; // time data was recorded from sensors

    float gen_freq_hz;
    float gen_acc_dHz_s;
    float gen_volts_V;

    float dP_sense_V;
    float dP_pressure_Pa;
    float dP_dense_gk_m3;
    float dP_airspeed_m_s;

    float atmos_temp_C;
    float atmos_pressure_Pa;
    float atmos_humid_pc;
} sensors_t;

// outputs_t: Current Setpoint of outputs
typedef struct {
    float fan_speed;
    float yaw_servo_pos;
    float pitch_servo_pos;
    bool dummy_load_state;
    bool smoothing_cap_state;
} outputs_t;

typedef struct {
    float fan_target;
    float yaw_servo_target;
    float pitch_servo_target;
} commands_t;

typedef struct {
    stateDef_t prog_state;
    escStatus_t fan_state;
} status_t;

typedef struct {
    int overspeed;
    int overvolt;
    int overacc;
    int timeout;
} alarms_t;

typedef struct {
    uint8_t na;
} settings_t;

typedef struct {
    float motor_hours;
    uint32_t gen_rotations;
    uint32_t yaws_cmd;
    uint32_t pitches_cmd;
} lifetime_t;

// instrumentData_t: instrument data ties all these structures together into one record of instrument state
typedef struct {
    sensors_t sensors;
    outputs_t outputs;
    commands_t commands;
    status_t status;
    alarms_t alarms;
    settings_t settings;
    lifetime_t lifetime;
} instrumentData_t;

#endif