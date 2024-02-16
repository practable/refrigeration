/*  sensorObj.cpp - The Generic Sensor Conversion Library for Arduino

    Convert Voltage, 4-20mA and 0-20mA  linear signals into process values

    Imogen Heard
    21/12/23


*/

#include "sensorObj.h"






void sensorObj::setCalibration(float _process_min, float _process_max, float _adc_min, float _adc_max, float _postoffset) {
  Serial.print(sensorID);
  adc_min = _adc_min;
  process_min = _process_min;
  adc_max = _adc_max;
  process_max = _process_max;
  input_range = adc_max - adc_min;
  process_range = process_max - process_min;
  cal.preoffset = adc_min;  // the initial offset is on the adc side, not the PROCESS side
  cal.factor = process_range / input_range;
  cal.postoffset = _postoffset;
  calSet = true;
  Serial.println(F(": Sensor Calibration data saved"));
}




// Generic Method given values passed as min/max during startup. Non Generic methods coming soon!
float sensorObj::calcProcessVar(float _adcVal) {
  float processVarible = 0;
  // Disable sensor scaling to see raw ADC value for calibration
#if DISABLE_SENSOR_SCALING == false
  processVarible = ((_adcVal - cal.preoffset) * cal.factor) + cal.postoffset ;
  currentVal = processVarible;
#elif DISABLE_SENSOR_SCALING == true
#pragma "Warning Sensor Scaling DISABLED"
  processVarible = _adcVal;
#endif
#if DEBUG_SENSOR_CALC == true
  Serial.print(sensorID);
  Serial.print(F(": "));
  Serial.print(_adcVal);
  Serial.print(ADC_units);
  Serial.print(processVarible);
  Serial.print(F(" "));
  Serial.println(process_units);
#endif
  return processVarible;
}




float sensorObj::calcPressure(float _voltage) {
  float pressure;
  float vMin = 1.0;
  float vRange = 5.0;
  float pRange = 30.0;
  float factor = pRange / vRange;
  pressure = ((_voltage - vMin) * factor);
  return pressure;
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

#if DEBUG_SENSOR_HISTORY == true
  for (int i = 0; i < SENSOR_BUFFER_SIZE; i++) {
    Serial.print(sensorHistory[i]);
    Serial.print(F(", "));
  }
  Serial.println();
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