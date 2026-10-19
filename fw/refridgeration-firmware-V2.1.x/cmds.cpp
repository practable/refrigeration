#include "cmds.h"

const char null_desc[] = "n/a";
// Unique Cmnds
const char desc_0[] = "Set Fan Speed: 0 - 180";
const char desc_1[] = "Set Yaw Angle: 0 - 180 deg";
const char desc_2[] = "Set Blade Pitch Angle: 0 - 180 deg";
const char desc_3[] = "Stop Fan (estop)";
const char desc_4[] = "Bump Fan Speed to Bump Speed";
const char desc_5[] = "Set load: True / False";
const char desc_6[] = "Set Smoothing Caps: True / False";
// new cmnds
const char desc_7[] = "Set/Reset Motor Runtime (S): INT & AUTH";
const char desc_8[] = "Set/Reset Generator Rotations: INT & AUTH";
const char desc_9[] = "Set/Reset Yaws Commanded: INT & AUTH";
const char desc_10[] = "Set/Reset Pitch Commanded: INT & AUTH";

// Common Commands
const char desc_A[] = "Set Samplerate in Hz (dflt: 1) DNU";
const char desc_B[] = "Set Print Rate in Hz (dflt: 1) DNU";
const char desc_C[] = "Start Data Streaming";
const char desc_D[] = "End Data Streaming";
const char desc_E[] = "set the secret word";
const char desc_F[] = "Reset to Default Condition NIY";
const char desc_G[] = "print sensor data & status NIY";
const char desc_H[] = "print commands list";

extern const int16_t NUM_CMDS = 20;

const char *const cmdDesc[] = {null_desc, desc_0, desc_1, desc_2, desc_3, desc_4, desc_5, desc_6, desc_7, desc_8, desc_9, desc_10, desc_A, desc_B, desc_C, desc_D, desc_E, desc_F, desc_G, desc_H};

void print_cmds() {
    // Serial.println(F("{\"na     \" : \"n/a\", \"desc\" : \"n/a\"}"));
    // Unique Commands Here
    // ---
    // Serial.println(F("{\"sample \" : \"1 to 200 \", \"desc\" : \"Set Samplerate in Hz (dflt: 1)\"}"));
    // Serial.println(F("{\"print  \" : \"1 to 200 \", \"desc\" : \"Set Print Rate in Hz (dflt: 1) \"}"));
    // Serial.println(F("{\"stream \" : \"null\", \"desc\" : \"Start Data Streaming  \"}"));
    // Serial.println(F("{\"endst  \" : \"null \", \"desc\" : \"End Data Streaming  \"}"));
    // Serial.println(F("{\"secret \" : \"char[8]\", \"desc\" : \"set the secret word  \"}"));
    // Serial.println(F("{\"info\"    : \"null\", \"desc\" : \"print sensor data & status \"}"));
    // Serial.println(F("{\"help\"    : \"null\", \"desc\" : \"print commands list\"}"));
}

// prints a single command from lists
void print_cmd2(uint8_t cmnd_num) {
    StaticJsonDocument<120> jsonCMDs;
    char cmdBuffer[10];
    char typeBuffer[10];
    sprintf(cmdBuffer, "%-7s", jsonStateMap[cmnd_num].cmd);
    sprintf(typeBuffer, "%-8s", typeNames[jsonStateMap[cmnd_num].data_type]);
    char buffer[60];
#ifdef __AVR__
    strcpy_P(buffer, (char *)pgm_read_ptr(&(cmdDesc[cmnd_num]))); // Necessary casts and dereferencing, just copy. (for AVR)
#elif defined(ESP32)
    strcpy_P(buffer, cmdDesc[cmnd_num]);
#else
    strcpy_P(buffer, cmdDesc[cmnd_num]); // incase some other implementation exists
#endif
    jsonCMDs[cmdBuffer].set(typeBuffer);
    jsonCMDs[F("desc")].set(buffer);
    serializeJson(jsonCMDs, Serial);
    Serial.println();
}

void print_cmds2() {
    for (int i = 0; i < NUM_CMDS; i++) {
        print_cmd2(i);
    }
}
