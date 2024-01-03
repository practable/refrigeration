/*  sensorObj.cpp - The Generic Sensor Conversion Library for Arduino

    Convert Voltage, 4-20mA and 0-20mA  linear signals into process values

    Imogen Heard
    21/12/23


*/

#include "sensorObj.h"



void sensorObj::set_range_min(float _process_min, float _dac_min) {
  dac_min = _dac_min;
  process_min = _process_min;
  rangeSet++;
}


void sensorObj::set_range_max(float _process_max, float _dac_max) {
  dac_max = _dac_max;
  process_max = _process_max;
  rangeSet++;
}


void sensorObj::setCalibration() {
  Serial.print(sensorID);
  if (rangeSet < 2) {
    Serial.println(": Sensor Range has Not Been Set!");
  } else {
    input_range = dac_max - dac_min;
    process_range = process_max - process_min;
    cal.offset = process_min;
    cal.factor = process_range / input_range;
    calSet = true;
    Serial.println(": Sensor Calibration data saved");
  }
}

float sensorObj::calcProcessVar(float _dacVal) {
  float processVarible = 0;
  processVarible = (_dacVal * cal.factor) + cal.offset;
  currentVal = processVarible;
#if DEBUG == true
  Serial.print(sensorID);
  Serial.print(": ");
  Serial.print(_dacVal);  
  Serial.print(ADC_units);
  Serial.print(processVarible);
  Serial.print(" ");
  Serial.println(process_units);
#endif
  return processVarible;
}

float sensorObj::returnVal() {
  return currentVal;
}

void sensorObj::updateHistory(float _sensorVal) {
  //currentVal = _sensorVal;  // this is done during calc process val
  for (int i = 0; i < SENSOR_BUFFER_SIZE - 1; i++) {  //make space in the array: inefficient for large arrays - better solution?
    sensorHistory[i] = sensorHistory[i + 1];
  }
  sensorHistory[SENSOR_BUFFER_SIZE - 1] = _sensorVal;

#if DEBUG == true
  // for (int i = 0; i < SENSOR_BUFFER_SIZE;i++ ){
  // Serial.print(sensorHistory[i]);
  // Serial.print(", ");
  // }
//  Serial.println();
#endif
}



float sensorObj::calAverage() {
}
float sensorObj::calcMin() {
}
float sensorObj::calcMax() {
}
float sensorObj::calcDxDy() {
}
float sensorObj::calcLMS() {
}