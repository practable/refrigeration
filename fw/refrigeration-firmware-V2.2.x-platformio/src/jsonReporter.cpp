/*  jsonReporter.h

 Functions to load data into a json template and print to Serial Output

*/

#include "jsonReporter.h"

#include "globals.h"

jsonReporter::jsonReporter() {}

// rounds a number to 2 decimal places
// example: round(3.14159) -> 3.14
float jsonReporter::round2(double value) { return (int)(value * 100 + 0.5) / 100.0; }

// rounds a number to X decimal places and ensures fixed width of signed and unsigned
void jsonReporter::formatFloat(float value, char *buffer, size_t length, int decimalPlaces) {
    if (length < 4) { // Ensure buffer is large enough
        if (length > 0)
            buffer[0] = '\0';
        return;
    }

    char temp[10]; // Temporary buffer

#if !defined(ARDUINO_ARCH_SAMD)
    dtostrf(value, length - 1, decimalPlaces, temp);
#else
    decimalPlaces++;                           // just to stop compiler warning
    snprintf(temp, length - 1, "%.2f", value); // sizeof(temp
                                               //  sprintf(temp, "%.3f", value);
#endif

    // Replace '+' with space for positive numbers
    if (temp[0] == '+')
        temp[0] = ' ';

    // Right-align by shifting if necessary
    size_t tempLen = strlen(temp);
    if (tempLen < length - 1) {
        size_t padding = length - 1 - tempLen;
        memmove(buffer + padding, temp, tempLen + 1);
        memset(buffer, ' ', padding);
    } else {
        strncpy(buffer, temp, length - 1);
        // buffer[length - 1] = '\0';  // Ensure null termination
    }
    buffer[length - 1] = '\0'; // Ensure null termination
}

void jsonReporter::start_printing() { print_json_active = true; }

void jsonReporter::stop_printing() { print_json_active = false; }

void jsonReporter::print_json() { // const instrumentData_t &data

    StaticJsonDocument<JSON_TX_BUFFER_SIZE> jsonTX;

    const char *payload_n = {"payload"};
    const char *valves_n = {"valves"};
    const char *sensors_n = {"sensors"};
    const char *pressure_n = {"pressure"};
    const char *temp_n = {"temp"};
    const char *humidity_n = {"humidity"};
    const char *misc_n = {"misc"};

    // char float_buffer[8];  // buffer to hold fixed length floats
    // freeRAM = ram.getPrintStats("update_json");
    // Header
    jsonTX[F("timestamp")].set(millis()); // Message Timestamp set this last before printing
                                          //  Payload
                                          //  jsonTX[F("payload")][F("state")][F("val")].set(smState);
                                          //  jsonTX[F("payload")][F("state")][F("name")].set(stateNames[smState]);
                                          //  jsonTX[F("payload")][F("state")].set(stateNames[smState]);

    // new method to get state name text from progmem
    char buffer[14];
    strcpy_P(buffer, (char *)pgm_read_ptr(&(stateNames[sm.get_state()]))); // Necessary casts and dereferencing, just copy.
    jsonTX[payload_n][F("state")].set(buffer);

       // char buffer[13];
    // const char *ptr = (const char *)pgm_read_word(&stateNames[smState]);
    //  strncpy_P(buffer, ptr, sizeof(buffer));
    //  buffer[sizeof(buffer) - 1] = "\0";
    //  jsonTX[F("payload")][F("state")].set(buffer);

    // jsonTX[F("payload")][F("state")][F("val")].set(smState);  only needed for debugging state machine
    char floatBuffer[12];

    // Output Data
    for (int i = 0; i < 8; i++) {
        char buffer[4];
        sprintf(buffer, "V%d", i + 1);
        jsonTX[payload_n][valves_n][buffer].set(
            int(bool(adams.adamsCtrl[ADAM6052_A].g_coilState & 1 << i))); // fancy binary operation to bitmask the valvestate variable with a power of 2 to get true or false for each valve
    }

    //   jsonTX[payload_n][F("fan")][F("speed")].set(data.outputs.fan_speed);
    //  jsonTX[payload_n][F("fan")][F("target")].set(data.commands.fan_target);
    //   jsonTX[payload_n][F("fan")][F("state")].set(esc.esc_stateNames[data.status.fan_state]); // this conversion should not be done here

    // formatFloat(data.sensors.gen_freq_hz, floatBuffer, 8, 3);
    //    jsonTX[payload_n][F("gen")][F("freq")].set(data.sensors.gen_freq_hz);
    // formatFloat(data.sensors.gen_volts_V, floatBuffer, 8, 3);
    //    jsonTX[payload_n][F("gen")][F("volts")].set(data.sensors.gen_volts_V);
    // formatFloat(data.sensors.gen_acc_dHz_s, floatBuffer, 8, 3);
    //    jsonTX[payload_n][F("gen")][F("acc")].set(data.sensors.gen_acc_dHz_s);

    // formatFloat(data.sensors.dP_sense_V, floatBuffer, 8, 3);
    // jsonTX[payload_n][F("air")][F("voltage")].set(data.sensors.dP_sense_V); // dP_sense_data.voltage);
    // formatFloat(data.sensors.dP_pressure_Pa, floatBuffer, 8, 3);
    //   jsonTX[payload_n][F("air")][F("dP_Pa")].set(data.sensors.dP_pressure_Pa);
    // formatFloat(data.sensors.dP_dense_gk_m3, floatBuffer, 8, 3);
    //   jsonTX[payload_n][F("air")][F("dense")].set(data.sensors.dP_dense_gk_m3);
    // formatFloat(data.sensors.dP_airspeed_m_s, floatBuffer, 8, 3);
    //   jsonTX[payload_n][F("air")][F("speed")].set(data.sensors.dP_airspeed_m_s);

    // jsonTX[payload_n][F("air")][F("speed")].set(current_air_speed_one);

    // For Arrays
    // create all the JSONarrays
    JsonArray jsonArrayOne = jsonTX[payload_n][sensors_n].createNestedArray(pressure_n);
    JsonArray jsonArrayTwo = jsonTX[payload_n][sensors_n].createNestedArray(temp_n);
    // JsonArray jsonArrayThree = jsonTX[payload_n][sensors_n].createNestedArray(humidity_n);

    //   jsonTX[payload_n][servo_n][F("yaw")].set(data.outputs.yaw_servo_pos);
    //   jsonTX[payload_n][servo_n][F("yaw_trgt")].set(data.commands.yaw_servo_target);
    //   jsonTX[payload_n][servo_n][F("pitch")].set(data.outputs.pitch_servo_pos);
    //   jsonTX[payload_n][servo_n][F("pitch_trgt")].set(data.commands.pitch_servo_target);

    //  jsonTX["state"][F("dmmy_ld")].set(data.outputs.dummy_load_state);
    //   jsonTX["state"][F("smooth")].set(data.outputs.smoothing_cap_state);

    // logData_t current_log = lifeLog.get_current();   // this line needs to be doing its thing elsewhere and putting its data into the datastore

    //   formatFloat(data.lifetime.motor_hours, floatBuffer, 8, 3);
    //   jsonTX[life_n][F("motor_h")].set(floatBuffer);                 //   current_log.motorSeconds + lifeCounters.motorSeconds
    //   jsonTX[life_n][F("gen_rot")].set(data.lifetime.gen_rotations); //   current_log.generatorRotations + gen_rotations
    //   jsonTX[life_n][F("yaws")].set(data.lifetime.yaws_cmd);         // current_log.yawsCommanded + lifeCounters.yawsCommanded
    //   jsonTX[life_n][F("pitches")].set(data.lifetime.pitches_cmd);   // current_log.pitchCommanded + lifeCounters.pitchCommanded

    // jsonTX[F("payload")][("meta")][F("samples")].set(num_samples);
    JsonArray timeArray = jsonTX[payload_n][F("meta")].createNestedArray("time");

    // for loop to place data into arrays (is it possible to just pass whole string without looping up to 200 times!?)
    // for (int i = 0; i < num_samples; i++) {
    char float_buffer_one[8]; // issues caused by reusing buffer
                              //    formatFloat(data.sensors.atmos_temp_C, float_buffer_one, sizeof(float_buffer_one), 2);
    jsonArrayOne.add(float_buffer_one);

    char float_buffer_two[8];
    //  formatFloat(data.sensors.atmos_pressure_Pa, float_buffer_two, sizeof(float_buffer_two), 2);
    jsonArrayTwo.add(float_buffer_two);

    //   char float_buffer_three[8];
    //   formatFloat(data.sensors.atmos_humid_pc, float_buffer_three, sizeof(float_buffer_three), 2);
    //   jsonArrayThree.add(float_buffer_three);

    // timeArray.add(data.sensors.timestamp_mS); // timestamp_array[i]
    //  }

    // Meta Data & Debugging
    // jsonTX[F("meta")][F("sizeof")].set(sizeof(jsonTX));

    // int JSON_bytes = sizeof(jsonTX);  // used for debugging
    // Serial.print("Size of JSON: ");
    // Serial.println(JSON_bytes);

    if (print_json_active) {
#if PRETTY_PRINT_JSON == true
        // #pragma JSON set to Pretty Print !-May experience problems with Machine Parsing
        serializeJsonPretty(jsonTX, Serial);
#else
        // #pragma JSON set to standard JSON output - For human readability try enabling Pretty Print !
        serializeJson(jsonTX, Serial);
#endif
        Serial.print(F("\n"));
        delay(2);
    }
}
