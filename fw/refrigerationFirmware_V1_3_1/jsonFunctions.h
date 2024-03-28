/*   jsonFunctions

  All functions relating to JSON messages that are not wrapped up in state machine



*/


#if PRETTY_PRINT_JSON == true
#pragma JSON set to Pretty Print !-May experience problems with Machine Parsing !
char newline[3] = { "\n" };
#else
#pragma JSON set to standard JSON output - For human readability try enabling Pretty Print !
char newline[3] = { " " };
#endif



void build_json() {
  char json_header[] = "\'{";
  char json_buffer[JSON_BUFFER_SIZE] = { "" };  // this needs to be sized correctly 512 is too small 600 seems to work for now
  char float_buffer[8];
  char json_footer[] = "}\'";
  char valves[] = "valves";
  char relays[] = "relays";
  char sensors[] = "sensors";
  char temperature[] = "temperature";
  char pressure[] = "pressure";
  char misc[] = "misc";
  char s_status[] = "status";
  char s_timestamp[] = "timestamp";


  // start json string building
  sprintf(json_buffer, "%s%s  \"%s\" : %lu,", json_header, newline,s_timestamp, sampleTimestamp);

 // sprintf(json_buffer, "%s%s  \"%s\" : %u,", json_header, newline, s_timestamp, sampleTimestamp);  //removed the l designation for u
  // load valve data
  sprintf(json_buffer, "%s%s  \"%s\" : {", json_buffer, newline, valves);
  for (int i = 0; i < 7; i++) {
    sprintf(json_buffer, "%s%s    \"V%i\" : %i,", json_buffer, newline, i + 1, bool(adam6052_A.g_coilState & 1 << i));  // fancy binary operation to bitmask the valvestate variable with a power of 2 to get true or false for each valve based on valvestate int
  }
  sprintf(json_buffer, "%s%s    \"V%i\" : %i", json_buffer, newline, 8, bool(adam6052_A.g_coilState & 1 << 8));  // Added to remove comma from last line of JSON subsection
  sprintf(json_buffer, "%s%s  },", json_buffer, newline);

  //load power relay data
  sprintf(json_buffer, "%s%s  \"%s\" : {", json_buffer, newline, relays);
  // sprintf(json_buffer, "%s%s  \"relays\" : {", json_buffer, newline);   // trying to save space // didnt work
  for (int i = 0; i < 2; i++) {
    sprintf(json_buffer, "%s%s   \"%s\" : %i,", json_buffer, newline, relay_names[i], bool(adam6052_B.g_coilState & 1 << i));
  }
  sprintf(json_buffer, "%s%s   \"%s\" : %i", json_buffer, newline, relay_names[2], bool(adam6052_B.g_coilState & 1 << 2));  // Added to remove comma from last line of JSON subsection
  sprintf(json_buffer, "%s%s  },", json_buffer, newline);

  // Load sensor data
  sprintf(json_buffer, "%s%s  \"%s\" : {", json_buffer, newline, sensors);

  //sprintf(json_buffer, "%s%s  \"sensors\" : {", json_buffer, newline);

  // load pressure sensors
  sprintf(json_buffer, "%s%s    \"%s\" : {", json_buffer, newline, pressure);
  for (int i = 0; i < NUM_PRESSURE_SENSORS - 1; i++) {
    dtostrf(ps_vals[i], 6, 2, float_buffer);
    sprintf(json_buffer, "%s%s      \"PS%i\" : %6s,", json_buffer, newline, i + 1, float_buffer);
  }
  dtostrf(ps_vals[NUM_PRESSURE_SENSORS - 1], 6, 2, float_buffer);
  sprintf(json_buffer, "%s%s      \"PS%i\" : %6s", json_buffer, newline, NUM_PRESSURE_SENSORS, float_buffer);  // Added to remove comma from last line of JSON subsection

  sprintf(json_buffer, "%s%s    },", json_buffer, newline);


  // load temp sensors
  sprintf(json_buffer, "%s%s    \"%s\" : {", json_buffer, newline, temperature);
  for (int i = 0; i < NUM_TEMP_SENSORS - 1; i++) {
    dtostrf(ts_vals[i], 6, 2, float_buffer);
    sprintf(json_buffer, "%s%s      \"TS%i\" : %6s,", json_buffer, newline, i + 1, float_buffer);
  }
  dtostrf(ts_vals[NUM_TEMP_SENSORS - 1], 6, 2, float_buffer);
  sprintf(json_buffer, "%s%s      \"TS%i\" : %6s", json_buffer, newline, NUM_TEMP_SENSORS, float_buffer);  // Added to remove comma from last line of JSON subsection

  sprintf(json_buffer, "%s%s    },", json_buffer, newline);


  // load misc sensors
  sprintf(json_buffer, "%s\%s    \"%s\" : {", json_buffer, newline, misc);
  for (int i = 0; i < 4; i++) {  //# Changed loop here from i < 4 to i < 5 due to additional datapoint
    dtostrf(misc_vals[i], 6, 2, float_buffer);
    sprintf(json_buffer, "%s%s      \"%s\" : %6s,", json_buffer, newline, misc_names[i], float_buffer);
  }
  dtostrf(misc_vals[4], 6, 2, float_buffer);
  sprintf(json_buffer, "%s%s      \"%s\" : %6s", json_buffer, newline, misc_names[4], float_buffer);  // Added to remove comma from last line of JSON subsection

  sprintf(json_buffer, "%s%s    }", json_buffer, newline);

  // close sensors
  sprintf(json_buffer, "%s%s  },", json_buffer, newline);

  // load status message
  sprintf(json_buffer, "%s%s\"%s\" : {", json_buffer, newline, s_status);
  sprintf(json_buffer, "%s%s    \"%s\" : %i,", json_buffer, newline, status_names[0], status.ok);
  sprintf(json_buffer, "%s%s    \"%s\" : \"%s\",", json_buffer, newline, status_names[1], status.state);
  sprintf(json_buffer, "%s%s    \"%s\" : %i,", json_buffer, newline, status_names[2], status.code);
  sprintf(json_buffer, "%s%s    \"%s\" : \"%s\"", json_buffer, newline, status_names[3], status.message);
  sprintf(json_buffer, "%s%s  }", json_buffer, newline);


  // close json string
  sprintf(json_buffer, "%s%s%s", json_buffer, newline, json_footer);

  if (PRINT_JSON) {
    Serial.println(json_buffer);
  }
}
