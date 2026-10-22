/*   jsonError.h

  Functions for displaying error messages using JSON format


*/


#ifndef jsonError_h
#define jsonError_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <wProgram.h>
#endif


#include <ArduinoJson.h>  // installed version 6.21.5 [Arduino Library Manager]
// #include "globals.h"


class jsonError {

private:

public:
  // constructor
  jsonError();




  void json_error(const char *level, const char *message);

  void json_error_data(const char *level, const char *message, const char *label, const int16_t data);

  void json_error_two_data(const char *level, const char *message, const char *label, const float data, const char *label2, const float data2);

  void json_error_type_2_data(const char *level, const char *message, const char *type, const char *label, const float data, const char *label2, const float data2);

};

#endif