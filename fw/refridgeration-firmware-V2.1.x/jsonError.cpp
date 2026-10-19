
#include <ArduinoJson.h>  // installed version 6.21.5 [Arduino Library Manager]

#include "jsonError.h"



jsonError::jsonError() {
}


void jsonError::json_error(const char *level, const char *message) {
  StaticJsonDocument<125> jsonDoc;
  jsonDoc[level].set(message);
  serializeJson(jsonDoc, Serial);
  Serial.println();
}

void jsonError::json_error_data(const char *level, const char *message, const char *label, const int16_t data) {
  StaticJsonDocument<1250> jsonDoc;
  jsonDoc[level].set(message);
  jsonDoc[label].set(data);
  serializeJson(jsonDoc, Serial);
  Serial.println();
}

void jsonError::json_error_two_data(const char *level, const char *message, const char *label, const float data, const char *label2, const float data2) {
  StaticJsonDocument<500> jsonDoc;
  jsonDoc[level].set(message);
  jsonDoc[label].set(data);
  jsonDoc[label2].set(data2);
  serializeJson(jsonDoc, Serial);
  Serial.println();
}


void jsonError::json_error_type_2_data(const char *level, const char *message, const char *type, const char *label, const float data, const char *label2, const float data2) {
  StaticJsonDocument<600> jsonDoc;
  jsonDoc[level].set(message);
  jsonDoc["type"].set(type);
  jsonDoc[label].set(data);
  jsonDoc[label2].set(data2);
  serializeJson(jsonDoc, Serial);
  Serial.println();
}
