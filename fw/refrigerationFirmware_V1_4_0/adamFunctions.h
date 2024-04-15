/*   adamFunctions

  All functions relating to ADAM industrial controllers



*/





void adams_begin() {
#if ADAM6052A_ACTIVE == true
  adam6052_A.begin();
  adam6052_A.set_coils(0b00000000);
#endif
#if ADAM6052B_ACTIVE == true
  adam6052_B.begin();
  adam6052_B.set_coils(0b00000000);
#endif
#if ADAM6217A_ACTIVE == true
  adam6217_C.begin();
#endif
#if ADAM6217B_ACTIVE == true
  adam6217_D.begin();
#endif
  delay(1000);
}




void sample_adam6052A() {
  adam6052_A.read_coils();
//adam6052A.read_digital_inputs();  // not needed in this iteration
#if ADAM6052A_ACTIVE == true
#if DEBUG_SAMPLING == true
  adam6052A.printBin(adam6052A.g_coilState);
#endif
#endif
}





void sample_adam6052B() {
  adam6052_B.read_coils();
//adam6052A.read_digital_inputs();  // not needed in this iteration
#if ADAM6052B_ACTIVE == true
#if DEBUG_SAMPLING == true
  adam6052B.printBin(adam6052B.g_coilState);
#endif
#endif
}




void sample_adam6217C() {
  adam6217_C.read_analog_inputs();  // read all temperature sensor inputs
  sampleTimestamp = millis();       // This takes a "generic" timestamp that should be accurate enough for most purposes
  for (int i = 0; i < NUM_PRESSURE_SENSORS; i++) {
    ps_vals[i] = pressure_s[i].calcProcessVar(adam6217_C.d_array.f_data[i]);
    // Check pressure vals here?
    // TODO status message for low/high pressure
#if DEBUG_SAMPLING == true
    Serial.print(ps_vals[i]);
    Serial.print(F(" Bar"));
#endif
  }
  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    ts_vals[i] = temp_s[i].calcProcessVar(adam6217_C.d_array.f_data[i + 3]);  // index for temp sensors starts at 3// calculate the process variable and save to temperature sensor array
                                                                              //   ts_times[i] = adam6217A.d_array.timeStamp_mS[i];                     // save the timestamp to the 2D array - depreciated no space left
                                                                              // temp_s[i].updateHistory(temp);                                    // this is only needed if doing maths in firmware(future use case?)
#if DEBUG_SAMPLING == true
    Serial.print(ts_vals[i]);
    Serial.print(F(" degC"));
#endif
  }
}




void sample_adam6217D() {
  adam6217_D.read_analog_inputs();  // This samples { "flow", "power", "PSA", "TSA" };
  //  sampleTimestamp = millis();  // This takes a "generic" timestamp that should be accurate enough for most purposes (not needed here unless running without the temp & pressure sensors)
  misc_vals[0] = flow_s.calcProcessVar(adam6217_D.d_array.f_data[0]);
  misc_vals[1] = power_s.calcProcessVar(adam6217_D.d_array.f_data[1]);
  // misc_vals[2] = t_ambi.calcProcessVar(adam6217_D.d_array.f_data[2]);  // These are now i2c sensors
  //  misc_vals[3] = p_ambi.calcProcessVar(adam6217_D.d_array.f_data[3]); // NOTE: This will cause errors in setion below unless loop is changed

#if DEBUG_SAMPLING == true
  for (int i = 0; i < 2; i++) {  // changed loop from i < 4 to i < 2
    Serial.print(misc_names[i]);
    Serial.print(F(" : "));
    Serial.print(misc_vals[i]);
    Serial.print(F(" "));
    Serial.println(misc_units[i]);
  }
#endif
}



